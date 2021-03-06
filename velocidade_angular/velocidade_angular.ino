
#include <Pololu3pi.h>
#include <PololuQTRSensors.h>
#include <OrangutanMotors.h>
#include <OrangutanAnalog.h>
#include <OrangutanLEDs.h>
#include <OrangutanLCD.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanBuzzer.h>

Pololu3pi robot;
unsigned int sensors[5];


#include <avr/pgmspace.h>

const char welcome_line1[] PROGMEM = " Pololu";
const char welcome_line2[] PROGMEM = "3\xf7 Robot";
const char demo_name_line1[] PROGMEM = "Line";
const char demo_name_line2[] PROGMEM = "follower";


const char welcome[] PROGMEM = ">g32>>c32";
const char go[] PROGMEM = "L16 cdegreg4";


const char levels[] PROGMEM = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};
void load_custom_characters()
{
  OrangutanLCD::loadCustomCharacter(levels + 0, 0); // no offset, e.g. one bar
  OrangutanLCD::loadCustomCharacter(levels + 1, 1); // two bars
  OrangutanLCD::loadCustomCharacter(levels + 2, 2); // etc...
  OrangutanLCD::loadCustomCharacter(levels + 3, 3);
  OrangutanLCD::loadCustomCharacter(levels + 4, 4);
  OrangutanLCD::loadCustomCharacter(levels + 5, 5);
  OrangutanLCD::loadCustomCharacter(levels + 6, 6);
  OrangutanLCD::clear(); // the LCD must be cleared for the characters to take effect
}

void display_readings(const unsigned int *calibrated_values)
{
  unsigned char i;

  for (i=0;i<5;i++) {
   
    const char display_characters[10] = { ' ', 0, 0, 1, 2, 3, 4, 5, 6, 255 };

  
    char c = display_characters[calibrated_values[i] / 101];


    OrangutanLCD::print(c);
  }
}
#include <OrangutanLCD.h>
OrangutanLCD lcd;

void setup()
{
  unsigned int counter; 

 
  robot.init(2000);

  load_custom_characters(); 


  OrangutanLCD::printFromProgramSpace(welcome_line1);
  OrangutanLCD::gotoXY(0, 1);
  OrangutanLCD::printFromProgramSpace(welcome_line2);
  OrangutanBuzzer::playFromProgramSpace(welcome);
  delay(1000);

  OrangutanLCD::clear();
  OrangutanLCD::printFromProgramSpace(demo_name_line1);
  OrangutanLCD::gotoXY(0, 1);
  OrangutanLCD::printFromProgramSpace(demo_name_line2);
  delay(1000);

  
  while (!OrangutanPushbuttons::isPressed(BUTTON_B))
  {
    int bat = OrangutanAnalog::readBatteryMillivolts();

    OrangutanLCD::clear();
    OrangutanLCD::print(bat);
    OrangutanLCD::print("mV");
    OrangutanLCD::gotoXY(0, 1);
    OrangutanLCD::print("Press B");

    delay(100);
  }

 
  OrangutanPushbuttons::waitForRelease(BUTTON_B);
  delay(1000);


  for (counter=0; counter<80; counter++)
  {
    if (counter < 20 || counter >= 60)
      OrangutanMotors::setSpeeds(40, -40);
    else
      OrangutanMotors::setSpeeds(-40, 40);

 
    robot.calibrateLineSensors(IR_EMITTERS_ON);

    delay(20);
  }
  OrangutanMotors::setSpeeds(0, 0);

  while (!OrangutanPushbuttons::isPressed(BUTTON_B))
  {
    // Read the sensor values and get the position measurement.
    unsigned int position = robot.readLine(sensors, IR_EMITTERS_ON);

    OrangutanLCD::clear();
    OrangutanLCD::print(position);
    OrangutanLCD::gotoXY(0, 1);
    display_readings(sensors);

    delay(100);
  }
  OrangutanPushbuttons::waitForRelease(BUTTON_B);

  OrangutanLCD::clear();

  OrangutanLCD::print("Go!");    

  OrangutanBuzzer::playFromProgramSpace(go);
  while(OrangutanBuzzer::isPlaying());
   lcd.gotoXY(0,0); 
   lcd.print("               ");    
   delay(1);

}
int volta = 0;
int meta = 0;
int vc = 100;
int vl;
int vr;
int r = 1;
int sum;
int pos;
int position;

void loop()
{
  robot.readLine(sensors, IR_EMITTERS_ON);
  sum=sensors[0]+sensors[1]+sensors[3]+sensors[4]+sensors[2];
  pos=sensors[0]*(-2)+sensors[1]*(-1)+sensors[3]*1+sensors[4]*2;
  position = pos;
  lcd.clear();
  lcd.gotoXY(0,0); 
  OrangutanLCD::print(pos);
  lcd.gotoXY(0,1);
  OrangutanLCD::print(sum);

  

  
//  if (sensors[0] > 600 && sensors[1] > 600 && sensors[2] > 600 && sensors[3] > 600 && sensors[4] > 600)
//  {
//    if (volta == 3)
//    {
//      OrangutanMotors::setSpeeds(0, 0);
//      delay(5000);
//      
//    }
//    
//    if (meta == 0) {
//      volta++;
//      meta = 1;
//      //lcd.gotoXY(0,0); 
//      //OrangutanLCD::print(volta); 
//         
//    }
//    else {
//      meta = 1;
//    }
//  }
//  else {
//    meta = 0;
//  } 
 int w = ((int)position)/25;
 
  vl = vc + w*r;
  vr = vc - w*r;
  OrangutanMotors::setSpeeds(vl , vr);

}
