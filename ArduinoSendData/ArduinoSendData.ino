#include <Servo.h>

// setup function to initialize hardware and software


Servo Servo1;
Servo Servo2;

const int STEP = 1;                     //move one degree between scans
int baudRate = 9600;                 // NOTE1: The baudRate for sending & receiving programs must match

const int SENSOR = A2;

const int servoPin = 3;
const int servoPin2= 10;

const int potPin1 = A3;
const int potPin2 = A4;

int var;
int vas;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // start the serial port
  Serial.begin(baudRate);               // NOTE2: Set the baudRate to 115200 for faster communication
  Servo1.attach(servoPin);
  Servo2.attach(servoPin2);
//  pan(0);
//  tilt(0);
}



///


/////////////////////////////////// main loop /////////////////////////////////////////

void loop()
{  
  int a, b, c, d;
//
  a = 0;
  b = 0;
  c = 0;
  d = 0;

  //
  // loop: calculate the data, then send it from the Arduino to the phython program
  //
//  /

  var = analogRead(potPin1);            //reads the potentiomeeter with a value between 1 to 1023
  var = map(var, 0, 1023, 0, 179);      //scale it using the servo with values between 0 and 180

  Servo1.write(var);                    //Sets the servo position according to the scaled values 
  Serial.println(var);                  //output the value
  delay(15);                            //waits for the servo to get there

  vas = analogRead(potPin2);
  vas = map(vas, 0, 1023, 0, 179);
  
  Servo2.write(vas);                    //Sets the servo position according to the scaled values 
  Serial.println(vas);                  //output the value
  delay(15);                            //waits for the servo to get there
  
///
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

///
