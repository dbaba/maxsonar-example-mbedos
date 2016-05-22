#include "mbed-drivers/mbed.h"

#define ASYNC 1

#if ASYNC
    #include "maxsonar-example/ultrasonic_async.hpp"
#else
    #include "maxsonar-example/ultrasonic_sync.hpp"
#endif

static bool terminated = false;
static minar::callback_handle_t blinky_task;
static DigitalOut led(LED1);
static void blinky(void) {
    if (terminated) {
        minar::Scheduler::cancelCallback(blinky_task);
        while (true) {
            led = !led;
            wait_ms(100);
        }
    } else {
        led = !led;
    }
}

void app_start(int, char**) {
#if ASYNC
    ultrasonic_distance_async_task_init(&terminated);
    minar::Scheduler::postCallback(ultrasonic_distance_async_task);
#else
    ultrasonic_distance_sync_task_init();
    minar::Scheduler::postCallback(ultrasonic_distance_sync_task).period(minar::milliseconds(500));
#endif
    blinky_task = minar::Scheduler::postCallback(blinky).period(minar::milliseconds(1000)).getHandle(); // 1Hz
}
