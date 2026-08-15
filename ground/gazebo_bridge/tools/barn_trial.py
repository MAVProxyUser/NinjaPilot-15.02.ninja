#!/usr/bin/env python3
"""One-shot intercept trial: does the balloon get stopped, or does it reach the barn?

PROTOCOL (as specified by the operator):
  - trails ON
  - success requires felt=True, the vehicle's OWN IMU registering the strike.
    A pass through the hitbox is NOT a success.
  - first-pass miss == failure == the balloon reaches the barn. Cut the run
    immediately and start the next one; no stern chase, no second attempt.
  - push both speeds: interceptor and balloon.

WHY felt=True IS THE BAR: sampled separation bottoms out AT the contact
distance (the ball deflects), so "0.58m" cannot distinguish a graze from a
solid strike. The IMU peak-hold detector reads the 250Hz stream, so it cannot
alias a real impulse away - it is the only honest success signal available.

ANTI-HANG (this rig has produced three different hangs):
  - hard per-run timeout, whole process GROUP killed on expiry
  - stragglers reaped between runs, unconditionally
  - the gz server is restarted every RESTART_EVERY runs AND whenever a run
    times out or no-flies: a long-lived server eventually stops initialising
    the attitude estimator and every later run silently sits on the pad.
"""
import json
import os
import re
import signal
import subprocess
import sys
import time

SC = os.path.dirname(os.path.abspath(__file__))
BR = "/Users/kfinisterre/Desktop/OP Revo Redux/NinjaPilot-15.02.ninja/ground/gazebo_bridge"
RUN_TIMEOUT = 300          # s, hard ceiling per run
RESTART_EVERY = 6          # runs between preventative server restarts
RESULTS = os.path.join(SC, "barn_trial_results.json")


def sh(cmd, timeout=60):
    try:
        return subprocess.run(cmd, shell=True, capture_output=True, text=True,
                              timeout=timeout)
    except subprocess.TimeoutExpired:
        return None


def reap():
    for pat in ("gazebo_bridge.py", "fw_simposix", "run_intercept.sh",
                "trail_daemon"):
        sh(f"pkill -f {pat}", timeout=20)
    time.sleep(1.5)


def restart_server(why):
    print(f"[trial] restarting gz server ({why})", flush=True)
    reap()
    sh("pkill -9 -f 'gz sim'", timeout=20)
    time.sleep(4)
    env = (f'export GZ_SIM_RESOURCE_PATH="{BR}/models"; '
           f'export GZ_GUI_PLUGIN_PATH="{BR}/gui_plugins/WindControl/build"; ')
    subprocess.Popen(
        env + f'cd "{BR}" && nohup gz sim -s -r --headless-rendering '
        f'worlds/quadcopter_ninjapilot.sdf > "{SC}/gzserver.log" 2>&1 &',
        shell=True)
    time.sleep(9)
    subprocess.Popen(
        env + f'cd "{BR}" && nohup gz sim -g > "{SC}/gzgui.log" 2>&1 &',
        shell=True)
    time.sleep(12)
    # whole-farm overview, barn at the top
    sh("gz service -s /gui/move_to/pose --reqtype gz.msgs.GUICamera "
       "--reptype gz.msgs.Boolean --timeout 3000 --req 'pose: {position: "
       "{x: -5, y: -75, z: 60}, orientation: {x: -0.2089, y: 0.2089, "
       "z: 0.6756, w: 0.6756}}'", timeout=20)
    ok = sh("gz topic -l | grep -c cam_track", timeout=25)
    print(f"[trial] server up (tracker topics: "
          f"{ok.stdout.strip() if ok else '?'})", flush=True)


def parse(label):
    """-> dict with felt/intercepted/sep/vert/t_hit, from log + track."""
    out = {"felt": False, "intercepted": False, "sep": None,
           "vert": None, "t_hit": None, "flew": False, "note": ""}
    log = os.path.join(SC, f"{label}.log")
    try:
        txt = open(log).read()
    except OSError:
        out["note"] = "no log"
        return out
    m = re.search(r"intercept_test: (\w+) - intercepted=(\w+), felt=(\w+), "
                  r"min_sep=([\d.]+)m", txt)
    if m:
        out["intercepted"] = m.group(2) == "True"
        out["felt"] = m.group(3) == "True"
        out["sep"] = float(m.group(4))
    if "FIRST PASS MISS" in txt:
        out["note"] = "first-pass miss (aborted)"
    if "ESTIMATOR STUCK" in txt or "waiting for attitude estimator" in txt and not m:
        out["note"] = "no-fly (estimator)"
    if "could not spawn target" in txt:
        out["note"] = "no-fly (spawn)"
    try:
        tr = json.load(open(os.path.join(SC, f"{label}_track.json")))["track"]
        if tr:
            out["flew"] = max(-r[1][2] for r in tr) > 3.0
            i = min(range(len(tr)), key=lambda k: tr[k][4])
            out["t_hit"] = round(tr[i][0], 1)
            if out["sep"] is None:
                out["sep"] = round(tr[i][4], 2)
            out["vert"] = round(-(tr[i][1][2] - tr[i][2][2]), 2)
    except Exception:
        pass
    return out


def run_one(label, ispeed, tspeed, vposp, vveld):
    env = dict(os.environ)
    env.update({
        "NINJAPILOT_ISPEED": str(ispeed),
        "NINJAPILOT_TARGET_SPEED": str(tspeed),
        "NINJAPILOT_VPOSP": str(vposp),
        "NINJAPILOT_VVELD": str(vveld),
        "NINJAPILOT_TRAILS": "1",
        "NINJAPILOT_VISION": "0",
        "TMPDIR": SC,
    })
    t0 = time.time()
    timed_out = False
    with open(os.path.join(SC, f"{label}_runner.txt"), "w") as fh:
        p = subprocess.Popen([f"{BR}/run_intercept.sh", label], env=env,
                             stdout=fh, stderr=subprocess.STDOUT,
                             preexec_fn=os.setsid)
        try:
            p.wait(timeout=RUN_TIMEOUT)
        except subprocess.TimeoutExpired:
            timed_out = True
            try:
                os.killpg(os.getpgid(p.pid), signal.SIGKILL)
            except Exception:
                pass
            p.wait(timeout=30)
    r = parse(label)
    r.update({"label": label, "ispeed": ispeed, "tspeed": tspeed,
              "vposp": vposp, "vveld": vveld,
              "secs": round(time.time() - t0, 1), "timed_out": timed_out})
    if timed_out:
        r["note"] = "TIMEOUT"
    # THE VERDICT the operator asked for.
    r["stopped_it"] = bool(r["felt"])
    r["barn_hit"] = not r["stopped_it"]
    return r


def main():
    plan = json.load(open(os.path.join(SC, "barn_trial_plan.json")))
    deadline = time.time() + plan.get("minutes", 60) * 60
    results = []
    if os.path.exists(RESULTS):
        try:
            results = json.load(open(RESULTS))
        except Exception:
            results = []
    n_since_restart = 99      # force a restart before the first run
    for cfg in plan["runs"]:
        if time.time() > deadline:
            print("[trial] time budget reached - stopping", flush=True)
            break
        if n_since_restart >= RESTART_EVERY:
            restart_server("scheduled")
            n_since_restart = 0
        reap()
        r = run_one(cfg["label"], cfg["ispeed"], cfg["tspeed"],
                    cfg.get("vposp", 0.25), cfg.get("vveld", 0.08))
        n_since_restart += 1
        results.append(r)
        json.dump(results, open(RESULTS, "w"), indent=1)
        verdict = "STOPPED (felt)" if r["stopped_it"] else "BARN HIT"
        print(f"[trial] {r['label']:6s} i={r['ispeed']} b={r['tspeed']} "
              f"vP={r['vposp']} vD={r['vveld']} -> {verdict:14s} "
              f"sep={r['sep']} vert={r['vert']} {r['note']} ({r['secs']}s)",
              flush=True)
        if r["timed_out"] or not r["flew"]:
            restart_server("bad run")
            n_since_restart = 0
    # tally
    print("[trial] ======== TALLY ========", flush=True)
    groups = {}
    for r in results:
        k = (r["ispeed"], r["tspeed"], r["vposp"], r["vveld"])
        groups.setdefault(k, []).append(r)
    for k, rs in sorted(groups.items()):
        stopped = sum(1 for x in rs if x["stopped_it"])
        print(f"[trial] i={k[0]} balloon={k[1]} vP={k[2]} vD={k[3]}: "
              f"STOPPED {stopped}/{len(rs)}, BARN HITS {len(rs)-stopped}",
              flush=True)
    tot = len(results)
    st = sum(1 for r in results if r["stopped_it"])
    print(f"[trial] OVERALL: {st}/{tot} stopped, {tot-st} balloons reached "
          f"the barn", flush=True)
    print("[trial] TRIAL_COMPLETE", flush=True)


if __name__ == "__main__":
    main()
