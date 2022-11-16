#include <FlexCAN.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>
#include <WString.h>
#define OLED_DC     6
#define OLED_CS     10
#define OLED_RESET  5
static CAN_message_t rmsg;
static CAN_message_t msg;
String idle = "Awaiting input";
String send = "Message sent";
String read = "Message recieved";
const int JOY_UP = 22;
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
bool stop = true;
bool stop2 = true;
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
pinMode(JOY_UP, INPUT_PULLUP);
Can0.begin(250000); //set speed here. 
display.begin(SSD1306_SWITCHCAPVCC);
display.setTextColor(WHITE);
display.clearDisplay();
msg.len = 8;
msg.id = 001;
display.print(idle);
Serial.begin(9600);
}

void loop() {
if(stop2 == true)
{
  Can0.read(rmsg);
}
  if((rmsg.buf[0] == 17) & (stop2 == true))
  {
    display.clearDisplay();
    display.print(read);
    display.display();
    stop2 = false;    
  }
  
  if((digitalRead(JOY_UP) == 0) & (stop == true))
  {
  display.clearDisplay();
  msg.buf[0] = 1;
  Can0.write(msg);
  display.setCursor(0,0);
  display.print(send);
  stop = false;
  }    
  display.display();
  Serial.println(rmsg.buf[0]);
}