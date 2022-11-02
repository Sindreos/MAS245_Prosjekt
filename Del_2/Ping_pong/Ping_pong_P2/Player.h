const int JOY_UP = 22;
const int JOY_DOWN = 23;

class Player 
{
private:
  int i = 0;
  bool init = true;
  
  int UP;
  int DOWN;


public:
  int16_t y = 0;
  bool isP1 = true;
  int lastPressed = 1;
  void PadPos(int CAN_UP, int CAN_DOWN) 
  {
      if (isP1 == true) 
      {
        UP = digitalRead(JOY_UP);
        DOWN = digitalRead(JOY_DOWN);
      } else 
      {
        UP = CAN_UP;
        DOWN = CAN_DOWN;
      }
    if (UP == 0) 
    {
      y--;
      lastPressed = 1;       
    }
    if (DOWN == 0) 
    {
      y++;
      lastPressed = 0;  
    }
    if (y > 440) 
    {
      y = 440;
    }
    if (y < 0) 
    {
      y = 0;
    }
  }
  int16_t length = y + 20;
};