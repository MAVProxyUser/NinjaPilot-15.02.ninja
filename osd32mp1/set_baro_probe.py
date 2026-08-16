import dronecan, time
# node 126: the running allocator owns 127
node = dronecan.make_node("can0", node_id=126, bitrate=1000000)
NID = 124
def do(req, label):
    out = []
    node.request(req, NID, lambda e: out.append(e))
    t0 = time.time()
    while not out and time.time() - t0 < 3: node.spin(0.05)
    print(label, out[0].transfer.payload if out else "NO RESPONSE")
    return out
P = dronecan.uavcan.protocol.param
do(P.GetSet.Request(name="BARO_PROBE_EXT"), "current:")
v = P.Value(integer_value=1024)                      # bit10 = BMP388
do(P.GetSet.Request(name="BARO_PROBE_EXT", value=v), "set->")
do(P.ExecuteOpcode.Request(opcode=P.ExecuteOpcode.Request().OPCODE_SAVE), "save:")
r = dronecan.uavcan.protocol.RestartNode.Request()
r.magic_number = r.MAGIC_NUMBER
do(r, "restart:")
