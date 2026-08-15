#!/usr/bin/env python3
"""Tally the barn trial, separating INVALID runs from real barn hits.

The operator's rule is "first-pass miss == barn hit". That is right for
GUIDANCE outcomes. But a run where the ball never spawned, or the attitude
estimator never initialised, is not a guidance outcome at all - the
interceptor never got a shot. Scoring those as barn hits would understate
the guidance and, worse, would make a harness bug look like a flight result.

So: three buckets, and the headline rate is computed over VALID runs only,
with the invalid count reported alongside so nothing is hidden.
"""
import json
import os
import sys

SC = os.path.dirname(os.path.abspath(__file__))
rs = json.load(open(os.path.join(SC, "barn_trial_results.json")))


def bucket(r):
    note = (r.get("note") or "").lower()
    if r.get("timed_out") or "no-fly" in note or not r.get("flew"):
        return "invalid"
    return "stopped" if r.get("stopped_it") else "barn"


groups = {}
for r in rs:
    k = (r["ispeed"], r["tspeed"], r["vposp"], r["vveld"])
    groups.setdefault(k, {"stopped": [], "barn": [], "invalid": []})
    groups[k][bucket(r)].append(r)

print("  %-28s %8s %8s %8s   %s" % ("config (icpt/balloon/vP/vD)",
                                    "STOPPED", "BARN", "invalid", "vert at merge"))
tot_s = tot_b = tot_i = 0
for k, g in sorted(groups.items()):
    s, b, i = len(g["stopped"]), len(g["barn"]), len(g["invalid"])
    tot_s += s; tot_b += b; tot_i += i
    verts = [x["vert"] for x in g["stopped"] + g["barn"] if x.get("vert") is not None]
    vtxt = " ".join(f"{v:+.2f}" for v in verts) if verts else "-"
    print("  i=%-4s b=%-4s vP=%-5s vD=%-5s %8d %8d %8d   %s"
          % (k[0], k[1], k[2], k[3], s, b, i, vtxt))
valid = tot_s + tot_b
print()
print("  VALID ENGAGEMENTS: %d | balloon STOPPED %d (%.0f%%) | reached the BARN %d"
      % (valid, tot_s, 100.0 * tot_s / valid if valid else 0, tot_b))
if tot_i:
    print("  (%d invalid run(s) excluded: no-fly / spawn failure / timeout - "
          "harness faults, not guidance outcomes)" % tot_i)
