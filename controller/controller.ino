#include <SoftwareSerial.h>

#define xBeeRxPin 10
#define xBeeTxPin 11
#define sw1Pin 2
#define sw2Pin 3
#define driveLRPin A0
#define driveUDPin A1
#define armLRPin A2
#define armUDPin A3

SoftwareSerial xBeeSerial(xBeeRxPin, xBeeTxPin);

//initial setup
void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // set the data rate for the SoftwareSerial port
  xBeeSerial.begin(115200);
  
  pinMode(sw1Pin, INPUT);
  pinMode(sw2Pin, INPUT);
  
  pinMode(driveLRPin, INPUT);
  pinMode(driveUDPin, INPUT);
  pinMode(armLRPin, INPUT);
  pinMode(armUDPin, INPUT);
}

//scan controls
//send commands to car
void loop()
{
  int sw1val = digitalRead(sw1Pin);
  int sw2val = digitalRead(sw2Pin);
  
  int lrval = analogRead(driveLRPin);
  //Serial.print("drive lrval:");
  //Serial.println(lrval);
  int udval = analogRead(driveUDPin);
  //Serial.print("drive udval:");
  //Serial.println(udval);

  if (udval > 700)
    xBeeSerial.write('u');
  else if (udval < 200)
    xBeeSerial.write("d");
  else
    xBeeSerial.write('-'); 

  if (lrval > 700)
    xBeeSerial.write('r');
  else if (lrval < 200)
    xBeeSerial.write('l');
  else
    xBeeSerial.write('|'); 

  lrval = analogRead(armLRPin);
  //Serial.print("arm lrval:");
  //Serial.println(lrval);
  udval = analogRead(armUDPin);
  //Serial.print("arm udval:");
  //Serial.println(udval);

  if (udval > 700)
    xBeeSerial.write('U');
  else if (udval < 200)
    xBeeSerial.write('D');
  else
    xBeeSerial.write('_');

  if (lrval > 700)
    xBeeSerial.write('R');
  else if (lrval < 200)
    xBeeSerial.write('L');
  else
    xBeeSerial.write('\\');

  delay(100);
}

