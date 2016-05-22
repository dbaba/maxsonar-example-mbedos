#include "mbed-drivers/mbed.h"

Serial pc(SERIAL_TX, SERIAL_RX);

/* I2C1 port, I2C Bus 1 */
I2C i2c(PB_9, PB_8);

#define I2C_ADDR_ULTRASONIC (0x70 << 1) // 7-bit address and response identifier

static void blinky(void) {
    static DigitalOut led(LED1);
    led = !led;
}

static void read_distance(void) {
    // 0x51 (81) Take a range reading
    uint8_t cmd[] = { 0x00, 0x51 };
    i2c.write(I2C_ADDR_ULTRASONIC, (char *) cmd, 2);
    wait_ms(100);
    // Report the last range value
    // Read the two bytes from the sensor starting with the range high byte and Read the range low byte.
    uint8_t data[2];
    i2c.read(I2C_ADDR_ULTRASONIC, (char *) data, 2);
    // compile the range integer from the two bytes received.
    uint16_t range = (data[0] << 8) + data[1];
    pc.printf("Range = %d cm\r\n", range);
}

void app_start(int, char**) {
    pc.baud(115200);
    i2c.frequency(400000);
    minar::Scheduler::postCallback(read_distance).period(minar::milliseconds(500));
    minar::Scheduler::postCallback(blinky).period(minar::milliseconds(500));
}
