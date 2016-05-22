#include "maxsonar-example/ultrasonic_async.hpp"

static bool* terminated;
static mbed::drivers::v2::I2C i2cAsyncBus(PB_9, PB_8);

static void ultrasonic_data_received(mbed::drivers::v2::I2CTransaction * t, uint32_t event) {
    if (event == I2C_EVENT_ERROR_NO_SLAVE) {
        printf("[ERROR] %s\r\n", "Sensor is disconnected!");
        *terminated = true;
        return;
    }
    if (event != I2C_EVENT_TRANSFER_COMPLETE) {
        minar::Scheduler::postCallback(ultrasonic_distance_async_task).delay(minar::milliseconds(500));
        return;
    }

    t->reset_current();
    uint8_t* data = (uint8_t*) t
        ->get_current() // get the first segment (the rx segment)
        ->get_buf();    // get the buffer pointer

    // compile the range integer from the two bytes received.
    uint16_t range = (data[0] << 8) + data[1];
    printf("Range = %d cm\r\n", range);
    minar::Scheduler::postCallback(ultrasonic_distance_async_task).delay(minar::milliseconds(500));
}

static void ultrasonic_read_data(void) {
    i2cAsyncBus.transfer_to(I2C_ADDR_ULTRASONIC)
        .rx(2)
        .on(I2C_EVENT_ALL, ultrasonic_data_received)
        .apply();
}

static void ultrasonic_cmd_sent(mbed::drivers::v2::I2CTransaction *, uint32_t event) {
    if (event == I2C_EVENT_ERROR_NO_SLAVE) {
        printf("[ERROR] %s\r\n", "Sensor is disconnected!");
        *terminated = true;
        return;
    }
    if (event != I2C_EVENT_TRANSFER_COMPLETE) {
        minar::Scheduler::postCallback(ultrasonic_distance_async_task).delay(minar::milliseconds(500));
        return;
    }

    minar::Scheduler::postCallback(ultrasonic_read_data).delay(minar::milliseconds(100));
}

void ultrasonic_distance_async_task(void) {
    // 0x51 (81) Take a range reading
    uint8_t cmd[] = { 0x00, 0x51 };
    i2cAsyncBus.transfer_to(I2C_ADDR_ULTRASONIC)
        .tx_ephemeral(cmd, 2)
        .on(I2C_EVENT_ALL, ultrasonic_cmd_sent)
        .apply();
}

void ultrasonic_distance_async_task_init(bool* terminated_) {
    i2cAsyncBus.frequency(400000);
    terminated = terminated_;
}
