#pragma once

#define GAME_DEBUG_PRINT

#define THRESHOLD_SENSOR_1 160
#define THRESHOLD_SENSOR_2 190
#define THRESHOLD_SENSOR_3 200
#define THRESHOLD_SENSOR_4 130

#define ANGLE_TAUPE_1 25
#define ANGLE_TAUPE_2 8
#define ANGLE_TAUPE_3 -8
#define ANGLE_TAUPE_4 -25


#include "sensors.h"
#include "motion.h"
#include "serial_printf.h"
#include <Arduino.h>
#include <LibRobus.h>

void bonkV2();