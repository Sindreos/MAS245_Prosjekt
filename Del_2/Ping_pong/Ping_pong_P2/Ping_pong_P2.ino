
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
Player2.isP1 = true;    
display.setFont(&Picopixel);
msg.len = 8;
msg.id = 001;
Player1.isP1 = false;
}

void loop() {
  display.clearDisplay();
  Player2.PadPos(UP, DOWN);
  Can0.read(rmsg);
  Player1.PadPos(rmsg.buf[0], rmsg.buf[1]);

  countLeft = rmsg.buf[6];
  countRight = rmsg.buf[7];
  display.fillCircle(rmsg.buf[4], rmsg.buf[5], 2, WHITE);
  display.fillRect(0,Player2.y/10,2, Player2.length,WHITE);
  display.fillRect(126,Player1.y/10,2, Player1.length,WHITE);
  display.drawRoundRect(52, 0, 24, 9, 2, WHITE);   
  display.drawLine(64, 0, 64, 8, WHITE); 
  display.setCursor(67, 6);
  display.print(countRight);
  display.setCursor(56, 6);
  display.print(countLeft);
  display.display();
  Serial.print(msg.buf[5]);
  msg.buf[2] = digitalRead(JOY_UP);
  msg.buf[3] = digitalRead(JOY_DOWN);
  Can0.write(msg);
}
