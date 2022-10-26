#include <FlexCAN.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define OLED_DC     6 //Choose pin for OLED Screen
#define OLED_CS     10
#define OLED_RESET  5
#define SSD1306_LCDHEIGHT 64 //Redefine the LCD height from 32 to 64
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS); 

static CAN_message_t mes, rmes; //Buffer structure

void setup(){
  display.begin(SSD1306_SWITCHCAPVCC); 
  display.clearDisplay(); //Clears the buffer of the display
  
  Can0.begin(250000); //Sets the Baud Rate of the can0 bus (250000 is standard) 
  Can1.begin(250000); //Sets the Baud Rate of the can1 bus Teensy 3.6 have two CAN
  mes.len = 8; //Sets the number of data bytes for this frame
  mes.buf[0] = 1; //This is the "Payload", first data byte of the buffer
  mes.buf[1] = 0;
  mes.buf[2] = 1;
  mes.buf[3] = 0;
  mes.buf[4] = 1;
  mes.buf[5] = 0;
  mes.buf[6] = 1;
  mes.buf[7] = 0;
  mes.buf[8] = 1;
  mes.flags.remote = 0; //Sets the frame as normal, if 1 then frame is remote request frame
  mes.id = 3046; //Specify an id
  mes.flags.extended = 0; //Decides if it uses the extended bit id or regular (up to 4095)
  Can0.write(mes);
  Can1.write(mes); 
  }

void loop() {
     Can0.read(rmes)
     Serial.print(rmes.id,HEX); 
     Serial.print(' '); 
     Serial.print(rmes.len,HEX); 
     Serial.print(' ');  
     
     display.fillRect(0,15,128, 30,BLACK);
     display.setCursor(0,15);
     
     display.println(rmes.id,HEX); 
     display.println(rmes.len,HEX); 
     display.display();
}