

#define threshold1 200
#define threshold1 100
#define threshold3 280
#define threshold4 250

#include "serial_printf.h"
#include "fonctionsTest.h"
#include "sensors.h"
#include "motion.h"
#include <Arduino.h>
#include <LibRobus.h>

int exempleFonction(int variable1, int variable2) {
    return variable1 * variable2;
}

void printIrValues() {
    SERIAL_PRINTF("IR 1: %i IR 2: %i IR 3: %i IR 4: %i\n", getSensorProximity(0), getSensorProximity(1), getSensorProximity(2), getSensorProximity(3));
}

void bonk() {

    for (int i = 0; i < 4; i++) {
        if (getSensorProximity(i) >= SENSOR_PROXIMITY_THRESHOLD) {
            #ifdef SENSOR_DEBUG_PRINT
                SERIAL_PRINTF("Found object #%i", i);
            #endif

            switch (i) {
                case 0:
                    rotate(30);
                    setServoAngle(130, SERVO_1);
                    delay(300);
                    setServoAngle(10, SERVO_1);
                    rotate(-30);
                break;
                case 1:
                    rotate(15);
                    setServoAngle(130, SERVO_1);
                    delay(300);
                    setServoAngle(10, SERVO_1);
                    rotate(-15);
                break;
                case 2:
                    rotate(-15);
                    setServoAngle(130, SERVO_1);
                    delay(300);
                    setServoAngle(10, SERVO_1);
                    rotate(15);
                break;
                case 3:
                    rotate(-30);
                    setServoAngle(130, SERVO_1);
                    delay(300);
                    setServoAngle(10, SERVO_1);
                    rotate(30);
                break;
            }
        }
    }
}