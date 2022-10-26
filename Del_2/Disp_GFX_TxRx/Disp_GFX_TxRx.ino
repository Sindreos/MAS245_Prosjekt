
#include <FlexCAN.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#include <Fonts/FreeMono24pt7b.h>
#define OLED_DC     6
#define OLED_CS     10
#define OLED_RESET  5
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);


#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int count = 0;
const int JOY_LEFT = 18;
const int JOY_RIGHT = 17;
const int JOY_CLICK =19;
const int JOY_UP  = 22;
const int JOY_DOWN = 23;
String CANStr("");
static CAN_message_t rmsg;

void setup() {
  Can0.begin(500000); //set speed here. 
  
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,16);
  display.println(" Testing");
  display.display();
  delay(1000);
  display.clearDisplay();  

  pinMode(JOY_LEFT, INPUT_PULLUP);
  pinMode(JOY_RIGHT, INPUT_PULLUP);
  pinMode(JOY_CLICK, INPUT_PULLUP);
  pinMode(JOY_UP, INPUT_PULLUP);
  pinMode(JOY_DOWN, INPUT_PULLUP);  
  Can0.startStats();
}

void Page2()
{
  
  int JOYL = HIGH;
  while(JOYL == HIGH)
{  
  Can0.read(rmsg);
  
  display.setCursor(4,1);  
  display.drawRoundRect(0,0,128,64,4,WHITE);
  display.drawLine(4,16,123, 16, WHITE);  
  for(int i = 4; i < 123; i++)
  {
    int16_t x = i;   
    if  (x % 2 == 0)
    {  
    display.drawPixel(x,16,WHITE);
    }
  }      
display.println(" MAS245 - Gruppe 01");  
  display.println(" CAN Statistikk   <2>");
  display.drawPixel(122,11,WHITE);
  display.drawPixel(122,12,WHITE);    
  display.drawPixel(123,12,WHITE);   
  display.drawPixel(122,13,WHITE); 
  display.drawLine(121,10,121, 14, WHITE);   
  display.drawPixel(111,11,WHITE);
  display.drawPixel(111,12,WHITE);    
  display.drawPixel(110,12,WHITE);   
  display.drawPixel(111,13,WHITE); 
  display.drawLine(112,10,112, 14, WHITE);   
  display.drawPixel(50,20,WHITE);
  display.drawPixel(51,20,WHITE);  
  display.drawPixel(50,21,WHITE);  
  display.drawPixel(51,21,WHITE);    
  display.drawPixel(50,26,WHITE);
  display.drawPixel(51,26,WHITE);  
  display.drawPixel(50,27,WHITE);  
  display.drawPixel(51,27,WHITE); 
  display.println(" Mottok ");
  display.setCursor(0,24);  
  display.print(" sist Id ");
  display.setCursor(58,17);
  display.setTextSize(1);
  display.print(rmsg.id,HEX);
  display.setTextSize(1);     
  display.display();  
  JOYL = digitalRead(JOY_LEFT);   
}
display.clearDisplay(); 
loop();
}

void loop()   
{  
  display.clearDisplay();  
  display.setCursor(4,1);  
  display.drawRoundRect(0,0,128,64,4,WHITE);
  display.drawLine(4,16,123, 16, WHITE);  
  for(int i = 4; i < 123; i++)
  {
    int16_t x = i;   
    if  (x % 2 == 0)
    {  
    display.drawPixel(x,32,WHITE);
    }
  }      
  display.println(" MAS245 - Gruppe 01");
  display.println(" CAN Statistikk    1>");
  display.drawPixel(122,11,WHITE);
  display.drawPixel(122,12,WHITE);    
  display.drawPixel(123,12,WHITE);   
  display.drawPixel(122,13,WHITE); 
  display.drawLine(121,10,121, 14, WHITE); 
  display.drawPixel(50,20,WHITE);
  display.drawPixel(51,20,WHITE);  
  display.drawPixel(50,21,WHITE);  
  display.drawPixel(51,21,WHITE);    
  display.drawPixel(50,26,WHITE);
  display.drawPixel(51,26,WHITE);  
  display.drawPixel(50,27,WHITE);  
  display.drawPixel(51,27,WHITE); 
  display.println(" Antall ");
  display.setCursor(0,24);  
  display.print(" mottatt ");
  display.setCursor(58,17);
  display.setTextSize(1);
  //display.print();
  display.setTextSize(1);      
  display.display();
  int JOYR = digitalRead(JOY_RIGHT);
  Serial.print(JOYR);  
  if(JOYR == LOW)
{
  display.clearDisplay();
  Page2();    
}
}