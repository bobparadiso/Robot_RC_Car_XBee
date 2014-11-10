/*
-car using: relays for h-bridge for rwd wheels
-using servo for front steering and arm
-arduino directly pulsing pins to control servos
*/

#include <SoftwareSerial.h>
#include <Servo.h> 
#include "ServoController.h"

//wireless
#define wirelessRxPin 3
#define wirelessTxPin 4

//servos

#define steerPin 3
#define steerCenter 1370
#define steerRadius 130

#define liftPin 5
#define liftUp 2150
#define liftDown 1210

#define grabPin 6
#define grabOpen 1800
#define grabClose 1060

//h-bridge
#define fwd 12
#define rev 11

#define wirelessTimeout 500

// set serial ports
//SoftwareSerial wirelessSerial(wirelessRxPin, wirelessTxPin);
#define wirelessSerial Serial

Servo steerServo;
ServoController steerControl;

Servo liftServo;
ServoController liftControl;

Servo grabServo;
ServoController grabControl;

// the setup routine runs once when you press reset:
void setup()
{
  //setup servos
  steerServo.attach(steerPin);
  steerControl.servo = &steerServo;
  liftServo.attach(liftPin);
  liftControl.servo = &liftServo;
  grabServo.attach(grabPin);
  grabControl.servo = &grabServo;
  
  pinMode(fwd, OUTPUT);     
  pinMode(rev, OUTPUT);     

  digitalWrite(fwd, HIGH);
  digitalWrite(rev, HIGH);

  //Serial.begin(115200);
  //Serial.println("hello world");

  //setup wireless  
  wirelessSerial.begin(115200); 
  //wirelessSerial.listen();

  //set starting positions
  steerControl.set(steerCenter, 0);
  liftControl.set(liftUp, 0);
  grabControl.set(grabClose, 0);
}

#define servoSpeed 400.0f

uint32_t lastRx;
uint32_t lastUpdate; 
void loop()
{
  float elapsed = (millis() - lastUpdate) * 0.001f;
  lastUpdate = millis();
  steerControl.update(elapsed);
  liftControl.update(elapsed);
  grabControl.update(elapsed);
  
  //wirelessSerial.listen();
  //Serial.write("hello\n");
  //delay(500);

  //force disable motor  
  if (millis() - lastRx > wirelessTimeout)
  {
      digitalWrite(rev, HIGH);
      digitalWrite(fwd, HIGH);
  }

  if (!wirelessSerial.available())
    return;
  
  char val = wirelessSerial.read();
  lastRx = millis();
    
  //Serial.print("received:");
  //Serial.println(val);
  
  switch(val)
  {
    case 'u':
      digitalWrite(fwd, LOW);
      digitalWrite(rev, HIGH);
      break;

    case 'd':
      digitalWrite(fwd, HIGH);
      digitalWrite(rev, LOW);
      break;

    case '-':
      digitalWrite(rev, HIGH);
      digitalWrite(fwd, HIGH);
      break;

    case 'l':
      steerControl.set(steerCenter - steerRadius, 0);
      break;

    case 'r':
      steerControl.set(steerCenter + steerRadius, 0);
      break;

    case '|':
      steerControl.set(steerCenter, 0);
      break;
      
    case 'U':
      //Serial.println("liftDown");
      liftControl.set(liftDown, servoSpeed);      
      break;

    case 'D':
      //Serial.println("liftUp");
      liftControl.set(liftUp, servoSpeed);      
      break;

    case '_':
      //hold at current position
      liftControl.set(liftControl.pos, 0);
      break;
      
    case 'L':
      //Serial.println("grabClose");
      grabControl.set(grabClose, servoSpeed);
      break;

    case 'R':
      //Serial.println("grabOpen");
      grabControl.set(grabOpen, servoSpeed);
      break;

    case '\\':
      //hold at current position
      grabControl.set(grabControl.pos, 0);
      break;
  }
}

