#include <OrangutanLEDs.h>
#include <OrangutanAnalog.h>
#include <OrangutanMotors.h>
#include <OrangutanLCD.h>
 
OrangutanAnalog analog;
OrangutanLEDs leds;
OrangutanMotors motors;
OrangutanLCD lcd;
 int speed=40;
 
 int direita=40;
 int esquerda=39;//direita/1.0447;
void setup()                    // run once, when the sketch starts
{
   delay(6000);
   
 
}
 
void loop()                     // run over and over again
{
  motors.setSpeeds(esquerda,direita);
   delay(3580);
   motors.setSpeeds(0,0);
    rodar(2);
}

void rodar(int n){
  motors.setSpeeds(-esquerda,direita);
  delay(850/n);
  motors.setSpeeds(0,0);
}

