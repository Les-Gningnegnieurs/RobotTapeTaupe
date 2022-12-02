#include "gameHandler.h"

int sensorThresholds[] = {THRESHOLD_SENSOR_1, THRESHOLD_SENSOR_2, THRESHOLD_SENSOR_3, THRESHOLD_SENSOR_4};
int anglesTaupe[] = {ANGLE_TAUPE_1, ANGLE_TAUPE_2, ANGLE_TAUPE_3, ANGLE_TAUPE_4};
int hits = 0;

void bonkV2() {
    for (int i = 0; i < 4; i++) {
        if (getSensorProximity(i) >= sensorThresholds[i]) {
            #ifdef GAME_DEBUG_PRINT
                SERIAL_PRINTF("Mole #%i has been detected\n", (i + 1));
            #endif
            rotate(anglesTaupe[i]);
            setServoAngle(85, SERVO_1);
            delay(400);  //Le delay(300) laisse le temps au servo d'atteindre l'angle désiré, ne pas l'enlever
            setServoAngle(10, SERVO_1);  
            rotate(-anglesTaupe[i]-1); 
            
           /* hits++;
            if (hits >= 100000) {
                resetEncoders();
                delay(200);   
                setMotorSpeed(LEFT, 0.15);
                setMotorSpeed(RIGHT, 0.15);
                while (ENCODER_Read(LEFT) < 150) {}
                setMotorSpeed(LEFT, 0);
                setMotorSpeed(RIGHT, 0);
                resetEncoders();
                hits = 0;*/
            
        }
    }
}