#define a 0
#define b 1
#define c 2
#define d 3
#define e 4
#define f 5
#define g 6
#define aa 7
#define bb 8
#define cc 9
#define dd 10
#define ee 11
#define ff 13
#define gg 12
#define RESET A0
#define TIME_UP A3
#define TIME_DOWN A4
#define SWITCH_DEALY A5
double num=0,dis=0;
long duration=0;
boolean delay_flag=0;
byte counter=0;
unsigned int delay_time=0;
byte cnt=0,num_after_point=0,num_befor_point=0;
byte s0[7]={a,b,c,d,e,f,g},s1[7]={aa,bb,cc,dd,ee,ff,gg};
byte nums[11][7]={
  {1,1,1,1,1,1,0},
  {0,1,1,0,0,0,0},  
  {1,1,0,1,1,0,1},
  {1,1,1,1,0,0,1},
  {0,1,1,0,0,1,1},
  {1,0,1,1,0,1,1},
  {1,0,1,1,1,1,1},
  {1,1,1,0,0,0,0},
  {1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1},
  {0,0,0,0,0,0,0}};

void sev1(uint8_t n10){
  for(int i=0;i<7;i++)
    digitalWrite(s1[i],*((*nums)+i+(7*n10)));    
}
void sev0(uint8_t n0){
  for(int i=0;i<7;i++)
    digitalWrite(s0[i],*((*nums)+i+(7*n0)));    
  }
void setup()
{
  for (int i=0;i<14;i++)
    pinMode(i, OUTPUT);
  for(byte i=14;i<20;i++)
  pinMode(i,INPUT_PULLUP);
}
void loop()
{
  if(!digitalRead(RESET))counter=0;
  if(!digitalRead(A1))counter--;
  else if(!digitalRead(A2))counter++;wait();
  counter=constrain(counter,0,99);
  num=counter;  
  num=(num>=10)?(num/10):num;
  num_befor_point=uint8_t(num);
  num_after_point=(((num+0.09)-uint8_t(num))*10);  
  sev1((counter>=10)?num_befor_point:10);
  sev0((counter>=10)?num_after_point:num_befor_point);
}


void wait(){
  if(!digitalRead(SWITCH_DEALY)){delay_flag=!delay_flag;while(!digitalRead(SWITCH_DEALY));}
  if(!digitalRead(TIME_UP)){delay_time+=100;while(!digitalRead(TIME_UP));}
  else if(!digitalRead(TIME_DOWN)){delay_time-=100;while(!digitalRead(TIME_DOWN));}
  delay_time=constrain(delay_time,0,5000);
  while((!digitalRead(A1)||!digitalRead(A2))&&delay_flag){delay_time=0;}
  delay(delay_time);
}
