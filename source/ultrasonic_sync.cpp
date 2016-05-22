#include "maxsonar-example/ultrasonic_sync.hpp"

static I2C i2cBus(PB_9, PB_8);

void ultrasonic_distance_sync_task_init(void) {
    i2cBus.frequency(400000);
}

void ultrasonic_distance_sync_task(void) {
    // 0x51 (81) Take a range reading
    uint8_t cmd[] = { 0x00, 0x51 };
    i2cBus.write(I2C_ADDR_ULTRASONIC, (char *) cmd, 2);
    wait_ms(100);
    // Report the last range value
    // Read the two bytes from the sensor starting with the range high byte and Read the range low byte.
    uint8_t data[2];
    i2cBus.read(I2C_ADDR_ULTRASONIC, (char *) data, 2);
    // compile the range integer from the two bytes received.
    uint16_t range = (data[0] << 8) + data[1];
    printf("Range = %d cm\r\n", range);
}
