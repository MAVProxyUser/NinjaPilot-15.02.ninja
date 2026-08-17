#!/bin/sh
# dt-pwm-unlock.sh - enable TIM3/TIM4/TIM8 PWM on the OSD32MP1-RED DTB.
# Run ON THE BOARD against the live DTB; reboot afterwards (and verify the
# reboot actually happened - watch ping drop, then check uptime).
#
# Result: SEVEN hardware PWM channels across four independent timers
# (TIM5 ships enabled in the stock DT; this adds the other three).
#
#   chip (addr)        channel  MCU pin  where            verified
#   TIM3 40001000      pwm1     PB5      RPi hdr pin 33   servo-verified
#   TIM4 40002000      pwm1     PD13     RPi hdr pin 32   servo-verified
#   TIM4 40002000      pwm2     PD14     mikroBUS PWM     servo-verified
#   TIM5 40003000      pwm1     PH11     RPi hdr pin 31   servo-verified
#   TIM8 44001000      pwm0     PI5      pin 12 / JP19    servo-verified
#   TIM8 44001000      pwm1     PI6      pin 38 / JP19    servo-verified
#   TIM8 44001000      pwm2     PI7      pin 35 / JP19    servo-verified
#
# NEVER hardcode pwmchipN - probing order shifts as chips are added.
# Find a timer's chip by address:
#   for c in /sys/class/pwm/pwmchip*; do readlink -f $c/device; done
#
# Sysfs rules learned the hard way:
#  - channels of ONE timer share a single period register: per-channel
#    duty, per-TIMER frame rate ("Device or resource busy" otherwise)
#  - lower duty_cycle BEFORE shrinking period below the current duty
#
# pinmux encoding: ((port-A)*16+pin)<<8 | (AF+1)
#   PB5  AF2 TIM3_CH2 = 0x1503      PD13 AF2 TIM4_CH2 = 0x3d03
#   PD14 AF2 TIM4_CH3 = 0x3e03     PI5/6/7 AF3 TIM8_CH1/2/3 = 0x8504/0x8604/0x8704
set -e
D=/boot/stm32mp157c-osd32mp1-red-v1_2.dtb
W=/tmp/pwm-unlock.dtb
cp "$D" "$W"

unlock() { # $1 timer-addr  $2 group-name  $3 phandle  $4... pinmux values
  T=$1; G=$2; PH=$3; shift 3
  fdtput -t s "$W" /soc/timer@$T status okay
  fdtput -t s "$W" /soc/timer@$T/pwm status okay
  fdtput -c "$W" /soc/pin-controller@50002000/$G
  fdtput -c "$W" /soc/pin-controller@50002000/$G/pins
  fdtput -t x "$W" /soc/pin-controller@50002000/$G/pins pinmux "$@"
  fdtput -t x "$W" /soc/pin-controller@50002000/$G/pins slew-rate 0
  fdtput -t s "$W" /soc/pin-controller@50002000/$G/pins bias-disable ""
  fdtput -t s "$W" /soc/pin-controller@50002000/$G/pins drive-push-pull ""
  fdtput -t x "$W" /soc/pin-controller@50002000/$G phandle $PH
  fdtput -t x "$W" /soc/timer@$T/pwm pinctrl-0 $PH
  fdtput -t s "$W" /soc/timer@$T/pwm pinctrl-names default
}

unlock 40002000 tim4-pwm-ninja-0 0x75 0x3d03 0x3e03
unlock 44001000 tim8-pwm-ninja-0 0x76 0x8504 0x8604 0x8704
unlock 40001000 tim3-pwm-ninja-0 0x77 0x1503

dtc -I dtb -O dtb -o /dev/null "$W" 2>/dev/null || { echo "dtc validation FAILED"; exit 1; }
cp "$D" "$D.pre-pwm-unlock"
cp "$W" "$D"
sync
echo "installed (backup $D.pre-pwm-unlock) - now: systemctl reboot, and VERIFY it went down"
