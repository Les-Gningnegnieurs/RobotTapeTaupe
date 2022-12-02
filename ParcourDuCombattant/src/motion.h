#pragma once

#define SERVO_ANGLE_RANGE 180
#define SERVO_1 0
#define SERVO_2 1
#define LEFT 0
#define RIGHT 1
#define ROTATE_SPEED 0.15
#define PULSE_PER_DEGREE_FORWARD 42 //To be changed
#define PULSE_PER_DEGREE_BACKWARD 44
#define CLOCKWISE_CORRECTION 1
#define COUNTERCLOCKWISE_CORRECTION 0.913
#define LEFT_WHEEL_CORRECTION  0 //-0.01
#define RIGHT_WHEEL_CORRECTION 0
//#define MOTION_DEBUG_PRINT
#define ENABLE_SERVO_1
//#define ENABLE_SERVO_2

#include <Arduino.h>
#include <Librobus.h>
#include "serial_printf.h"



void resetEncoders();

void setMotorSpeed(int id, float speed);

void rotate(int angle);

void setServoAngle(int angle, int servoId);

void bonk();
