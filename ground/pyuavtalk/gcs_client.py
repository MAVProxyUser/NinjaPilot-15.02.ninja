#!/usr/bin/env python3
"""gcs_client.py - drive the NinjaPilot GCS automation surface.

The GCS must run with NINJAPILOT_GCS_AUTOMATION=1 (port 17654 default).
Every call is one JSON line in, one JSON line out, on the GUI thread.
"""
import socket, json, time


class GcsClient:
    def __init__(self, host="127.0.0.1", port=17654, timeout=8.0):
        self.addr = (host, port)
        self.timeout = timeout
        self.sock = None
        self.buf = b""

    def connect(self, retries=30):
        for _ in range(retries):
            try:
                s = socket.create_connection(self.addr, timeout=self.timeout)
                s.settimeout(self.timeout)
                self.sock = s
                return True
            except OSError:
                time.sleep(0.5)
        return False

    def _cmd(self, **kw):
        line = (json.dumps(kw) + "\n").encode()
        self.sock.sendall(line)
        while b"\n" not in self.buf:
            chunk = self.sock.recv(65536)
            if not chunk:
                raise ConnectionError("GCS closed the socket (possible crash)")
            self.buf += chunk
        line, _, self.buf = self.buf.partition(b"\n")
        return json.loads(line.decode())

    # verbs
    def ping(self):                 return self._cmd(cmd="ping")
    def workspaces(self):           return self._cmd(cmd="workspaces")
    def workspace(self, name):      return self._cmd(cmd="workspace", name=name)
    def tree(self, depth=12, mx=4000): return self._cmd(cmd="tree", depth=depth, max=mx)
    def find(self, name="", role="", mx=100): return self._cmd(cmd="find", name=name, role=role, max=mx)
    def menus(self):                return self._cmd(cmd="menus")
    def menu(self, path):           return self._cmd(cmd="menu", path=path)
    def do(self, path, action="Press"): return self._cmd(cmd="do", path=path, action=action)
    def get(self, path):            return self._cmd(cmd="get", path=path)
    def set(self, path, value):     return self._cmd(cmd="set", path=path, value=value)


if __name__ == "__main__":
    import sys
    c = GcsClient()
    if not c.connect():
        print("could not connect to GCS automation port"); sys.exit(1)
    print("ping:", c.ping())
    print("workspaces:", json.dumps(c.workspaces(), indent=2))
