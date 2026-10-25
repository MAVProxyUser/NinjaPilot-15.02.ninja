/**
 ******************************************************************************
 * @file       pios_servo.c
 * @author     NinjaPilot, 2026
 * @brief      ESP32 servo/ESC output via MCPWM.
 *
 * MCPWM is used rather than LEDC because PIOS_Servo_Update() is a coordinated
 * push -- all channels are meant to take their new value together -- and MCPWM
 * gives us that plus a clean 1us tick. LEDC would be simpler but updates each
 * channel whenever it feels like it.
 *
 * The original ESP32 has 2 MCPWM units x 3 timers x 2 generators, so six
 * outputs is the comfortable ceiling. That matches the channel count on the
 * reference wiring and is plenty for a quad.
 *
 * Timer resolution is set to 1MHz, so a comparator value is literally the
 * pulse width in microseconds and PIOS_Servo_Set() is a straight assignment.
 *
 * NOT IMPLEMENTED: DShot. RMT would do it well and it is a few hundred lines,
 * but PWM/OneShot is what a first bring-up needs. MODE is PWM only.
 * @see        The GNU Public License (GPL) Version 3
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "pios.h"

#ifdef PIOS_INCLUDE_SERVO

#include "driver/mcpwm_prelude.h"
#include "driver/ledc.h"

#define SERVO_TIMEBASE_HZ       1000000UL   /* 1 tick == 1us */
#define SERVO_DEFAULT_RATE_HZ   400
#define SERVO_GENERATORS_PER_TIMER 2

/* ---------------------------------------------------------------------------
 * Brushed backend.
 *
 * A coreless motor on a low-side MOSFET has no ESC to decode a pulse width --
 * the gate is either on or off and the motor sees the average. So this backend
 * drives LEDC at a fixed carrier and varies duty. 24 kHz is above hearing and
 * comfortably inside what these little MOSFETs switch cleanly; at 10-bit
 * resolution the LEDC divider works out to 80MHz/(1024*24k) = 3.26, which is
 * legal, and 1024 steps maps almost 1:1 onto the 0..1000 command range.
 *
 * The command unit is per mille of full throttle. That matches the actuator
 * endpoints this board ships with (min 0 / neutral 0 / max 1000), so a
 * disarmed board holds 0% duty and the motors are genuinely off -- not
 * "idling below the arming threshold" the way a servo-pulse ESC would be.
 * ------------------------------------------------------------------------- */
#define SERVO_BRUSHED_DEFAULT_HZ 24000UL
#define SERVO_BRUSHED_RES        LEDC_TIMER_10_BIT
#define SERVO_BRUSHED_MAX_DUTY   ((1u << 10) - 1u)
#define SERVO_BRUSHED_FULL_SCALE 1000u

/* Snap the last 1% at each end to fully off / fully on.
 *
 * A MOSFET is only cheap to drive when it is saturated or cut off; the
 * transition is where it dissipates. At a 24 kHz carrier the period is 41.7 us,
 * so a 0.1% command is a 42 ns gate pulse -- comparable to the IRLML6344's own
 * switching time, which means the part never fully enhances. It heats, and the
 * motor does not turn: all loss, no thrust. The same is true inverted at the
 * top, where a 99.9% command leaves a 42 ns off-notch that buys nothing and
 * costs a switching edge every cycle.
 *
 * Nothing is lost by rounding those away. 1% duty on a 720-size coreless motor
 * is far below breakaway torque, so the commands being discarded could not
 * have produced thrust anyway -- and the actuator endpoints already put the
 * disarmed state at exactly 0. esp-fc does the same thing on its brushed path
 * (EscDriverEsp8266.cpp: "do not generate brushed pulses if duty < ~0.2%",
 * "set brushed output hi if duty > ~99.8%"); this is a slightly wider band,
 * chosen from the switching time above rather than from a round number. */
#define SERVO_BRUSHED_DEADBAND   (SERVO_BRUSHED_FULL_SCALE / 100u)   /* 1% */

struct servo_chan {
    mcpwm_cmpr_handle_t comparator;
    mcpwm_gen_handle_t  generator;
    uint16_t            position_us;
    uint16_t            pending_us;
};

static struct servo_chan servo_chans[PIOS_ESP32_SERVO_MAX_CHANNELS];
static mcpwm_timer_handle_t servo_timers[PIOS_ESP32_SERVO_MAX_CHANNELS / SERVO_GENERATORS_PER_TIMER];
static uint8_t servo_num_chans;
static uint8_t servo_num_timers;
static uint16_t servo_rate_hz = SERVO_DEFAULT_RATE_HZ;
static bool servo_brushed;

static int32_t PIOS_ESP32_Servo_InitBrushed(const struct pios_esp32_servo_cfg *cfg)
{
    ledc_timer_config_t tcfg = {
        .speed_mode      = LEDC_LOW_SPEED_MODE,
        .duty_resolution = SERVO_BRUSHED_RES,
        .timer_num       = LEDC_TIMER_0,
        .freq_hz         = cfg->brushed_freq_hz ? cfg->brushed_freq_hz
                                                : SERVO_BRUSHED_DEFAULT_HZ,
        .clk_cfg         = LEDC_AUTO_CLK,
    };

    if (ledc_timer_config(&tcfg) != ESP_OK) {
        return -1;
    }

    for (uint8_t ch = 0; ch < cfg->num_pins; ch++) {
        ledc_channel_config_t ccfg = {
            .gpio_num   = cfg->pins[ch],
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .channel    = (ledc_channel_t)ch,
            .timer_sel  = LEDC_TIMER_0,
            .duty       = 0,    /* motors off from the first instruction */
            .hpoint     = 0,
        };

        if (ledc_channel_config(&ccfg) != ESP_OK) {
            return -1;
        }
    }

    servo_num_chans  = cfg->num_pins;
    servo_num_timers = 1;
    servo_brushed    = true;

    return 0;
}

int32_t PIOS_ESP32_Servo_Init(const struct pios_esp32_servo_cfg *cfg)
{
    PIOS_Assert(cfg);
    PIOS_Assert(cfg->num_pins <= PIOS_ESP32_SERVO_MAX_CHANNELS);

    if (cfg->brushed) {
        return PIOS_ESP32_Servo_InitBrushed(cfg);
    }

    servo_rate_hz = cfg->default_rate_hz ? cfg->default_rate_hz : SERVO_DEFAULT_RATE_HZ;

    const uint32_t period_ticks = SERVO_TIMEBASE_HZ / servo_rate_hz;

    servo_num_chans  = cfg->num_pins;
    servo_num_timers = (cfg->num_pins + SERVO_GENERATORS_PER_TIMER - 1) /
                       SERVO_GENERATORS_PER_TIMER;

    for (uint8_t t = 0; t < servo_num_timers; t++) {
        mcpwm_timer_config_t tcfg = {
            .group_id      = t / 3,      /* 3 timers per MCPWM group */
            .clk_src       = MCPWM_TIMER_CLK_SRC_DEFAULT,
            .resolution_hz = SERVO_TIMEBASE_HZ,
            .period_ticks  = period_ticks,
            .count_mode    = MCPWM_TIMER_COUNT_MODE_UP,
        };
        if (mcpwm_new_timer(&tcfg, &servo_timers[t]) != ESP_OK) {
            return -1;
        }

        mcpwm_oper_handle_t oper;
        mcpwm_operator_config_t ocfg = { .group_id = tcfg.group_id };

        if (mcpwm_new_operator(&ocfg, &oper) != ESP_OK) {
            return -1;
        }
        if (mcpwm_operator_connect_timer(oper, servo_timers[t]) != ESP_OK) {
            return -1;
        }

        for (uint8_t g = 0; g < SERVO_GENERATORS_PER_TIMER; g++) {
            uint8_t ch = t * SERVO_GENERATORS_PER_TIMER + g;

            if (ch >= cfg->num_pins) {
                break;
            }

            mcpwm_comparator_config_t ccfg = {
                .flags.update_cmp_on_tez = true,
            };
            if (mcpwm_new_comparator(oper, &ccfg, &servo_chans[ch].comparator) != ESP_OK) {
                return -1;
            }

            mcpwm_generator_config_t gcfg = { .gen_gpio_num = cfg->pins[ch] };
            if (mcpwm_new_generator(oper, &gcfg, &servo_chans[ch].generator) != ESP_OK) {
                return -1;
            }

            /* High at counter zero, low when the comparator matches. */
            mcpwm_generator_set_action_on_timer_event(servo_chans[ch].generator,
                MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP,
                                             MCPWM_TIMER_EVENT_EMPTY,
                                             MCPWM_GEN_ACTION_HIGH));
            mcpwm_generator_set_action_on_compare_event(servo_chans[ch].generator,
                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP,
                                               servo_chans[ch].comparator,
                                               MCPWM_GEN_ACTION_LOW));

            /* Start at zero width, not at 1000us. An ESC should see no
             * pulse at all until the flight code has actually decided what
             * to output. */
            servo_chans[ch].position_us = 0;
            servo_chans[ch].pending_us  = 0;
            mcpwm_comparator_set_compare_value(servo_chans[ch].comparator, 0);
        }

        if (mcpwm_timer_enable(servo_timers[t]) != ESP_OK) {
            return -1;
        }
        if (mcpwm_timer_start_stop(servo_timers[t], MCPWM_TIMER_START_NO_STOP) != ESP_OK) {
            return -1;
        }
    }

    return 0;
}

void PIOS_Servo_SetHz(const uint16_t *speeds, __attribute__((unused)) const uint32_t *clock,
                      uint8_t banks)
{
    if (!speeds || banks == 0) {
        return;
    }

    /* One rate for every bank: the channels share MCPWM timers in fixed
     * pairs, so per-bank rates would need a different timer assignment than
     * the one built in Init(). Take bank 0's rate and apply it globally. */
    uint16_t rate = speeds[0];

    if (rate == 0) {
        return;
    }
    if (servo_brushed) {
        /* The LEDC carrier has nothing to do with the actuator update rate;
         * the mixer's "PWM rate" is meaningless for a MOSFET gate. */
        return;
    }
    servo_rate_hz = rate;

    const uint32_t period_ticks = SERVO_TIMEBASE_HZ / rate;

    for (uint8_t t = 0; t < servo_num_timers; t++) {
        mcpwm_timer_set_period(servo_timers[t], period_ticks);
    }
}

void PIOS_Servo_Set(uint8_t servo, uint16_t position)
{
    if (servo >= servo_num_chans) {
        return;
    }
    /* Staged, not applied: PIOS_Servo_Update() is the commit point. */
    servo_chans[servo].pending_us = position;
}

void PIOS_Servo_Update(void)
{
    for (uint8_t ch = 0; ch < servo_num_chans; ch++) {
        if (servo_chans[ch].pending_us == servo_chans[ch].position_us) {
            continue;
        }
        servo_chans[ch].position_us = servo_chans[ch].pending_us;

        if (servo_brushed) {
            uint32_t cmd = servo_chans[ch].position_us;
            uint32_t duty;

            if (cmd > SERVO_BRUSHED_FULL_SCALE) {
                cmd = SERVO_BRUSHED_FULL_SCALE;
            }

            if (cmd <= SERVO_BRUSHED_DEADBAND) {
                duty = 0;                          /* gate hard off */
            } else if (cmd >= SERVO_BRUSHED_FULL_SCALE - SERVO_BRUSHED_DEADBAND) {
                duty = SERVO_BRUSHED_MAX_DUTY;     /* gate hard on  */
            } else {
                duty = (cmd * SERVO_BRUSHED_MAX_DUTY) / SERVO_BRUSHED_FULL_SCALE;
            }

            ledc_set_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)ch, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, (ledc_channel_t)ch);
            continue;
        }
        /* update_cmp_on_tez means this lands at the next period boundary,
         * so all channels move together and no pulse is ever truncated
         * mid-flight. */
        mcpwm_comparator_set_compare_value(servo_chans[ch].comparator,
                                           servo_chans[ch].position_us);
    }
}

void PIOS_Servo_SetBankMode(__attribute__((unused)) uint8_t bank,
                            __attribute__((unused)) uint8_t mode)
{
    /* Only PWM output mode exists on this backend. */
}

uint8_t PIOS_Servo_GetPinBank(uint8_t pin)
{
    /* Channels are paired onto timers, and a "bank" in PiOS terms is a set
     * of pins that must share a rate. Brushed channels all hang off one LEDC
     * timer and have no meaningful rate, so they are one bank. */
    if (servo_brushed) {
        return 0;
    }
    return pin / SERVO_GENERATORS_PER_TIMER;
}

#endif /* PIOS_INCLUDE_SERVO */
