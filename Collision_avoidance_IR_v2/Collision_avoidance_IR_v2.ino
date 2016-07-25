/*

   Code Written By Cyril Anthony
   
   Not for commercial use 

*/
#include <ServoIn.h>
#include <ServoOut.h>
#include <Timer1.h>
#define CHANNELS 2

int setpoint=60,Kp=3;

uint16_t g_values[CHANNELS];  
uint16_t Obuff[CHANNELS];                  
uint8_t  g_workIn[SERVOIN_WORK_SIZE(CHANNELS)];
uint8_t  g_pinsOut[CHANNELS] = {8, 9};
uint8_t  g_work[SERVOOUT_WORK_SIZE(CHANNELS)];
rc::ServoIn g_ServoIn(g_values, g_workIn, CHANNELS);
rc::ServoOut g_ServoOut(g_pinsOut, Obuff, g_work, CHANNELS);

void setup() {
  rc::Timer1::init();
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  Serial.begin(9600);
  PCMSK0 = (1 << PCINT18) | (1 << PCINT19);
  PCICR = (1 << PCIE0);
  g_ServoIn.start();

}

void loop() {
  setpoint=map(setpoint,20,150,0,1024);
  g_ServoIn.update();
  int left,front,right,back;
  int temp,temp1,temp2,temp3;
  int e1,e2,e3,e4;
  int op1,op2,op3,op4,opx,opy;
  int d1,d2,d3,d4;
  int x1=4;
  temp=0;
  temp1=0;
  temp2=0;
  temp3=0;
  for(int i=0;i<=x1;i++)
  {
    left = analogRead(A0);
    delay(2);
    temp=temp+left;
  }
  d1=temp/x1;
  for(int i=0;i<=x1;i++)
  {
    right = analogRead(A2);
    delay(2);
    temp1=temp1+right;
  }
   d3=temp1/x1;
  for(int i=0;i<=x1;i++)
  { 
    front = analogRead(A1);
    delay(2);
    temp2=temp2+front;
  }
  d2=temp2/x1;
  for(int i=0;i<=x1;i++)
  { 
    back = analogRead(A3);
    delay(2);
    temp3=temp3+back;
  }
  d4=temp3/x1;

  e1=d1-setpoint;
  e2=d2-setpoint;
  e3=d3-setpoint;
  e4=d4-setpoint;

  
  op1=e1*Kp;
  op2=e2*Kp;
  op3=e3*Kp;
  op4=e4*Kp;

   
  Obuff[1]=g_values[1]-op3+op1;
  Obuff[2]=g_values[2]-op4+op2;
  
  
  
  
  g_ServoOut.update();
  
  Serial.print(g_values[1]);
  Serial.print(",");
  Serial.print(g_values[2]);
  Serial.print(",");
  Serial.print(d1);
  Serial.print(",");
  Serial.print(d2);
  Serial.print(",");
  Serial.print(d3);
  Serial.print(",");
  Serial.println(d4);
  
  
}

static uint8_t lastB = 0;


ISR(PCINT18_vect)
{
 
  uint8_t newB = PINB;
  uint8_t chgB = newB ^ lastB; 
  lastB = newB;
  

  if (chgB)
  {
    
    if (chgB & _BV(0))
    {
      g_ServoIn.pinChanged(0, newB & _BV(0));
    }
    if (chgB & _BV(1))
    {
      g_ServoIn.pinChanged(1, newB & _BV(1));
    }
   }
}
