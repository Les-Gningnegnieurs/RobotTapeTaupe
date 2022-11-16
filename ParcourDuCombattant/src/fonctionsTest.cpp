#include "fonctionsTest.h"
#include <Arduino.h>
#include <LibRobus.h>

int exempleFonction(int variable1, int variable2) {
    return variable1 * variable2;
}

void printSonarValues() {
    Serial.println("Sonnar 1:");
    Serial.println(SONAR_GetRange(0));
    Serial.println("Sonnar 2:");
    Serial.println(SONAR_GetRange(1));
    Serial.println("\n");
}