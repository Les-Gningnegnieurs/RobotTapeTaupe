#pragma once

#define GAME_DEBUG_PRINT

#define THRESHOLD_SENSOR_1 300
#define THRESHOLD_SENSOR_2 300
#define THRESHOLD_SENSOR_3 300
#define THRESHOLD_SENSOR_4 300

#define ANGLE_TAUPE_1 30
#define ANGLE_TAUPE_2 15
#define ANGLE_TAUPE_3 -15
#define ANGLE_TAUPE_4 -30


#include "sensors.h"
#include "motion.h"
#include "serial_printf.h"
#include <Arduino.h>
#include <LibRobus.h>

void bonkV2();