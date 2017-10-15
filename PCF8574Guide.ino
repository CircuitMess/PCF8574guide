#include <SPI.h>
#include <Gamebuino.h>
#include <Wire.h>

Gamebuino gb;

#define PCF8574A 0x38
#define inputPin 0x02

bool ledOff = true;
byte values = 0;
int counter = 0;

void setup(){
  gb.begin();
  Wire.begin();
  Wire.beginTransmission(PCF8574A);
  Wire.write(0xFF);
  Wire.endTransmission();
  gb.titleScreen(F("PCF8574(A) Pro Guide"));
}


void loop(){

  if(gb.update())
  {
    Wire.requestFrom(PCF8574A, 1);
    while(Wire.available())
    {
      values = Wire.read();
    }
    if((values & inputPin)==0)counter++;
    else counter = 0;
    
    if(counter == 5)
    {
      ledOff = !ledOff;
      counter = 0;
    }
    Wire.beginTransmission(PCF8574A);
    Wire.write((inputPin | ledOff));
    Wire.endTransmission();

    gb.display.cursorX = 0;
    gb.display.cursorY = 0;
    if(ledOff)gb.display.println(F("LED Off"));
    else gb.display.println(F("LED On"));
    
    values = 0;
    
    if(gb.buttons.pressed(BTN_C))                      
    {                                                 
      gb.titleScreen(F("PCF8574(A) Pro Guide"));
    }
  }  
}
