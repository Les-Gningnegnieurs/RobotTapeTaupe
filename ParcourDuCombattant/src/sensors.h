#pragma once

#define SENSOR_DEBUG_PRINT
#define SENSOR_PROXIMITY_THRESHOLD 200

#include <Arduino.h>
#include <Librobus.h>
#include "serial_printf.h"


int getSensorProximity(int id);