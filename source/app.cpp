#include "mbed-drivers/mbed.h"

#define ASYNC 0

#if ASYNC
    #include "maxsonar-example/ultrasnoic_async.hpp"
#else
    #include "maxsonar-example/ultrasnoic_sync.hpp"
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
    ultrasnoic_distance_async_task_init(&terminated);
    minar::Scheduler::postCallback(ultrasnoic_distance_async_task);
#else
    ultrasnoic_distance_sync_task_init();
    minar::Scheduler::postCallback(ultrasnoic_distance_sync_task).period(minar::milliseconds(500));
#endif
    blinky_task = minar::Scheduler::postCallback(blinky).period(minar::milliseconds(1000)).getHandle(); // 1Hz
}
