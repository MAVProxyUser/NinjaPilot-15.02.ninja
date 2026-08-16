/* Standalone harness: prove the hub against the REAL parts before the
 * firmware depends on it. Sanity-checks magnitudes, not just "numbers moved". */
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <pios_sensors_hub.h>
int main(void)
{
    if (PIOS_SENSORS_HUB_Init("/dev/i2c-3", "can0") != 0) return 1;
    for (int i = 0; i < 6; i++) {
        sleep(1);
        struct pios_sensors_hub_data d;
        if (!PIOS_SENSORS_HUB_Get(&d)) { printf("  seqlock starved\n"); continue; }
        float ga = sqrtf(d.accel_mss[0]*d.accel_mss[0] + d.accel_mss[1]*d.accel_mss[1]
                       + d.accel_mss[2]*d.accel_mss[2]);
        float mg = sqrtf(d.mag_ga[0]*d.mag_ga[0] + d.mag_ga[1]*d.mag_ga[1]
                       + d.mag_ga[2]*d.mag_ga[2]);
        printf("  gyro %+7.2f %+7.2f %+7.2f dps | accel |a|=%5.2f m/s2 (%.3f g)"
               " | baro %8.1f Pa %4.1fC | mag |B|=%.4f Ga (%.1f uT) n%d\n",
               d.gyro_dps[0], d.gyro_dps[1], d.gyro_dps[2], ga, ga/9.80665f,
               d.press_pa, d.baro_temp_c, mg, mg*100.0f, d.mag_node);
        printf("     counts imu=%u baro=%u mag=%u   errors imu=%u baro=%u\n",
               d.imu_count, d.baro_count, d.mag_count, d.imu_errors, d.baro_errors);
    }
    PIOS_SENSORS_HUB_Stop();
    return 0;
}
