
// Use with GP2Y0A21YK Sensors

#include<Servo.h>
Servo aileron,elevator;
int setpoint=60,Kp=3;
void setup()
{
  Serial.begin(9600);
  aileron.attach(9);
  elevator.attach(10);
}
void loop()
{
  setpoint=map(setpoint,20,150,0,1024);
  int left,right,front,back;
  int d1,d2,d3,d4;
  int temp,temp1,temp2,temp3;
  int e1,e2,e3,e4;
  int op1,op2,op3,op4,opx,opy;
  temp=0;
  temp1=0;
  temp2=0;
  temp3=0;
  for(int i=0;i=10;i++)
  {
    left = analogRead(A0);
    delay(1);
    temp=temp+left;
  }
  d1=temp/10;
  for(int i=0;i=10;i++)
  {
    right = analogRead(A1);
    delay(1);
    temp1=temp1+right;
  }
  d2=temp1/10;
  for(int i=0;i=10;i++)
  {
    front = analogRead(A2);
    delay(1);
    temp2=temp2+front;
  }
  d3=temp2/10;
  for(int i=0;i=10;i++)
  {
    back = analogRead(A3);
    delay(1);
    temp3=temp3+back;
  }
  d4=temp3/10;
  
  e1=d1-setpoint;
  e2=d2-setpoint;
  e3=d3-setpoint;
  e4=d4-setpoint;
  
  op1=e1*Kp;
  op2=e2*Kp;
  op3=e3*Kp;
  op4=e4*Kp;
  
  opx=1500-op1+op2;
  opy=1500-op3+op4;
  
  aileron.writeMicroseconds(opx);
  elevator.writeMicroseconds(opy);
  
  
  
}
  
  
  
  
  

  
  
  
  
