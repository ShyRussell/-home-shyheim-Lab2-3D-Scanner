#include <Servo.h>

// setup function to initialize hardware and software


Servo Servo1;
Servo Servo2;

int baudRate = 9600;                 // NOTE1: The baudRate for sending & receiving programs must match

const int SENSOR = 4;

const int servoPin = 3;
const int servoPin2= 10;

int sensorVal = 0;                          // variable to storw the value coming from the sensor, set to 0 initially
int pos = 180;
int value = 0;

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
   /// Infrared Distance Sensor Calibration code

    value = analogRead(SENSOR);
    Serial.println(value);
    delay(100);
    

///////////////////////////////////////////////////////////////////////////////////////////////////
  ///Servo1 Movement on its own 
  
   for(pos = 0; pos < 180; pos += 1)           // goes from 0 degrees to 180 degrees
  {                                            // in steps of 1 degree
    Servo1.write(pos);                         // tell servo to go to position in variable 'pos'
    delay(15);                                 // waits 15ms for the servo to reach the position
    Servo2.write(pos);
    delay(15);
  }
  for(pos = 180; pos>=1; pos-=1)                // goes from 180 degrees to 0 degrees
  {                               
    Servo1.write(pos);                          // tell servo to go to position in variable 'pos'
    delay(15);                                  // waits 15ms for the servo to reach the position
    Servo2.write(pos);
    delay(15);
  }}
///////////////////////////////////////////////////////////////////////////////////////////////////


  


/////////////////////////////////////////////////////////////////////////////////////////////////////////

///
