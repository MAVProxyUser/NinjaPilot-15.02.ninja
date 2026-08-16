import websocket
import ssl

url = "wss://ai.watchfun.cn/ws/transcribe?mode=3&language=en"

headers = [
    "appVersion: 1.1.2",
    "language: en",
    "osType: iOS",
    "osVersion: 26.5",
    "phoneBrand: iPhone",
    "phoneModel: iPad8,6",
    "isInChina: 0",
    "x-request-appid: 9kEKG2jc3GBlwv6a",
]

ws = websocket.create_connection(
    url,
    header=headers,
    timeout=10,
)

print("CONNECTED")
print("status:", ws.getstatus())

ws.settimeout(3)

try:
    while True:
        msg = ws.recv()
        print("RX:", repr(msg))
except Exception as e:
    print("recv:", type(e).__name__, e)

ws.close()

