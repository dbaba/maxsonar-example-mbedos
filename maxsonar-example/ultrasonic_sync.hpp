#pragma once

#include "mbed-drivers/mbed.h"
#include "maxsonar-example/mb1242.hpp"

void ultrasonic_distance_sync_task_init(void);

void ultrasonic_distance_sync_task(void);
