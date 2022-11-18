#include <Arduino.h>
#include <LibRobus.h>
#include "fonctionsTest.h"



void setup() {
  // put your setup code here, to run once:
  BoardInit();
  SERVO_Enable(0);
  
}



void loop() {
  //move();
  //SERVO_SetAngle(0, 0);
  printIrValues();
  delay(1000);
}