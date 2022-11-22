#pragma once
#include <string.h>
#include <stdarg.h>
//#include <Arduino.h>
//#include <LibRobus.h>

#define SERIAL_PRINTF_BUFFER_SIZE 255
static char internal__SerialPrintfBuffer[SERIAL_PRINTF_BUFFER_SIZE];

#define SERIAL_PRINTF(format, ...) \
{ \
    sprintf(internal__SerialPrintfBuffer, format, ##__VA_ARGS__); \
    Serial.print(internal__SerialPrintfBuffer); \
}