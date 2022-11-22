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