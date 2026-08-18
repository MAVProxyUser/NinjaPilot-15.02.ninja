#!/bin/sh
# The over-CAN transfer is INTERMITTENTLY flaky: the same image needs
# 843 reads and boots on a good run, 1700-2400 reads and fails on a bad
# one. Retry until the node reports OPERATIONAL.
systemctl stop ninjapilot
for i in 1 2 3 4 5; do
  echo "=== attempt $i ==="
  timeout 640 python3 /home/root/can_flash_v3.py 2>&1 | tail -3
  sleep 5
  M=$(timeout 20 python3 - <<PY
import socket, struct, time
s=socket.socket(socket.AF_CAN, socket.SOCK_RAW, socket.CAN_RAW); s.bind(("can0",))
m="?"; t=time.time()+8
while time.time()<t:
    d=s.recv(72); cid,dlc=struct.unpack("<IB3x", d[:8]); c=cid&0x1FFFFFFF
    if c&0x80 or (c&0x7F)!=124: continue
    if ((c>>8)&0xFFFF)==341 and dlc>=7: m=(d[8+4]>>3)&7
print(m)
PY
)
  echo "  -> node124 mode=$M"
  if [ "$M" = "0" ]; then echo "*** BOOTED on attempt $i ***"; break; fi
done
systemctl start ninjapilot
echo "DONE fw=$(systemctl is-active ninjapilot)"
