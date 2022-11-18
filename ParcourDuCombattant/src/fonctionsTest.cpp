#include "fonctionsTest.h"
#include <Arduino.h>
#include <LibRobus.h>

int exempleFonction(int variable1, int variable2) {
    return variable1 * variable2;
}
/*void servo()
{
	SERVO_Enable(1);
	SERVO_SetAngle(1, 180);
	delay(100);
	SERVO_SetAngle(1, -180);
	delay(200);
	SERVO_Disable(1);
}*/
int lirecapteur()
{
	while(1)
	{
		ROBUS_ReadIR(1);
		Serial.println(ROBUS_ReadIR(1));
		delay(50);
		if(ROBUS_ReadIR(1)>300)
		{
			return 1;
		}
	}
}
void move()
{
	int pos = lirecapteur();
	if(pos == 1)
	{
	ENCODER_Reset(0);
	ENCODER_Reset(1);

		while(ENCODER_Read(0)<1000)
		{
			MOTOR_SetSpeed(0, 0.10);
			MOTOR_SetSpeed(1, -0.10);
		}
		MOTOR_SetSpeed(0, 0);
		MOTOR_SetSpeed(1, 0);
		delay(2000);
		//servo();
		ENCODER_Reset(0);
		ENCODER_Reset(1);
		while(ENCODER_Read(0)>-1000)
		{
			MOTOR_SetSpeed(0, -0.10);
			MOTOR_SetSpeed(1, 0.10);
		}
		MOTOR_SetSpeed(0, 0);
		MOTOR_SetSpeed(1, 0);
		Serial.println("frapper taupe");
	}

	
}

void printSonarValues() {
    Serial.print("Sonnar 1:");
    Serial.print(SONAR_GetRange(0));
    Serial.print("Sonnar 2:");
    Serial.print(SONAR_GetRange(1));
    Serial.print("\n");
}

void printIrValues() {
	Serial.print("Pin 1:");
  Serial.print(ROBUS_ReadIR(0));
	Serial.print("Pin 2:");
  Serial.print(ROBUS_ReadIR(1));
	Serial.print("Pin 3:");
  Serial.print(ROBUS_ReadIR(2));
	Serial.print("Pin 4:");
  Serial.print(ROBUS_ReadIR(3));
	Serial.print("\n");
}
