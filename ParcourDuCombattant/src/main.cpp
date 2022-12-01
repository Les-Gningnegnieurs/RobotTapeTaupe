#include <Arduino.h>
#include <LibRobus.h>
#include "motion.h"
#include "sensors.h"
#include "gameHandler.h"
#include "fonctionsTest.h"



void setup() {
  // put your setup code here, to run once:
  BoardInit();
  
  #ifdef ENABLE_SERVO_1
    SERVO_Enable(SERVO_1);
    Serial.println("Servo 1 enabled");
  #elif defined ENABLE_SERVO_2
    SERVO_Enable(SERVO_2);
    Serial.println("Servo 2 enabled");
  #endif
  setServoAngle(10, SERVO_1);
}

void loop() {

  //SERIAL_PRINTF("%i \n", getSensorProximity(1));
  //printIrValues();
  //bonkV2();
  //testRotate();
  rotate(-30);
  delay(500);
  //testCounterRotate();
  rotate(30);
  delay(600);
}