#include <Arduino.h>
#include <LibRobus.h>
#include "motion.h"
#include "sensors.h"
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
}



void loop() {
  printSonarValues();
  delay(500);
}