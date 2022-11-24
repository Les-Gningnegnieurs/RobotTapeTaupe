#define TEST_DEBUG_PRINT

#include "serial_printf.h"
#include "fonctionsTest.h"
#include "sensors.h"
#include "motion.h"
#include <Arduino.h>
#include <LibRobus.h>

int exempleFonction(int variable1, int variable2) {
    return variable1 * variable2;
}

void printSonarValues() {
    Serial.print("Sonnar 1:");
    Serial.print(SONAR_GetRange(0));
    Serial.print("Sonnar 2:");
    Serial.print(SONAR_GetRange(1));
    Serial.print("\n");
}

void bonk() {

    for (int i = 0; i < 4; i++) {
        if (getSensorProximity(i) >= SENSOR_PROXIMITY_THRESHOLD) {
            #ifdef SENSOR_DEBUG_PRINT
                SERIAL_PRINTF("Found object #%i", i);
            #endif
            rotate(30 - (20 * i));
            setServoAngle(130, SERVO_1);
            delay(300);
            setServoAngle(10, SERVO_1);
            rotate(-(30 - (20 * i)));
            delay(500);
        }
    }
}