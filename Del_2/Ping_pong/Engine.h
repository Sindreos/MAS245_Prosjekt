
class Engine 
{
private:
bool init = true;
int count = 1;
public:
int u = 50; //speed (pixel/u*ms)
int s1 = 0;
int x1 = -1;
int y1 = 0;
int16_t x = 0;
int16_t y = 0;
int s = 0;
int startTime1;

void Ball(int startTime)
{
  int endTime = millis();
  while(init == true)
  {   
    x = 64;
    y = 32;
    s = -(startTime - endTime);
    startTime1 = startTime;
    init = false;
  }
  if(s > u)
{ 
    startTime1 = millis(); 
    x = x + x1;
    y = y + y1;
}
  s = -(startTime1 - endTime);
    if(((y < 4)  or (y > 60)) and (s > u))
  {
  y1 = -1*y1;
  }
}

void ColP1(int P1ay, int lpr)
{
  if((x > 123) & (y > (P1ay/10)) & (y < (P1ay/10 + 20)))
  {
  if(lpr == 1)
{    
  y1 = -1;
}  
else
{
  y1 = 1;
}
  x1 = -1;
  if(s > u)
  { u = u - 2;
  }
  }
}
void ColP2(int P2ay, int lpr2)
{
  if((x < 2) & (y > (P2ay/10)) & (y < (P2ay/10 + 20)))
  {
  if(lpr2 == 1)
{    
  y1 = -1;
}  
else
{
  y1 = 1;
}
  x1 = -1;
  if(s > u)
  { u = u - 2;
  }
x1 = 1;  
}
}
};
