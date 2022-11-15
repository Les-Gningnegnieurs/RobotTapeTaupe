#include <Arduino.h>
#include <LibRobus.h>

//Constantes Robot B
const float LEFT_MOTOR_FULL_TURN = 3125.f; //in pulses
const float RIGHT_MOTOR_FULL_TURN = 3098.f; //in pulses
const float TOUR_PAR_CM = (1.f / 24.f); //t/cm
const float PULSE_PAR_CM = 128.125f; //p/cm
//90deg = 1.265 tour
const float TOUR_PAR_DEG_LEFT = (1.f/71.1462451f); //t/deg
const float PULSE_PAR_DEG_LEFT = 43.9236111f; //p/deg

//90deg = 1.255 tour
const float TOUR_PAR_DEG_RIGHT = (1.f/71.7131474f); //t/deg
const float PULSE_PAR_DEG_RIGHT = 43.1998889f; //p/deg

float vitesseMoteur0=0;   //vitesse du moteur gauche (0)
float vitesseMoteur1=0;   //vitesse du moteur droit (1)

const int moteurDroit = 0;
const int moteurGauche = 1;
const int deuxMoteurs = 2;


void setup() {
  // put your setup code here, to run once:
  BoardInit();
}

/// @brief Permet de faire tourner le roue x nombre de fois
/// @param mode 3 = les deux roues en sens inverse, 2 = les deux roues dans le même sens, 1 = roue droite, 0 = roue gauche
/// @param turnNb Nombre de tours
/// @param speed Vitesse de déplacement
/// @param counterClockwise Seulement mode 3, change le sens de la rotation (true ==> counter clockwise)
void MotorTurn(int mode, float turnNb, float speed, bool counterClockwise = false){
  float x = 0;
  float y = 0;
  float startx = 0;
  float starty = 0;

  switch (mode){
    case 3:
    //spot turn
      startx = ENCODER_Read(0);
      starty = ENCODER_Read(1);

      if(counterClockwise){
        MOTOR_SetSpeed(1, speed);
        MOTOR_SetSpeed(0, -speed);
      }
      else{
        MOTOR_SetSpeed(1, -speed);
        MOTOR_SetSpeed(0, speed);
      }

      while(1){
        x = ENCODER_Read(0);
        y = ENCODER_Read(1);
        // Serial.print(x);
        // Serial.print(" ");
        // Serial.println(y);
        
        if(counterClockwise){
          if(x >= LEFT_MOTOR_FULL_TURN * turnNb / 2 + startx){
            MOTOR_SetSpeed(0, 0);
          }
          if(y <= -RIGHT_MOTOR_FULL_TURN * turnNb / 2 + starty){
            MOTOR_SetSpeed(1, 0);
          }
          if(x >= LEFT_MOTOR_FULL_TURN * turnNb / 2 + startx && y <= -RIGHT_MOTOR_FULL_TURN * turnNb / 2 + starty){
            break;
          }
        }
        else{
          if(x <= -LEFT_MOTOR_FULL_TURN * turnNb / 2 + startx){
            MOTOR_SetSpeed(0, 0);
          }
          if(y >= RIGHT_MOTOR_FULL_TURN * turnNb / 2 + starty){
            MOTOR_SetSpeed(1, 0);
          }
          if(x <= -LEFT_MOTOR_FULL_TURN * turnNb / 2 + startx && y >= RIGHT_MOTOR_FULL_TURN * turnNb / 2 + starty){
            break;
          }
        }
      }

      // Serial.println("End");
      MOTOR_SetSpeed(0, 0);
      MOTOR_SetSpeed(1, 0);
      break;

    case 2 :
      //Left and Right Motor
      // ENCODER_Reset(0);
      // ENCODER_Reset(1);
      startx = ENCODER_Read(0);
      starty = ENCODER_Read(1);
      MOTOR_SetSpeed(1, speed);
      MOTOR_SetSpeed(0, speed);
      // Serial.println("Start");

      while(1){
        x = ENCODER_Read(0);
        y = ENCODER_Read(1);
        // Serial.print(x);
        // Serial.print(" ");
        // Serial.println(y);
        
        if(x >= LEFT_MOTOR_FULL_TURN * turnNb + startx){
          MOTOR_SetSpeed(0, 0);
        }
        if(y >= RIGHT_MOTOR_FULL_TURN * turnNb + starty){
          MOTOR_SetSpeed(1, 0);
        }
        if(x >= LEFT_MOTOR_FULL_TURN * turnNb + startx && y >= RIGHT_MOTOR_FULL_TURN * turnNb + starty){
          break;
        }
      }

      // Serial.println("End");
      MOTOR_SetSpeed(0, 0);
      MOTOR_SetSpeed(1, 0);
      break;

      case 1 :
      //Right Motor
      y = 0;
      // ENCODER_Reset(1);
      starty = ENCODER_Read(1);
      MOTOR_SetSpeed(1, speed);
      Serial.println("Start");
      while(1){
        y = ENCODER_Read(1);
        Serial.println(y);
        
        if(y >= RIGHT_MOTOR_FULL_TURN * turnNb + starty){
          MOTOR_SetSpeed(1, 0);
        }
        if(y >= RIGHT_MOTOR_FULL_TURN * turnNb + starty){
          break;
        }
      }
      Serial.println("End");
      MOTOR_SetSpeed(1, 0);

      break;

      case 0 :
      //Left Motor
      x = 0;
      // ENCODER_Reset(0);
      startx = ENCODER_Read(0);
      MOTOR_SetSpeed(0, speed);
      Serial.println("Start");
      while(1){
        x = ENCODER_Read(0);
        Serial.print(x);
        
        if(x >= LEFT_MOTOR_FULL_TURN * turnNb + startx){
          MOTOR_SetSpeed(0, 0);
        }
        if(x >= LEFT_MOTOR_FULL_TURN * turnNb + startx){
          break;
        }
      }
      Serial.println("End");
      MOTOR_SetSpeed(0, 0);
      break;
  }
}
void move(float distanceInPulse, float speed)
{
  float turnNb= distanceInPulse / LEFT_MOTOR_FULL_TURN;
  int mode = 2;
  
    MotorTurn(2,turnNb, speed);
}

void progressiveMove(float distanceInCM)
{
  ENCODER_Reset(1);
  float pulseDepart = ENCODER_Read(1);
  float sliceAmountACC=200;
  float speed = 0;
  float middlepulse= pulseDepart +(distanceInCM*PULSE_PAR_CM)/2;
  //float milieu=distanceInCM/2;
  float dACC=middlepulse/sliceAmountACC;
  float v = 0.10;
  float vMax=0.8f;
  float aACC = (v - vMax)/(pulseDepart - middlepulse);
  float x=0;

  if(middlepulse < 5000)
    vMax = 0.4f;
  /*Start en readant lencodeur--> continue TANT que que la DISTANCE EN PULSE est 
    plus petite que(DISTANCE EN PULSE + VALEUR INITIALE ENCODEUR)
    start le moteur a 0.15 pour la premiere iteration des 20
    faire des 20 iterations en cm(car move le convertit en tours)
    a chaque fois tu augmente la vitesse de 0.0175*/
    for(v=0.10; v<=vMax; v+=vMax/sliceAmountACC)
    {
      Serial.println(v);
      x=ENCODER_Read(1);
      if(x>=middlepulse){
        Serial.println("Fin ACC");
        break;
      }
    //  for(int i=0; i<sliceAmountDEC; i++)
    // {
    //   v=a*dDEC*i+vdec;

      move(dACC,v);
      //if v=vmax --> move le reste de la distance at vmax***
    }
    if(v>=vMax)
    {
      x=ENCODER_Read(1);
      float drestantePulse=(middlepulse-x);
      move(drestantePulse,vMax);
    }
  //deceleration
  x=ENCODER_Read(1);
  float pulsefinal= pulseDepart +(distanceInCM*PULSE_PAR_CM);
  float vMin=0.10;
  float vdec=v;
  float dDEC=500.f ; //a modifier
  int sliceAmountDEC=(pulsefinal-x)/dDEC ;  //donne le nb de slices (chaque slice est 1000 pulse)
  float aDEC=(vMin-vdec)/((pulsefinal-x));
  Serial.println("DECC");
  for(float i=0.f; i<=sliceAmountDEC; i++)
    {//qqchose pour dire à d'envoyer i à chaque slice donc a chaque 1000, envoyer v pour 1000 slice --> refaire calcul... 
      v=aDEC*dDEC*i+vdec;

      x=ENCODER_Read(1);
      Serial.print(pulsefinal);
      Serial.print(" ");
      Serial.print(x);
      Serial.print(' ');
      Serial.print(v);
      Serial.print(" ");
      Serial.print(dDEC * i);
      Serial.print(" ");
      Serial.println(sliceAmountDEC);


      if(v<=vMin)
        v=vMin;
      x=ENCODER_Read(1);
      if(x>=pulsefinal)
        { 
        v=0;
        Serial.println("fin");
        break;
        }
      move(dDEC,v);
    }
    //if v=vmax --> move le reste de la distance at vmax***

      x=ENCODER_Read(1);
      if(x<pulsefinal){
        Serial.println("restant hit");
        move(pulsefinal-x, vMin);
      }

      Serial.print("Restant : ");
      Serial.println(pulsefinal - x);
}
/* Permet de déplacer le robot sur une distance donnée en CM
   Paramètres : 
    float distanceInCM: la distance a parcourir en CM (positif pour avancer, négatif pour reculer)
    float speedInCMPerSecond: la vitesse du robot en % de force du moteur (entre 0 et 1)
   Retour : aucun
*/
void turn (float angleInDegrees, float speed) {

uint8_t choixmoteur=0;    //choisir moteur gauche ou moteur droit
int nbPulseTotal=0;   //nombre de pulse total pour effectuer la rotation
int EncodeurVal=0;    //valeur lue par l'encodeur

  //déterminer la direction de la rotation (choisir moteur)
  if (angleInDegrees>0)
  {
    //tourner à gauche
    int mode = 1;
    float turnNb = angleInDegrees * TOUR_PAR_DEG_LEFT;
    MotorTurn(mode ,turnNb,speed);
  } 
  
  else if (angleInDegrees<0)
  {
    //tourner à droite
    int mode = 0;
    float turnNb = -1 * angleInDegrees * TOUR_PAR_DEG_RIGHT;
    MotorTurn(mode ,turnNb, speed);
  }
  else
  {
    //quitter la méthode turn
    return;
  }
}



void loop() {
  progressiveMove(114.50);
  delay(1000);
  turn(90,0.2);
  delay(1000);
  progressiveMove(75);
  delay(1000);
  turn(-90,0.2);
  delay(1000);
  progressiveMove(75);
  delay(1000);
  turn(-45,0.2);
  delay(1000);
  progressiveMove(180);
  delay(1000);
  turn(90,0.2);
  delay(1000);
  progressiveMove(50);
  delay(1000);
  turn(-45,0.2);
  delay(1000);
  progressiveMove(120);
  delay(10000);

}