#include "motion.h"

static float leftMotorSpeed = 0;
static float rightMotorSpeed = 0;


void resetEncoders() {
    ENCODER_Reset(LEFT);
    ENCODER_Reset(RIGHT);
    #ifdef MOTION_DEBUG_PRINT
        SERIAL_PRINTF("Encoders have been reset\n");
    #endif
}

void setMotorSpeed(int id, float speed) {

    if ((speed < -1) || (speed > 1)) {
        #ifdef MOTION_DEBUG_PRINT
            SERIAL_PRINTF("Invalid speed when calling setMotorSpeed()\n");
        #endif
        return;
    }

    switch (id) {
        case LEFT:
            leftMotorSpeed = speed;
            MOTOR_SetSpeed(LEFT, leftMotorSpeed);
            #ifdef MOTION_DEBUG_PRINT
                SERIAL_PRINTF("Left motor speed has been set to %f \n", (float)leftMotorSpeed);
            #endif
        break;

        case RIGHT:
            rightMotorSpeed = speed;
            MOTOR_SetSpeed(RIGHT, rightMotorSpeed);
            #ifdef MOTION_DEBUG_PRINT
                SERIAL_PRINTF("Right motor speed has been set to %f \n", (float)rightMotorSpeed);
            #endif
        break;

        default:
            #ifdef MOTION_DEBUG_PRINT
                SERIAL_PRINTF("Invalid ID when calling setMotorSpeed()\n");
            #endif
        break;
    }
}

void rotate(int angle) {
    resetEncoders();
    if (angle > 0) {
        #ifdef MOTION_DEBUG_PRINT
            SERIAL_PRINTF("Starting clockwise rotation of %i degree(s)\n", angle);
        #endif
        setMotorSpeed(LEFT, ROTATE_SPEED);
        setMotorSpeed(RIGHT, -ROTATE_SPEED);
        while (ENCODER_Read(LEFT) < (angle * PULSE_PER_DEGREE_FORWARD * CLOCKWISE_CORRECTION)){}
        setMotorSpeed(LEFT, 0);
        setMotorSpeed(RIGHT, 0);
        #ifdef MOTION_DEBUG_PRINT
            SERIAL_PRINTF("Clockwise rotation finished with %i pulses on the left motor and %i pulses on the right motor\n", ENCODER_Read(LEFT), ENCODER_Read(RIGHT));
        #endif
    }
    else if (angle < 0) {
        #ifdef MOTION_DEBUG_PRINT
            SERIAL_PRINTF("Starting counterclockwise rotation of %i degree(s)\n", angle);
        #endif
        setMotorSpeed(LEFT, -ROTATE_SPEED);
        setMotorSpeed(RIGHT, ROTATE_SPEED);
        while (ENCODER_Read(LEFT) > (angle * PULSE_PER_DEGREE_BACKWARD * COUNTERCLOCKWISE_CORRECTION)){}
        setMotorSpeed(LEFT, 0);
        setMotorSpeed(RIGHT, 0);
        #ifdef MOTION_DEBUG_PRINT
            SERIAL_PRINTF("Counterclockwise rotation finished with %i pulses on the left motor and %i pulses on the right motor\n", ENCODER_Read(LEFT), ENCODER_Read(RIGHT));
        #endif
    }
    else {
        #ifdef MOTION_DEBUG_PRINT
            SERIAL_PRINTF("Invalid angle when calling rotate()\n");
        #endif  
    }
    resetEncoders();
}

void setServoAngle(int angle, int servoId) {
    if ((angle < 0) || (angle > SERVO_ANGLE_RANGE)) {
        #ifdef MOTION_DEBUG_PRINT
            SERIAL_PRINTF("Invalid angle when calling setServoAngle()\n");
        #endif
        return;
    }

    switch (servoId) {
        case SERVO_1:
            #ifdef ENABLE_SERVO_1
                SERVO_SetAngle(SERVO_1, angle);
            #elif defined MOTION_DEBUG_PRINT
                SERIAL_PRINTF("Servo 1 not active\n");
            #endif
        break;

        case SERVO_2:
            #ifdef ENABLE_SERVO_2
                SERVO_SetAngle(SERVO_2, angle);
            #elif defined MOTION_DEBUG_PRINT
                SERIAL_PRINTF("Servo 2 not active\n");
            #endif
        break;
        
        default:
            #ifdef MOTION_DEBUG_PRINT
                SERIAL_PRINTF("Invalid ID when calling setServoAngle()\n");
            #endif
        break;
    }
}