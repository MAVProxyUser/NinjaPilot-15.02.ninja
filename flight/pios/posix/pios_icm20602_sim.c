/**
 ******************************************************************************
 * @file       pios_icm20602_sim.c
 * @author     NinjaPilot, 2026
 * @brief      Simulated ICM-20602 for the SIM_WROOM target.
 *
 * The ESP32 Thing Plus runs the CC-style Attitude module, which drinks raw
 * int16 samples straight from the IMU driver's queue -- no UAVObject sits in
 * that path on hardware. In simulation the sensor data arrives the other way
 * around: the Gazebo bridge writes GyroSensor (deg/s) and AccelSensor (m/s^2)
 * UAVObjects over telemetry. This shim closes the gap: it subscribes to those
 * objects, packs each gyro update into the PIOS_SENSORS_3Axis_SensorsWithTemp
 * record the Attitude module expects (accel latched from the most recent
 * accel update -- the bridge sends accel on alternate ticks), and exposes the
 * standard driver interface under the PIOS_ICM20602_Driver name that
 * attitude.c's ATTITUDE_IMU_DRIVER macro resolves to on this branch.
 *
 * Scaling is the REAL board's, verbatim: board_hw_defs.c configures the
 * ICM-20602 for +/-2000 dps and +/-8g, so the hardware driver advertises
 * gyro 1/16.4 deg/s per LSB and accel g/4096 m/s^2 per LSB. The shim packs
 * with the inverse of those same factors, so attitude.c's scale math (and any
 * AccelGyroSettings calibration the user carries over) behaves identically to
 * hardware, exact to int16 quantization.
 * @see        The GNU Public License (GPL) Version 3
 *****************************************************************************/

#include "pios.h"

#ifdef PIOS_INCLUDE_ICM20602

#include <pios_icm20602.h>
#include <uavobjectmanager.h>
#include <pios_constants.h>
#include "gyrosensor.h"
#include "accelsensor.h"

/* Same record layout trick as the hardware driver: the flexible-array
 * header plus two Vector3i16 samples, sample[0]=accel, sample[1]=gyro. */
#define ICM_SIM_SENSOR_COUNT 2
#define ICM_SIM_DATA_SIZE    (sizeof(PIOS_SENSORS_3Axis_SensorsWithTemp) + sizeof(Vector3i16) * ICM_SIM_SENSOR_COUNT)
#define ICM_SIM_QUEUE_LEN    4

/* +/-2000 dps and +/-8g, matching board_hw_defs.c on the real board */
#define ICM_SIM_GYRO_SCALE   (1.0f / 16.4f)
#define ICM_SIM_ACCEL_SCALE  (PIOS_CONST_MKS_GRAV_ACCEL_F / 4096.0f)

static QueueHandle_t icm_sim_queue;
static PIOS_SENSORS_3Axis_SensorsWithTemp *icm_sim_data;
static volatile int16_t icm_sim_accel[3];

static int16_t icm_sim_clamp(float v)
{
    if (v > 32767.0f) {
        return 32767;
    }
    if (v < -32768.0f) {
        return -32768;
    }
    return (int16_t)v;
}

static void icm_sim_accel_cb(__attribute__((unused)) UAVObjEvent *ev)
{
    AccelSensorData d;

    AccelSensorGet(&d);
    icm_sim_accel[0] = icm_sim_clamp(d.x / ICM_SIM_ACCEL_SCALE);
    icm_sim_accel[1] = icm_sim_clamp(d.y / ICM_SIM_ACCEL_SCALE);
    icm_sim_accel[2] = icm_sim_clamp(d.z / ICM_SIM_ACCEL_SCALE);
}

static void icm_sim_gyro_cb(__attribute__((unused)) UAVObjEvent *ev)
{
    GyroSensorData d;

    if (!icm_sim_queue || !icm_sim_data) {
        return;
    }
    GyroSensorGet(&d);

    icm_sim_data->count       = ICM_SIM_SENSOR_COUNT;
    icm_sim_data->temperature = (int16_t)(d.temperature * 100.0f);
    icm_sim_data->sample[0].x = icm_sim_accel[0];
    icm_sim_data->sample[0].y = icm_sim_accel[1];
    icm_sim_data->sample[0].z = icm_sim_accel[2];
    icm_sim_data->sample[1].x = icm_sim_clamp(d.x / ICM_SIM_GYRO_SCALE);
    icm_sim_data->sample[1].y = icm_sim_clamp(d.y / ICM_SIM_GYRO_SCALE);
    icm_sim_data->sample[1].z = icm_sim_clamp(d.z / ICM_SIM_GYRO_SCALE);

    /* Drop-oldest: a fresh sample always beats blocking the event
     * dispatcher, and the attitude task averages whatever it drains. */
    if (xQueueSend(icm_sim_queue, icm_sim_data, 0) != pdTRUE) {
        static uint8_t scratch[ICM_SIM_DATA_SIZE];
        (void)xQueueReceive(icm_sim_queue, scratch, 0);
        (void)xQueueSend(icm_sim_queue, icm_sim_data, 0);
    }
}

static bool icm_sim_test(__attribute__((unused)) uintptr_t context)
{
    return true;
}

static QueueHandle_t icm_sim_get_queue(__attribute__((unused)) uintptr_t context)
{
    return icm_sim_queue;
}

static void icm_sim_get_scale(float *scales, uint8_t size,
                              __attribute__((unused)) uintptr_t context)
{
    PIOS_Assert(size >= 2);
    scales[0] = ICM_SIM_ACCEL_SCALE;
    scales[1] = ICM_SIM_GYRO_SCALE;
}

const PIOS_SENSORS_Driver PIOS_ICM20602_Driver = {
    .test      = icm_sim_test,
    .poll      = NULL,
    .fetch     = NULL,
    .reset     = NULL,
    .get_queue = icm_sim_get_queue,
    .get_scale = icm_sim_get_scale,
    .is_polled = false,
};

int32_t PIOS_ICM20602_SIM_Init(void)
{
    icm_sim_queue = xQueueCreate(ICM_SIM_QUEUE_LEN, ICM_SIM_DATA_SIZE);
    if (!icm_sim_queue) {
        return -1;
    }
    icm_sim_data = (PIOS_SENSORS_3Axis_SensorsWithTemp *)pios_malloc(ICM_SIM_DATA_SIZE);
    if (!icm_sim_data) {
        return -2;
    }

    GyroSensorInitialize();
    AccelSensorInitialize();
    GyroSensorConnectCallback(icm_sim_gyro_cb);
    AccelSensorConnectCallback(icm_sim_accel_cb);

    PIOS_SENSORS_Register(&PIOS_ICM20602_Driver,
                          PIOS_SENSORS_TYPE_3AXIS_GYRO_ACCEL, 0);
    return 0;
}

#endif /* PIOS_INCLUDE_ICM20602 */
