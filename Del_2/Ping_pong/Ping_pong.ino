
#include <FlexCAN.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>
#include <Fonts/Picopixel.h>
#include "Player.h"
#include "Engine.h"
#define OLED_DC     6
#define OLED_CS     10
#define OLED_RESET  5
static CAN_message_t rmsg;
static CAN_message_t msg;
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

Player Player1;
Player Player2;
Engine Eng;
int startTime = millis();
int UP = 1;
int DOWN = 1;
int countRight;
int countLeft;

void setup() {
Can0.begin(500000); //set speed here. 
Serial.begin(9600);
display.begin(SSD1306_SWITCHCAPVCC);
display.setTextColor(WHITE);
pinMode(JOY_UP, INPUT_PULLUP);
pinMode(JOY_DOWN, INPUT_PULLUP);  
display.clearDisplay();
Player1.isP1 = true;   
Player2.isP1 = false; 
display.setFont(&Picopixel);
msg.len = 8;
msg.id = 002;
}

void loop() {
  display.clearDisplay();
  Player1.PadPos(UP, DOWN);
  Can0.read(rmsg);
  Player2.PadPos(rmsg.buf[2], rmsg.buf[3]);
  Eng.Ball(startTime);
if(Eng.x < -4)
{
  countRight++;
  Eng.x = 64;
  Eng.y = 32;
  Eng.u = 50;
}  
if(Eng.x > 130)
{
  countLeft++;  
  Eng.x = 64;
  Eng.y = 32;
  Eng.u = 50;
}  
  Eng.ColP1(Player1.y, Player1.lastPressed);
  Eng.ColP2(Player2.y, Player2.lastPressed);
  display.fillCircle(Eng.x, Eng.y, 2, WHITE);
  msg.buf[4] = Eng.x;
  msg.buf[5] = Eng.y;
  msg.buf[0] = digitalRead(JOY_UP);
  msg.buf[1] = digitalRead(JOY_DOWN);
  msg.buf[6] = countLeft;
  msg.buf[7] = countRight;
  Can0.write(msg);
  display.fillRect(126,Player1.y/10,4, Player1.length,WHITE);
  display.fillRect(0,Player2.y/10,2, Player2.length,WHITE);
  display.drawRoundRect(52, 0, 24, 9, 2, WHITE);   
  display.drawLine(64, 0, 64, 8, WHITE); 
  display.setCursor(67, 6);
  display.print(countRight);
  display.setCursor(56, 6);
  display.print(countLeft);
  display.display();
  Serial.print(msg.buf[0]);
}
