#pragma once

#include "mbed-drivers/mbed.h"
#include "mbed-drivers/v2/I2C.hpp"
#include "maxsonar-example/maxsonar.hpp"

void ultrasonic_distance_async_task_init(bool* terminated_);

void ultrasonic_distance_async_task(void);
