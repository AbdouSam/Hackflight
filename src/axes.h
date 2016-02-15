typedef enum {
    X = 0,
    Y,
    Z
} sensor_axis_e;

typedef enum {
    ALIGN_DEFAULT = 0,                                      // driver-provided alignment
    CW0_DEG = 1,
    CW90_DEG = 2,
    CW180_DEG = 3,
    CW270_DEG = 4,
    CW0_DEG_FLIP = 5,
    CW90_DEG_FLIP = 6,
    CW180_DEG_FLIP = 7,
    CW270_DEG_FLIP = 8
} sensor_align_e;

typedef void (*sensorInitFuncPtr)(sensor_align_e align);   // sensor init prototype

typedef void (*sensorReadFuncPtr)(int16_t *data);          // sensor read and align prototype

typedef struct sensor_t {
    sensorInitFuncPtr init;                                 // initialize function
    sensorReadFuncPtr read;                                 // read 3 axis data function
    sensorReadFuncPtr temperature;                          // read temperature if available
    float scale;                                            // scalefactor (currently used for gyro only, todo for accel)
} sensor_t;

// Returns value of acc_1G
uint16_t mpuInit(sensor_t *acc, sensor_t *gyro, uint8_t lpf, int hwrev);

void alignSensors(int16_t *src, int16_t *dest, uint8_t rotation);
