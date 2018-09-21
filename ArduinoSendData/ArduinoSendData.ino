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
int pos = 9;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // start the serial port
  Serial.begin(baudRate);               // NOTE2: Set the baudRate to 115200 for faster communication
  Servo1.attach(servoPin);
  Servo2.attach(servoPin2);
}


//


/////////////////////////////////// main loop /////////////////////////////////////////

void loop()
{  
   ///Servo Movement with potentiometer
    
//  var = analogRead(potPin1);            //reads the potentiomeeter with a value between 1 to 1023
//  var = map(var, 0, 1023, 0, 179);      //scale it using the servo with values between 0 and 180
//
//  Servo1.write(var);                    //Sets the servo position according to the scaled values 
//  Serial.println(var);                  //output the value
//  delay(15);                            //waits for the servo to get there
//
//  vas = analogRead(potPin2);
//  vas = map(vas, 0, 1023, 0, 179);
//  
//  Servo2.write(vas);                    //Sets the servo position according to the scaled values 
//  Serial.println(vas);                  //output the value
//  delay(15);                            //waits for the servo to get there

///////////////////////////////////////////////////////////////////////////////////////////////////
  ///Servo1 Movement on its own 
  
   for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees
  {                                  // in steps of 1 degree
    Servo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees
  {                               
    Servo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
///////////////////////////////////////////////////////////////////////////////////////////////////
  ///Servo2 Movemnt on its own
  
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees
  {                                  // in steps of 1 degree
    Servo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees
  {                               
    Servo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
///
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

///
