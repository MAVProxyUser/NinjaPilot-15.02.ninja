/**
 ******************************************************************************
 * @file       pios_board.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2026.
 * @brief      Board initialisation of the CubePilot Cube Purple (FMUv3)
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

#include "inc/openpilot.h"
#include <pios_board_info.h>
#include <uavobjectsinit.h>
#include <hwsettings.h>
#include <manualcontrolsettings.h>
#include <gcsreceiver.h>
#include <taskinfo.h>
#ifdef PIOS_INCLUDE_INSTRUMENTATION
#include <pios_instrumentation.h>
#endif
#if defined(PIOS_INCLUDE_FLASH_FRAM)
#include <pios_flash_fram.h>
#endif
#if defined(PIOS_INCLUDE_IOMCU)
#include <pios_iomcu.h>
#endif

/*
 * Pull in the board-specific static HW definitions.
 * Including .c files is a bit ugly but this allows all of
 * the HW definitions to be const and static to limit their
 * scope.
 *
 * NOTE: THIS IS THE ONLY PLACE THAT SHOULD EVER INCLUDE THIS FILE
 */
#include "../board_hw_defs.c"

#if defined(PIOS_INCLUDE_ADC)
#include <pios_adc_priv.h>
void PIOS_ADC_DMC_irq_handler(void);
void DMA2_Stream4_IRQHandler(void) __attribute__((alias("PIOS_ADC_DMC_irq_handler")));
struct pios_adc_cfg pios_adc_cfg = {
    .adc_dev = ADC1,
    .dma     = {
        .irq                                       = {
            .flags = (DMA_FLAG_TCIF4 | DMA_FLAG_TEIF4 | DMA_FLAG_HTIF4),
            .init  = {
                .NVIC_IRQChannel    = DMA2_Stream4_IRQn,
                .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_LOW,
                .NVIC_IRQChannelSubPriority        = 0,
                .NVIC_IRQChannelCmd = ENABLE,
            },
        },
        .rx                                        = {
            .channel = DMA2_Stream4,
            .init    = {
                .DMA_Channel                       = DMA_Channel_0,
            },
        }
    },
    .half_flag = DMA_IT_HTIF4,
    .full_flag = DMA_IT_TCIF4,
};
void PIOS_ADC_DMC_irq_handler(void)
{
    /* Call into the generic code to handle the IRQ for this specific device */
    PIOS_ADC_DMA_Handler();
}
#endif /* if defined(PIOS_INCLUDE_ADC) */

#if defined(PIOS_INCLUDE_MS5611_SPI)
#include "pios_ms5611.h"
static const struct pios_ms5611_cfg pios_ms5611_cfg = {
    .oversampling = MS5611_OSR_512,
};
#endif /* PIOS_INCLUDE_MS5611_SPI */

#if defined(PIOS_INCLUDE_INVENSENSE)
#include "pios_invensense.h"
static pios_invensense_t pios_imu_id;

static bool PIOS_IMU_IRQHandler(void)
{
    return PIOS_INVENSENSE_IRQHandler(pios_imu_id);
}

/* Data ready on PD15.  Below the IO co-processor's UART interrupt: this
 * handler polls a ~20 us SPI read, during which 1.5 Mbaud bytes must still
 * be collected. */
static const struct pios_exti_cfg pios_exti_imu_cfg __exti_config = {
    .vector = PIOS_IMU_IRQHandler,
    .line   = EXTI_Line15,
    .pin    = {
        .gpio = GPIOD,
        .init = {
            .GPIO_Pin   = GPIO_Pin_15,
            .GPIO_Speed = GPIO_Speed_100MHz,
            .GPIO_Mode  = GPIO_Mode_IN,
            .GPIO_OType = GPIO_OType_OD,
            .GPIO_PuPd  = GPIO_PuPd_NOPULL,
        },
    },
    .irq                                       = {
        .init                                  = {
            .NVIC_IRQChannel    = EXTI15_10_IRQn,
            .NVIC_IRQChannelPreemptionPriority = PIOS_IRQ_PRIO_MID,
            .NVIC_IRQChannelSubPriority        = 0,
            .NVIC_IRQChannelCmd = ENABLE,
        },
    },
    .exti                                      = {
        .init                                  = {
            .EXTI_Line    = EXTI_Line15, // matches above GPIO pin
            .EXTI_Mode    = EXTI_Mode_Interrupt,
            .EXTI_Trigger = EXTI_Trigger_Rising,
            .EXTI_LineCmd = ENABLE,
        },
    },
};

/*
 * MPU9250: 1 kHz internal rate halved to 500 Hz, 184 Hz low-pass, 2000 deg/s
 * and 8 g.  TOP_90DEG is ArduPilot's YAW_270 for this board composed with
 * its driver's own axis swap (rest: accel z = -9.8).  The AK8963 behind the
 * part's I2C master is brought up too.
 */
static const struct pios_invensense_cfg pios_invensense_cfg = {
    .exti_cfg       = &pios_exti_imu_cfg,
    .type           = PIOS_INVENSENSE_MPU9250,
    .smpl_rate_div  = 1,
    .int_cfg        = PIOS_INVENSENSE_INT_CLR_ANYRD,
    .int_en         = PIOS_INVENSENSE_INTEN_DATA_RDY,
    .user_ctl       = PIOS_INVENSENSE_USERCTL_DIS_I2C,
    .pwr_mgmt_clk   = PIOS_INVENSENSE_PWRMGMT_PLL_BEST,
    .mag_ak8963     = true,
    .accel_range    = PIOS_INVENSENSE_ACCEL_8G,
    .gyro_range     = PIOS_INVENSENSE_SCALE_2000_DEG,
    .filter         = PIOS_INVENSENSE_LOWPASS_184_HZ,
    .orientation    = PIOS_INVENSENSE_TOP_90DEG,
    .slow_prescaler = SPI_BaudRatePrescaler_128,
    .fast_prescaler = SPI_BaudRatePrescaler_16,
};
#endif /* PIOS_INCLUDE_INVENSENSE */

/* One slot per selectable group, filled in below. */
uint32_t pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_NONE];

#define PIOS_COM_TELEM_RF_RX_BUF_LEN     512
#define PIOS_COM_TELEM_RF_TX_BUF_LEN     512

#define PIOS_COM_GPS_RX_BUF_LEN          128
#define PIOS_COM_GPS_TX_BUF_LEN          32

#define PIOS_COM_TELEM_USB_RX_BUF_LEN    65
#define PIOS_COM_TELEM_USB_TX_BUF_LEN    65

#define PIOS_COM_BRIDGE_RX_BUF_LEN       65
#define PIOS_COM_BRIDGE_TX_BUF_LEN       12

#define PIOS_COM_HKOSD_RX_BUF_LEN        22
#define PIOS_COM_HKOSD_TX_BUF_LEN        22

#define PIOS_COM_IOMCU_RX_BUF_LEN        128
#define PIOS_COM_IOMCU_TX_BUF_LEN        128

#if defined(PIOS_INCLUDE_DEBUG_CONSOLE)
#define PIOS_COM_DEBUGCONSOLE_TX_BUF_LEN 40
uint32_t pios_com_debug_id;
#endif /* PIOS_INCLUDE_DEBUG_CONSOLE */

uint32_t pios_com_gps_id       = 0;
uint32_t pios_com_telem_usb_id = 0;
uint32_t pios_com_telem_rf_id  = 0;
uint32_t pios_com_bridge_id    = 0;
uint32_t pios_com_hkosd_id     = 0;
uint32_t pios_com_vcp_id       = 0;
uint32_t pios_com_iomcu_id     = 0;
uint32_t pios_iomcu_id         = 0;

uintptr_t pios_uavo_settings_fs_id;
uintptr_t pios_user_fs_id;

/* What holds the settings, for whoever asks (the GCS' board description). */
const char *pios_cube_settings_store = "none";

/*
 * Setup a com port based on the passed cfg, driver and buffer sizes. tx size of -1 make the port rx only
 */
static void PIOS_Board_configure_com(const struct pios_usart_cfg *usart_port_cfg, size_t rx_buf_len, size_t tx_buf_len,
                                     const struct pios_com_driver *com_driver, uint32_t *pios_com_id)
{
    uint32_t pios_usart_id;

    if (PIOS_USART_Init(&pios_usart_id, usart_port_cfg)) {
        PIOS_Assert(0);
    }

    uint8_t *rx_buffer = (uint8_t *)pios_malloc(rx_buf_len);
    PIOS_Assert(rx_buffer);
    if (tx_buf_len != (size_t)-1) { // this is the case for rx/tx ports
        uint8_t *tx_buffer = (uint8_t *)pios_malloc(tx_buf_len);
        PIOS_Assert(tx_buffer);

        if (PIOS_COM_Init(pios_com_id, com_driver, pios_usart_id,
                          rx_buffer, rx_buf_len,
                          tx_buffer, tx_buf_len)) {
            PIOS_Assert(0);
        }
    } else { // rx only port
        if (PIOS_COM_Init(pios_com_id, com_driver, pios_usart_id,
                          rx_buffer, rx_buf_len,
                          NULL, 0)) {
            PIOS_Assert(0);
        }
    }
}

#if defined(PIOS_INCLUDE_PPM)
static void PIOS_Board_configure_ppm(const struct pios_ppm_cfg *ppm_cfg)
{
    uint32_t pios_ppm_id;

    PIOS_PPM_Init(&pios_ppm_id, ppm_cfg);

    uint32_t pios_ppm_rcvr_id;
    if (PIOS_RCVR_Init(&pios_ppm_rcvr_id, &pios_ppm_rcvr_driver, pios_ppm_id)) {
        PIOS_Assert(0);
    }
    pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_PPM] = pios_ppm_rcvr_id;
}
#endif /* PIOS_INCLUDE_PPM */

/*
 * Actuator outputs: ActuatorSettings.ChannelAddr 0-7 are MAIN OUT 1-8 through
 * the IO co-processor, 8-12 are AUX OUT 1-5 on this MCU's timers.
 * Bank 1 of the update rates also sets the MAIN OUT rate.
 */
bool PIOS_Board_ServoSet(uint8_t channel, uint16_t value)
{
#if defined(PIOS_INCLUDE_IOMCU)
    if (channel < PIOS_IOMCU_NUM_SERVOS) {
        if (pios_iomcu_id) {
            PIOS_IOMCU_ServoSet(pios_iomcu_id, channel, value);
        }
        return true;
    }
    PIOS_Servo_Set(channel - PIOS_IOMCU_NUM_SERVOS, value);
    return true;
#else
    (void)channel;
    (void)value;
    return false;
#endif
}

void PIOS_Board_ServoSetHz(const uint16_t *hz, uint8_t banks)
{
#if defined(PIOS_INCLUDE_IOMCU)
    if (pios_iomcu_id && banks > 0) {
        PIOS_IOMCU_ServoSetHz(pios_iomcu_id, hz[0]);
    }
#else
    (void)hz;
    (void)banks;
#endif
}

/*
 * Bring-up aid: CUBE_BOOT_STOP=N brings USB up as early as possible and halts
 * the init sequence at stage N with the LED blinking, so a board that does
 * not enumerate can be bisected without a console.  0 (default) = off.
 */
#ifndef CUBE_BOOT_STOP
#define CUBE_BOOT_STOP 0
#endif
#if CUBE_BOOT_STOP || defined(CUBE_MARKS)
/* Reset into the ArduPilot bootloader and make it stay there (RTC BKP0R
 * magic): the bootloader's own USB device appearing is the observable. */
static void cube_bl_reset(void) __attribute__((noreturn));
static void cube_bl_reset(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    PWR_BackupAccessCmd(ENABLE);
    RTC_WriteBackupRegister(RTC_BKP_DR0, 0xB0070001);
    NVIC_SystemReset();
    for (;;) {}
}
#endif
#if CUBE_BOOT_STOP
void CUBE_BootStage(uint32_t n)
{
    if (CUBE_BOOT_STOP == n) {
        cube_bl_reset();
    }
}
#define CUBE_STAGE(n) CUBE_BootStage(n)
#else
void CUBE_BootStage(__attribute__((unused)) uint32_t n) {}
#define CUBE_STAGE(n) do { } while (0)
#endif


/*
 * Bring-up aid #2: CUBE_MARKS.  Progress markers are single words programmed
 * to zero in the (erased) top of internal flash; the ArduPilot bootloader's
 * GET_CRC then reveals which were reached, without any working USB.
 */
#ifdef CUBE_MARKS
#define CUBE_MARK_BASE 0x080FFF00u
/* slot 26 = an event has been recorded; catchers stay quiet after that so a
 * boot loop cannot smear the record */
static bool cube_recorded(void)
{
    return *(volatile uint32_t *)(CUBE_MARK_BASE + 4u * 26u) == 0u;
}
void CUBE_Mark(uint32_t slot)
{
    if (slot >= 64) {
        return;
    }
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
    FLASH_ProgramWord(CUBE_MARK_BASE + 4u * slot, 0);
    FLASH_Lock();
}
void cube_fault_c(uint32_t *sp, uint32_t slot) __attribute__((used, noinline, noreturn));
void cube_fault_c(uint32_t *sp, uint32_t slot)
{
    uint32_t pc  = sp[6];
    uint32_t off = (pc - 0x08004000u) >> 1;
    if (cube_recorded()) { for (;;) {} }
    CUBE_Mark(26);
    CUBE_Mark(slot);
    for (uint32_t j = 0; j < 19; j++) {
        if (off & (1u << j)) {
            CUBE_Mark(40 + j);
        }
    }
    cube_bl_reset(); /* park in the bootloader: the marks then describe exactly one event */
}
#define CUBE_FAULT(name, slot) \
    void name(void) __attribute__((naked)); \
    void name(void) { __asm volatile ("tst lr, #4\n\t" "ite eq\n\t" "mrseq r0, msp\n\t" "mrsne r0, psp\n\t" "mov r1, #" #slot "\n\t" "b cube_fault_c"); }
CUBE_FAULT(HardFault_Handler, 30)
CUBE_FAULT(MemManage_Handler, 29)
CUBE_FAULT(BusFault_Handler, 29)
CUBE_FAULT(UsageFault_Handler, 29)
#define CUBE_MARK(n) CUBE_Mark(n)
/* configASSERT reporter (CUBE_ASSERTS): slot 27 = an assert fired, file class in
 * slots 59..60 (0 other, 1 list.c, 2 tasks.c, 3 queue.c), line in slots 40..56,
 * slot 57 = fired from an exception handler; then wait for the watchdog. */
void CUBE_AssertHook(const char *file, int line)
{
    static bool done;
    if (done) {
        for (;;) {}
    }
    done = true;
    const char *b = file;
    for (const char *p = file; *p; p++) {
        if (*p == '/') { b = p + 1; }
    }
    uint32_t cls = 0;
    if (b[0] == 'l' && b[1] == 'i') { cls = 1; } else if (b[0] == 't' && b[1] == 'a') { cls = 2; } else if (b[0] == 'q') { cls = 3; }
    CUBE_Mark(27);
    for (uint32_t j = 0; j < 17; j++) {
        if ((uint32_t)line & (1u << j)) { CUBE_Mark(40 + j); }
    }
    for (uint32_t j = 0; j < 2; j++) {
        if (cls & (1u << j)) { CUBE_Mark(59 + j); }
    }
    if (__get_IPSR() != 0) { CUBE_Mark(57); }
    cube_bl_reset();
}
/* Double-insertion catcher (list.c hook): owner task name chars 0,1,last in
 * slots 40..57, slot 58 = re-inserted into the same list, slot 30 = capture. */
void CUBE_ListHook(void *item, void *list, void *ra)
{
    static bool done;
    (void)ra;
    if (done || xTaskGetTickCount() < 3000) {
        return;
    }
    done = true;
    ListItem_t *it = (ListItem_t *)item;
    void *owner = it->pvOwner;
    uint32_t enc = 0;
    if (owner && ((uint32_t)owner >= 0x10000000u) && ((uint32_t)owner < 0x20030000u)) {
        const char *n = pcTaskGetName((TaskHandle_t)owner);
        uint32_t len = strlen(n);
        enc = ((uint32_t)n[0] & 0x3F) | (((uint32_t)n[len > 1 ? 1 : 0] & 0x3F) << 6) | (((uint32_t)n[len ? len - 1 : 0] & 0x3F) << 12);
    }
    CUBE_Mark(30);
    for (uint32_t j = 0; j < 18; j++) {
        if (enc & (1u << j)) { CUBE_Mark(40 + j); }
    }
    if ((void *)it->pxContainer == list) { CUBE_Mark(58); }
}
/*
 * Stuck-tick catcher: TIM6 at NVIC priority 0 (above everything the kernel
 * masks) fires every 100 ms.  When the kernel tick has not advanced for two
 * periods the CPU is stuck with SysTick masked - a spinning interrupt
 * handler or a critical section - and the interrupted context's PC
 * (slots 40..58) and exception number (bits 0..4 -> 59..63, bit 5 -> 27,
 * bit 6 -> 30; 0 = thread mode) are recorded, slot 29 marks the capture.
 */
void cube_tim6_c(uint32_t *frame) __attribute__((used, noinline));
void cube_tim6_c(uint32_t *frame)
{
    static uint32_t last_tick, stuck;
    static bool done;
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    uint32_t t = xTaskGetTickCountFromISR();
    if (t == last_tick) {
        stuck++;
    } else {
        stuck = 0;
        last_tick = t;
    }
    if (stuck == 2 && !done && t > 3000) {
        done = true;
        uint32_t pc = frame[6];
        uint32_t ipsr = frame[7] & 0x1FFu;
        if (cube_recorded()) { return; }
        CUBE_Mark(26);
        CUBE_Mark(29);
        if (pc >= 0x08004000u && pc < 0x080C0000u) {
            uint32_t off = (pc - 0x08004000u) >> 1;
            for (uint32_t j = 0; j < 19; j++) {
                if (off & (1u << j)) { CUBE_Mark(40 + j); }
            }
        }
        for (uint32_t j = 0; j < 5; j++) {
            if (ipsr & (1u << j)) { CUBE_Mark(59 + j); }
        }
        if (ipsr & 0x20u) { CUBE_Mark(27); }
        if (ipsr & 0x40u) { CUBE_Mark(30); }
    }
}
void TIM6_DAC_IRQHandler(void) __attribute__((naked));
void TIM6_DAC_IRQHandler(void)
{
    __asm volatile ("tst lr, #4\n\t" "ite eq\n\t" "mrseq r0, msp\n\t" "mrsne r0, psp\n\t" "b cube_tim6_c");
}
static void cube_tim6_start(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    TIM_TimeBaseInitTypeDef tb;
    TIM_TimeBaseStructInit(&tb);
    tb.TIM_Prescaler     = (PIOS_PERIPHERAL_APB1_CLOCK / 10000) - 1; /* 10 kHz */
    tb.TIM_Period        = 1000 - 1;                                  /* 100 ms */
    tb.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &tb);
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    NVIC_InitTypeDef nv = { .NVIC_IRQChannel = TIM6_DAC_IRQn, .NVIC_IRQChannelPreemptionPriority = 0, .NVIC_IRQChannelSubPriority = 0, .NVIC_IRQChannelCmd = ENABLE };
    NVIC_Init(&nv);
    TIM_Cmd(TIM6, ENABLE);
}
/* Hang catcher: when the watchdog flags stop changing for 200 ms the board is
 * about to be reset by the IWDG.  Record which flags had been kicked
 * (slots 59..63), slot 29, and the interrupted task's PC (slots 40..58). */
void vApplicationTickHook(void)
{
    static uint16_t last_flags;
    static uint32_t same;
    static bool captured;
    uint16_t f = PIOS_WDG_GetActiveFlags();
    if (f == last_flags) {
        same++;
    } else {
        same = 0;
        last_flags = f;
    }
    /* arm 3 s after boot: nothing kicks the flags while the drivers initialise */
    if (same == 200 && !captured && xTaskGetTickCount() > 3000) {
        captured = true;
        uint32_t *frame = (uint32_t *)__get_PSP();
        uint32_t pc = frame[6];
        for (uint32_t i = 0; i < 5; i++) {
            if (f & (1u << i)) { CUBE_Mark(59 + i); }
        }
        CUBE_Mark(29);
        if (pc >= 0x08004000u && pc < 0x080C0000u) {
            uint32_t off = (pc - 0x08004000u) >> 1;
            for (uint32_t j = 0; j < 19; j++) {
                if (off & (1u << j)) { CUBE_Mark(40 + j); }
            }
        }
    }
}
#else
void CUBE_Mark(__attribute__((unused)) uint32_t slot) {}
#define CUBE_MARK(n) do { } while (0)
#endif

/**
 * PIOS_Board_Init()
 * initializes all the core subsystems on this specific hardware
 * called from System/openpilot.c
 */
void PIOS_Board_Init(void)
{
    const struct pios_board_info *bdinfo = &pios_board_info_blob;

#if defined(PIOS_INCLUDE_LED)
    const struct pios_gpio_cfg *led_cfg  = PIOS_BOARD_HW_DEFS_GetLedCfg(bdinfo->board_rev);
    PIOS_Assert(led_cfg);
    PIOS_LED_Init(led_cfg);
#endif /* PIOS_INCLUDE_LED */
    CUBE_STAGE(103);
    CUBE_MARK(1);
#if defined(CUBE_MARKS) && !defined(CUBE_NO_RESETCAUSE)
    {
        /* reset cause of this boot (slots 36..39) */
        uint32_t csr = RCC->CSR;
        /* The flags are sticky.  Record only boots that follow something
         * other than the power-up, so a later self-reset stands out, and
         * clear them so each boot reports its own cause. */
        if (csr & RCC_CSR_PORRSTF) {
            CUBE_Mark(39);
        } else {
            if (csr & RCC_CSR_WDGRSTF) { CUBE_Mark(36); }
            if (csr & RCC_CSR_SFTRSTF) { CUBE_Mark(37); }
            if (csr & RCC_CSR_PADRSTF) { CUBE_Mark(38); }
            if (csr & RCC_CSR_BORRSTF) { CUBE_Mark(27); }
        }
        RCC_ClearFlag();
    }
#endif
#if CUBE_BOOT_STOP == 104
    if (!pvPortMalloc(80)) { cube_bl_reset(); }
#endif

#ifdef PIOS_INCLUDE_INSTRUMENTATION
    PIOS_Instrumentation_Init(PIOS_INSTRUMENTATION_MAX_COUNTERS);
#endif

    CUBE_STAGE(1);
    CUBE_MARK(5);
    /* Power rails: sensors 3.3 V (high = on) and peripheral 5 V (low = on),
     * and every SPI chip select this firmware does not drive parked high. */
    GPIO_SetBits(pios_cube_vdd_sensors_en.gpio, pios_cube_vdd_sensors_en.init.GPIO_Pin);
    GPIO_Init(pios_cube_vdd_sensors_en.gpio, (GPIO_InitTypeDef *)&pios_cube_vdd_sensors_en.init);
    GPIO_ResetBits(pios_cube_vdd_periph_en_n.gpio, pios_cube_vdd_periph_en_n.init.GPIO_Pin);
    GPIO_Init(pios_cube_vdd_periph_en_n.gpio, (GPIO_InitTypeDef *)&pios_cube_vdd_periph_en_n.init);
    for (uint32_t i = 0; i < pios_cube_parked_cs_count; i++) {
        GPIO_SetBits(pios_cube_parked_cs[i].gpio, pios_cube_parked_cs[i].init.GPIO_Pin);
        GPIO_Init(pios_cube_parked_cs[i].gpio, (GPIO_InitTypeDef *)&pios_cube_parked_cs[i].init);
    }

    CUBE_STAGE(2);
    CUBE_MARK(6);
    /* Set up the SPI interfaces to the sensors and the FRAM */
    if (PIOS_SPI_Init(&pios_spi_sensors_id, &pios_spi_sensors_cfg)) {
        PIOS_DEBUG_Assert(0);
    }
    CUBE_MARK(14);
    if (PIOS_SPI_Init(&pios_spi_fram_id, &pios_spi_fram_cfg)) {
        PIOS_DEBUG_Assert(0);
    }
    CUBE_MARK(15);

    CUBE_STAGE(3);
    CUBE_MARK(7);
#if defined(PIOS_INCLUDE_FLASH)
    bool fs_mounted = false;
#if defined(PIOS_INCLUDE_FLASH_FRAM)
    {
        uintptr_t fram_id;
        if (PIOS_Flash_Fram_Init(&fram_id, pios_spi_fram_id, CUBE_SPI2_SLAVE_FRAM, CUBE_FRAM_SECTOR) == 0) {
            uint32_t size = PIOS_Flash_Fram_Size(fram_id);
            flashfs_fram_cfg.total_fs_size = size;
            flashfs_fram_cfg.arena_size    = size / 2;
            if (PIOS_FLASHFS_Logfs_Init(&pios_uavo_settings_fs_id, &flashfs_fram_cfg, &pios_fram_flash_driver, fram_id) == 0) {
                fs_mounted = true;
                pios_cube_settings_store = PIOS_Flash_Fram_Name(fram_id);
            }
        }
    }
#endif /* PIOS_INCLUDE_FLASH_FRAM */
    if (!fs_mounted) {
        uintptr_t flash_id;
        if (PIOS_Flash_Internal_Init(&flash_id, &flash_internal_cfg)) {
            PIOS_DEBUG_Assert(0);
        }
        if (PIOS_FLASHFS_Logfs_Init(&pios_uavo_settings_fs_id, &flashfs_internal_cfg, &pios_internal_flash_driver, flash_id)) {
            PIOS_DEBUG_Assert(0);
        }
        pios_cube_settings_store = "internal-flash";
    }
#endif /* PIOS_INCLUDE_FLASH */

    CUBE_STAGE(4);
    CUBE_MARK(8);
#if defined(PIOS_INCLUDE_RTC)
    PIOS_RTC_Init(&pios_rtc_main_cfg);
#endif

    /* IAP System Setup */
    PIOS_IAP_Init();
    // check for safe mode commands from gcs
    if (PIOS_IAP_ReadBootCmd(0) == PIOS_IAP_CLEAR_FLASH_CMD_0 &&
        PIOS_IAP_ReadBootCmd(1) == PIOS_IAP_CLEAR_FLASH_CMD_1 &&
        PIOS_IAP_ReadBootCmd(2) == PIOS_IAP_CLEAR_FLASH_CMD_2) {
        PIOS_FLASHFS_Format(pios_uavo_settings_fs_id);
        PIOS_IAP_WriteBootCmd(0, 0);
        PIOS_IAP_WriteBootCmd(1, 0);
        PIOS_IAP_WriteBootCmd(2, 0);
    }

    CUBE_STAGE(5);
    CUBE_MARK(9);
#ifdef PIOS_INCLUDE_WDG
    PIOS_WDG_Init();
#endif
#if defined(CUBE_MARKS) && defined(PIOS_INCLUDE_WDG)
    {
        /* which watchdog flags had been kicked when the previous run died (slots 59..63) */
        uint16_t f = PIOS_WDG_GetBootupFlags();
        for (uint32_t i = 0; i < 5; i++) {
            if (f & (1u << i)) { CUBE_Mark(59 + i); }
        }
    }
#endif

    CUBE_STAGE(6);
    CUBE_MARK(10);
    /* Initialize the task monitor */
    if (PIOS_TASK_MONITOR_Initialize(TASKINFO_RUNNING_NUMELEM)) {
        PIOS_Assert(0);
    }

    /* Initialize the delayed callback library */
    PIOS_CALLBACKSCHEDULER_Initialize();

    /* Initialize UAVObject libraries */
    EventDispatcherInitialize();
    UAVObjInitialize();

    CUBE_STAGE(7);
    CUBE_MARK(11);
    HwSettingsInitialize();

    /* Initialize the alarms library */
    AlarmsInitialize();

    CUBE_STAGE(8);
    CUBE_MARK(12);
    PIOS_TIM_InitClock(&tim_1_cfg);
    PIOS_TIM_InitClock(&tim_4_cfg);

    uint16_t boot_count = PIOS_IAP_ReadBootCount();
    if (boot_count < 3) {
        PIOS_IAP_WriteBootCount(++boot_count);
        AlarmsClear(SYSTEMALARMS_ALARM_BOOTFAULT);
    } else {
        /* Too many failed boot attempts, force hwsettings to defaults */
        HwSettingsSetDefaults(HwSettingsHandle(), 0);
        AlarmsSet(SYSTEMALARMS_ALARM_BOOTFAULT, SYSTEMALARMS_ALARM_CRITICAL);
    }

    CUBE_STAGE(9);
    CUBE_MARK(13);
#if defined(PIOS_INCLUDE_USB)
    /* Initialize board specific USB data */
    PIOS_USB_BOARD_DATA_Init();

    /* Flags to determine if various USB interfaces are advertised */
    bool usb_hid_present = false;
    bool usb_cdc_present = false;

#if defined(PIOS_INCLUDE_USB_CDC)
    if (PIOS_USB_DESC_HID_CDC_Init()) {
        PIOS_Assert(0);
    }
    usb_hid_present = true;
    usb_cdc_present = true;
#else
    if (PIOS_USB_DESC_HID_ONLY_Init()) {
        PIOS_Assert(0);
    }
    usb_hid_present = true;
#endif

    uint32_t pios_usb_id;
    PIOS_USB_Init(&pios_usb_id, PIOS_BOARD_HW_DEFS_GetUsbCfg(bdinfo->board_rev));

#if defined(PIOS_INCLUDE_USB_CDC)

    uint8_t hwsettings_usb_vcpport;
    /* Configure the USB VCP port */
    HwSettingsUSB_VCPPortGet(&hwsettings_usb_vcpport);

    if (!usb_cdc_present) {
        /* Force VCP port function to disabled if we haven't advertised VCP in our USB descriptor */
        hwsettings_usb_vcpport = HWSETTINGS_USB_VCPPORT_DISABLED;
    }

    uint32_t pios_usb_cdc_id;
    if (PIOS_USB_CDC_Init(&pios_usb_cdc_id, &pios_usb_cdc_cfg, pios_usb_id)) {
        PIOS_Assert(0);
    }

    uint32_t pios_usb_hid_id;
    if (PIOS_USB_HID_Init(&pios_usb_hid_id, &pios_usb_hid_cfg, pios_usb_id)) {
        PIOS_Assert(0);
    }

    switch (hwsettings_usb_vcpport) {
    case HWSETTINGS_USB_VCPPORT_DISABLED:
        break;
    case HWSETTINGS_USB_VCPPORT_USBTELEMETRY:
#if defined(PIOS_INCLUDE_COM)
        {
            uint8_t *rx_buffer = (uint8_t *)pios_malloc(PIOS_COM_TELEM_USB_RX_BUF_LEN);
            uint8_t *tx_buffer = (uint8_t *)pios_malloc(PIOS_COM_TELEM_USB_TX_BUF_LEN);
            PIOS_Assert(rx_buffer);
            PIOS_Assert(tx_buffer);
            if (PIOS_COM_Init(&pios_com_telem_usb_id, &pios_usb_cdc_com_driver, pios_usb_cdc_id,
                              rx_buffer, PIOS_COM_TELEM_USB_RX_BUF_LEN,
                              tx_buffer, PIOS_COM_TELEM_USB_TX_BUF_LEN)) {
                PIOS_Assert(0);
            }
        }
#endif /* PIOS_INCLUDE_COM */
        break;
    case HWSETTINGS_USB_VCPPORT_COMBRIDGE:
#if defined(PIOS_INCLUDE_COM)
        {
            uint8_t *rx_buffer = (uint8_t *)pios_malloc(PIOS_COM_BRIDGE_RX_BUF_LEN);
            uint8_t *tx_buffer = (uint8_t *)pios_malloc(PIOS_COM_BRIDGE_TX_BUF_LEN);
            PIOS_Assert(rx_buffer);
            PIOS_Assert(tx_buffer);
            if (PIOS_COM_Init(&pios_com_vcp_id, &pios_usb_cdc_com_driver, pios_usb_cdc_id,
                              rx_buffer, PIOS_COM_BRIDGE_RX_BUF_LEN,
                              tx_buffer, PIOS_COM_BRIDGE_TX_BUF_LEN)) {
                PIOS_Assert(0);
            }
        }
#endif /* PIOS_INCLUDE_COM */
        break;
    case HWSETTINGS_USB_VCPPORT_DEBUGCONSOLE:
#if defined(PIOS_INCLUDE_COM)
#if defined(PIOS_INCLUDE_DEBUG_CONSOLE)
        {
            uint8_t *tx_buffer = (uint8_t *)pios_malloc(PIOS_COM_DEBUGCONSOLE_TX_BUF_LEN);
            PIOS_Assert(tx_buffer);
            if (PIOS_COM_Init(&pios_com_debug_id, &pios_usb_cdc_com_driver, pios_usb_cdc_id,
                              NULL, 0,
                              tx_buffer, PIOS_COM_DEBUGCONSOLE_TX_BUF_LEN)) {
                PIOS_Assert(0);
            }
        }
#endif /* PIOS_INCLUDE_DEBUG_CONSOLE */
#endif /* PIOS_INCLUDE_COM */
        break;
    }
#endif /* PIOS_INCLUDE_USB_CDC */

#if defined(PIOS_INCLUDE_USB_HID)
    /* Configure the usb HID port */
    uint8_t hwsettings_usb_hidport;
    HwSettingsUSB_HIDPortGet(&hwsettings_usb_hidport);

    if (!usb_hid_present) {
        /* Force HID port function to disabled if we haven't advertised HID in our USB descriptor */
        hwsettings_usb_hidport = HWSETTINGS_USB_HIDPORT_DISABLED;
    }

#if !defined(PIOS_INCLUDE_USB_CDC)
    uint32_t pios_usb_hid_id;
    if (PIOS_USB_HID_Init(&pios_usb_hid_id, &pios_usb_hid_cfg, pios_usb_id)) {
        PIOS_Assert(0);
    }
#endif

    switch (hwsettings_usb_hidport) {
    case HWSETTINGS_USB_HIDPORT_DISABLED:
        break;
    case HWSETTINGS_USB_HIDPORT_USBTELEMETRY:
#if defined(PIOS_INCLUDE_COM)
        {
            uint8_t *rx_buffer = (uint8_t *)pios_malloc(PIOS_COM_TELEM_USB_RX_BUF_LEN);
            uint8_t *tx_buffer = (uint8_t *)pios_malloc(PIOS_COM_TELEM_USB_TX_BUF_LEN);
            PIOS_Assert(rx_buffer);
            PIOS_Assert(tx_buffer);
            if (PIOS_COM_Init(&pios_com_telem_usb_id, &pios_usb_hid_com_driver, pios_usb_hid_id,
                              rx_buffer, PIOS_COM_TELEM_USB_RX_BUF_LEN,
                              tx_buffer, PIOS_COM_TELEM_USB_TX_BUF_LEN)) {
                PIOS_Assert(0);
            }
        }
#endif /* PIOS_INCLUDE_COM */
        break;
    }

#endif /* PIOS_INCLUDE_USB_HID */

    if (usb_hid_present || usb_cdc_present) {
        PIOS_USBHOOK_Activate();
    }
#endif /* PIOS_INCLUDE_USB */

    /*
     * Serial ports, the "RV" (full size Revolution) set of HwSettings fits
     * the Cube's connectors:
     *   RV_TelemetryPort = TELEM1 (USART2)
     *   RV_AuxPort       = TELEM2 (USART3)
     *   RV_GPSPort       = GPS    (UART4)
     */
    uint8_t hwsettings_port;

    HwSettingsRV_TelemetryPortGet(&hwsettings_port);
    switch (hwsettings_port) {
    case HWSETTINGS_RV_TELEMETRYPORT_TELEMETRY:
        PIOS_Board_configure_com(&pios_usart_telem1_cfg, PIOS_COM_TELEM_RF_RX_BUF_LEN, PIOS_COM_TELEM_RF_TX_BUF_LEN, &pios_usart_com_driver, &pios_com_telem_rf_id);
        break;
    case HWSETTINGS_RV_TELEMETRYPORT_COMBRIDGE:
        PIOS_Board_configure_com(&pios_usart_telem1_cfg, PIOS_COM_BRIDGE_RX_BUF_LEN, PIOS_COM_BRIDGE_TX_BUF_LEN, &pios_usart_com_driver, &pios_com_bridge_id);
        break;
    default:
        break;
    }

    HwSettingsRV_AuxPortGet(&hwsettings_port);
    switch (hwsettings_port) {
    case HWSETTINGS_RV_AUXPORT_TELEMETRY:
        if (!pios_com_telem_rf_id) {
            PIOS_Board_configure_com(&pios_usart_telem2_cfg, PIOS_COM_TELEM_RF_RX_BUF_LEN, PIOS_COM_TELEM_RF_TX_BUF_LEN, &pios_usart_com_driver, &pios_com_telem_rf_id);
        }
        break;
    case HWSETTINGS_RV_AUXPORT_COMBRIDGE:
        if (!pios_com_bridge_id) {
            PIOS_Board_configure_com(&pios_usart_telem2_cfg, PIOS_COM_BRIDGE_RX_BUF_LEN, PIOS_COM_BRIDGE_TX_BUF_LEN, &pios_usart_com_driver, &pios_com_bridge_id);
        }
        break;
    case HWSETTINGS_RV_AUXPORT_OSDHK:
        PIOS_Board_configure_com(&pios_usart_telem2_cfg, PIOS_COM_HKOSD_RX_BUF_LEN, PIOS_COM_HKOSD_TX_BUF_LEN, &pios_usart_com_driver, &pios_com_hkosd_id);
        break;
    default:
        break;
    }

    HwSettingsRV_GPSPortGet(&hwsettings_port);
    switch (hwsettings_port) {
    case HWSETTINGS_RV_GPSPORT_GPS:
        PIOS_Board_configure_com(&pios_usart_gps_cfg, PIOS_COM_GPS_RX_BUF_LEN, PIOS_COM_GPS_TX_BUF_LEN, &pios_usart_com_driver, &pios_com_gps_id);
        break;
    case HWSETTINGS_RV_GPSPORT_TELEMETRY:
        if (!pios_com_telem_rf_id) {
            PIOS_Board_configure_com(&pios_usart_gps_cfg, PIOS_COM_TELEM_RF_RX_BUF_LEN, PIOS_COM_TELEM_RF_TX_BUF_LEN, &pios_usart_com_driver, &pios_com_telem_rf_id);
        }
        break;
    case HWSETTINGS_RV_GPSPORT_COMBRIDGE:
        if (!pios_com_bridge_id) {
            PIOS_Board_configure_com(&pios_usart_gps_cfg, PIOS_COM_BRIDGE_RX_BUF_LEN, PIOS_COM_BRIDGE_TX_BUF_LEN, &pios_usart_com_driver, &pios_com_bridge_id);
        }
        break;
    default:
        break;
    }

    /*
     * RC input.  The IO co-processor decodes whatever is on RC IN (PPM,
     * S.Bus, DSM) and serves it as the PWM, S.Bus and DSM groups; a PPM
     * stream on AUX OUT 6 is the PPM group.
     */
    HwSettingsRV_RcvrPortGet(&hwsettings_port);
#if defined(PIOS_INCLUDE_PPM)
    if (hwsettings_port == HWSETTINGS_RV_RCVRPORT_PPM || hwsettings_port == HWSETTINGS_RV_RCVRPORT_PPMOUTPUTS) {
        PIOS_Board_configure_ppm(&pios_ppm_cfg);
    }
#endif

#if defined(PIOS_INCLUDE_GCSRCVR)
    GCSReceiverInitialize();
    uint32_t pios_gcsrcvr_id;
    PIOS_GCSRCVR_Init(&pios_gcsrcvr_id);
    uint32_t pios_gcsrcvr_rcvr_id;
    if (PIOS_RCVR_Init(&pios_gcsrcvr_rcvr_id, &pios_gcsrcvr_rcvr_driver, pios_gcsrcvr_id)) {
        PIOS_Assert(0);
    }
    pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_GCS] = pios_gcsrcvr_rcvr_id;
#endif /* PIOS_INCLUDE_GCSRCVR */

#if defined(PIOS_INCLUDE_IOMCU)
    /* MAIN OUT 1-8, RC IN, safety switch.  Safety is forced off so the
     * outputs follow this firmware's own arming, as on every other board. */
    PIOS_Board_configure_com(&pios_usart_iomcu_cfg, PIOS_COM_IOMCU_RX_BUF_LEN, PIOS_COM_IOMCU_TX_BUF_LEN, &pios_usart_com_driver, &pios_com_iomcu_id);
    if (pios_com_iomcu_id && PIOS_IOMCU_Init(&pios_iomcu_id, pios_com_iomcu_id, true) == 0) {
        uint32_t pios_iomcu_rcvr_id;
        if (PIOS_RCVR_Init(&pios_iomcu_rcvr_id, &pios_iomcu_rcvr_driver, pios_iomcu_id) == 0) {
            if (hwsettings_port != HWSETTINGS_RV_RCVRPORT_DISABLED) {
                pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_PWM] = pios_iomcu_rcvr_id;
            }
            pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_SBUS] = pios_iomcu_rcvr_id;
            pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_DSMMAINPORT]  = pios_iomcu_rcvr_id;
            pios_rcvr_group_map[MANUALCONTROLSETTINGS_CHANNELGROUPS_DSMFLEXIPORT] = pios_iomcu_rcvr_id;
        }
    }
#endif /* PIOS_INCLUDE_IOMCU */

    /* AUX OUT 1-5 */
    PIOS_Servo_Init(&pios_servo_cfg_out);

#if defined(PIOS_INCLUDE_I2C)
    if (PIOS_I2C_Init(&pios_i2c_external_adapter_id, &pios_i2c_external_adapter_cfg)) {
        PIOS_DEBUG_Assert(0);
    }
    if (PIOS_I2C_Init(&pios_i2c_internal_adapter_id, &pios_i2c_internal_adapter_cfg)) {
        PIOS_DEBUG_Assert(0);
    }
#endif

    /* The MPU9250 needs ~100 ms after its rail comes up before it answers. */
    PIOS_DELAY_WaitmS(100);

#if defined(PIOS_INCLUDE_ADC)
    PIOS_ADC_Init(&pios_adc_cfg);
#endif

#if defined(PIOS_INCLUDE_INVENSENSE)
    if (PIOS_INVENSENSE_Init(&pios_imu_id, pios_spi_sensors_id, CUBE_SPI1_SLAVE_IMU, &pios_invensense_cfg) == 0) {
        PIOS_INVENSENSE_Register(pios_imu_id);
    }
#endif

#if defined(PIOS_INCLUDE_MS5611_SPI)
    PIOS_MS5611_SPI_Init(&pios_ms5611_cfg, pios_spi_sensors_id, CUBE_SPI1_SLAVE_MS5611);
    PIOS_MS5611_Register();
#endif
#ifdef CUBE_MARKS
    cube_tim6_start();
#endif
}

/**
 * @}
 * @}
 */
