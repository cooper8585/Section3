#include "mbed.h"
#include "LSM6DSLSensor.h"
#include <cmath> 

#define PI 3.141592

static DevI2C devI2c(PB_11, PB_10);
static LSM6DSLSensor acc_gyro(&devI2c, 0xD4, D4, D5); 

float computeAngle(int x, int y, int z) {
    
    float angle = atan2(y, sqrt(x * x + z * z)) * 180.0 / PI;
    return angle;
}

int main() {
    uint8_t id;
    int32_t axes[3];
    float res = 0;
    acc_gyro.init(NULL);

    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while(1) {
        acc_gyro.get_x_axes(axes);
        res = computeAngle(axes[0], axes[1], axes[2]);
        printf("LSM6DSL: %6d, %6d, %6d, %3.2f degrees\r\n", axes[0], axes[1], axes[2], res);

        thread_sleep_for(2000);
    }
}
