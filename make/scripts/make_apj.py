#!/usr/bin/env python3
'''
Wrap a raw firmware .bin in a PX4 .apj container.

Boards that keep their stock PX4/ArduPilot bootloader are flashed with the PX4
uploader protocol, which expects this JSON container rather than OpenPilot's
own .opfw format.  The bootloader checks board_id against its own compiled-in
value and refuses an image that does not match, so getting that right is what
stops you writing, say, a Revo image onto a PixRacer.

Format matches ArduPilot's Tools/scripts/make_apj.py so that the ArduPilot and
PX4 uploaders, QGroundControl and Mission Planner all accept the result.

Usage: make_apj.py <input.bin> <output.apj> --board-id N [--description TEXT]
'''

import argparse
import base64
import json
import zlib

parser = argparse.ArgumentParser(description='Wrap a .bin in a PX4 .apj container')
parser.add_argument('bin', help='raw firmware image, linked at the bootloader load address')
parser.add_argument('apj', help='output .apj path')
parser.add_argument('--board-id', type=int, required=True,
                    help='PX4 board id (11 = FMUv4 / PixRacer)')
parser.add_argument('--description', default=None, help='human readable description')
parser.add_argument('--version', default='0.1', help='firmware version string')
parser.add_argument('--pad-to', default=None,
                    help='pad the image with 0xFF up to this size (decimal or 0x..) before --append')
parser.add_argument('--append', default=None,
                    help='file to append after padding: the OpenPilot firmware info block, so the '
                         'running firmware can report its description and git hash')

args = parser.parse_args()

with open(args.bin, 'rb') as f:
    img = f.read()

if args.pad_to is not None:
    pad_to = int(args.pad_to, 0)
    if len(img) > pad_to:
        raise SystemExit("make_apj: image is %u bytes, larger than the %u it must be padded to" % (len(img), pad_to))
    img += b'\xff' * (pad_to - len(img))
if args.append is not None:
    with open(args.append, 'rb') as f:
        img += f.read()

apj = {
    "board_id": args.board_id,
    "magic": "APJFWv1",
    "description": args.description or ("Firmware for board id %u" % args.board_id),
    "image": base64.b64encode(zlib.compress(img, 9)).decode('utf-8'),
    "summary": args.bin,
    "version": args.version,
    "image_size": len(img),
    "board_revision": 0,
    "signed_firmware": False,
}

with open(args.apj, 'w') as out:
    out.write(json.dumps(apj, indent=4))

print("  APJ         %s (%u bytes, board id %u)" % (args.apj, len(img), args.board_id))
