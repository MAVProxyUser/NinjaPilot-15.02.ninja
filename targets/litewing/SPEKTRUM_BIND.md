# spektrum_bind — bind firmware for the LiteWing satellite

This branch is `litewing` with one difference: `.bind_pulses = 9` in
`targets/litewing/board_hw_defs.c`. Do not fly it.

For the first 30 s after every boot the DSM task sends one 9-pulse train on
IO15 every 210 ms (red LED blinks), then starts the UART. 9 pulses = internal
DSMX 11 ms, the mode Spektrum recommends for a single remote.

Why it is done this way: Spektrum's Remote Receiver Interfacing spec requires
the pulses within 200 ms of the *satellite's* power-up, and this board's DSM
task starts ~2.8 s after reset (bootloader 0.4 s, WiFi 2.4 s). So the
satellite is powered *after* the board instead. One train per window matters:
the satellite counts every falling edge in its window and the count selects
the mode; two trains gave 18 edges and the transmitter reported Bind Failed.

## Procedure

1. Build and flash this branch (`idf.py -p <port> -b 115200 flash`).
2. Transmitter into bind mode, keep it there.
3. Satellite unplugged, or its 3.3 V lead off.
4. Press RESET on the board. ~3 s later the red LED starts blinking.
5. Plug the satellite in while it blinks. Its LED fast-blinks, then goes solid.
   If its LED does not change, the plug-in fell in the gap between trains:
   unplug and plug again within the 30 s.
6. Transmitter out of bind mode.
7. Flash `litewing` again. Left on this firmware, every boot spends 30 s
   pulsing the receiver line with the UART down.

A second remote for the *same* airframe must be bound in external mode
(10 pulses) at the same time as the internal one; this board has a single
DSM input, so that is not useful here yet.
