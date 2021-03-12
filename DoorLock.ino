#include <IRremote.h>
#include <Servo.h>

#define button 0x1C

int RECV_PIN = 2;
int SERVO_PIN = 3;
int led = 4;
int lockDegree = 120;
int unlockDegree = 0;

IRrecv irrecv(RECV_PIN);
Servo  servo;

void setup() 
{
  Serial.begin(96000);
  servo.attach(SERVO_PIN);
  pinMode(led, OUTPUT);
  irrecv.enableIRIn();
  servo.write(unlockDegree);
}

void loop() 
{
  if(irrecv.decode())
  {
    if(irrecv.decodedIRData.command == button)
    {
      if(CheckIsLocked() == true)
      {
        servo.write(unlockDegree);
        digitalWrite(led, LOW);
      }
      else
      {
        servo.write(lockDegree);
        digitalWrite(led, HIGH);
      }
      
      delay(100);
    }
  }
  
  irrecv.resume();
}

bool CheckIsLocked()
{
  if(servo.read() == lockDegree)
    return true;
  else
    return false;
}
