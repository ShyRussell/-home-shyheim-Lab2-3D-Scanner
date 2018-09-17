#include <Servo.h>

// setup function to initialize hardware and software


Servo Servo1;
Servo Servo2;

const int STEP = 1;                     //move one degree between scans
//

const int SENSOR = A2;

const int servoPin = 3;
const int servoPin2= 10;
const int potPin1 = A3;
const int potPin2 = 9;
int var;

void setup() {
  // start the serial port
  long baudRate = 9600;                 // NOTE1: The baudRate for sending & receiving programs must match
  Serial.begin(baudRate);               // NOTE2: Set the baudRate to 115200 for faster communication
  Servo1.attach(servoPin);
  Servo2.attach(servoPin2);
  pan(0);
  tilt(0);
}



void scan(int resolution){
  int column = -30;                      // current state of the pan servo
  double val;                            // distance sensor result stored here

  pan(column);
  tilt(0);                               // set initial position of servos

  // do all the scanning
  while(column < 30) {

    //scan direction 1
    for(float d1 = -10; d1 < 50; d1 += STEP){
      tilt(d1);                         //scans one direction horizontally
      val = getDistance();
      
      Serial.print(d1);
      Serial.print(",");
      Serial.print(column);
      Serial.print(",");
      Serial.println(val);
      delay(50);
    }
    column += STEP;
    pan(column);                        //move over one step
    delay(50);

    //scans in the other direction
    for(int d2 = 50; d2 > -10; d2 -= STEP){ 
      tilt(d2);
      val = getDistance();
      
      Serial.print(d2);
      Serial.print(",");
      Serial.print(column);
      Serial.print(",");
      Serial.println(val);
      delay(50);
    }
    column += STEP;
    pan(column);
    delay(50);
  }                                     // end scanning loop
  
    pan(0);                             // reset to pointing straight ahead
    tilt(0);                            // (mostly for show)
}

//
// main loop
//
void loop()
{  
//  int a, b, c, d;
//
//  a = 0;
//  b = 0;
//  c = 0;
//  d = 0;
//
//  //
//  // loop: calculate the data, then send it from the Arduino to the phython program
//  //
//  while(true) {
//    //
//    // here is where you update the data to be sent
//    //
//    a = a + 1;    // a counts by 1s
//    b = b + 2;    // b counts by 2s
//    c = c + 3;    // c counts by 3s
//    d = d + 4;    // d counts by 4s
//
//
//    //
//    // transmit one line of text to phython with 4 numeric values
//    // NOTE: commas are sent between values, after the last value a Newline is sent
//    //
//    Serial.print(a);    Serial.print(",");
//    Serial.print(b);    Serial.print(",");
//    Serial.print(c);    Serial.print(",");
//    Serial.println(d);
//
//
//    //
//    // delay after sending data so the serial connection is not over run
//    //
//    delay(400);
//  }

  var = analogRead(potPin1);            //reads the potentiomeeter with a value between 1 to 1023
  var = map(var, 0, 1023, 0, 179);      //scale it using the servo with values between 0 and 180

  Servo1.write(var);                    //Sets the servo position according to the scaled values 
  Serial.println(var);                  //output the value
  delay(15);                            //waits for the servo to get there
  
  establishContact(); // wait until a keypress comes across the line
  while (Serial.available() > 0) 
  {
    // empty the serial buffer
    char inByte = Serial.read();
  }
  // begin the scan
  scan(10);
}

bool pan(int deg) {
  // deg as in degrees
  // Pan to the correct angle - include calibration
    
  if(deg < -30 || deg > 30) {
                                        // outside of bounds
    return false;
  }

  deg += 43;                            // take calibration into account
  Servo1.write(deg);
  Serial.print(deg);
  return true;                          // if successful
}

bool tilt(int deg) {
  // Tilt to the correct angle - include calibration
  
  if(deg < -10 || deg > 90) {
    // outside of bounds
    return false;
  }
  
  deg = -deg;
  deg += 157;                           // take calibration into account
  Servo2.write(deg);
  Serial.print(deg);
  return true;                          // if successful
}
void establishContact() {
  while (Serial.available() <= 0) {
    delay(500);
  }
}

double getDistance() {
  double distance;
  distance = analogRead(SENSOR);
  delay(10);
  distance += analogRead(SENSOR);
  delay(10);
  distance += analogRead(SENSOR);
  delay(10);
  
  distance = distance / 3.0;
  
  // fit on the calibration data (calculated in Matlab)
  // y = p1*x^4 + p2*x^3 + p3*x^2 + p4*x + p5 

  //  Coefficients:
  //    p1 = 1.7565e-09
  //    p2 = -3.1001e-06
  //    p3 = 0.0020337
  //    p4 = -0.62428
  //    p5 = 89.447
  
  distance = 1.7565e-09 * pow(distance,4) + -3.1001e-06 * pow(distance,3) + 0.0020337 * pow(distance,2) + -0.62428 * distance + 89.447;
  
  // returns distance in inches
  return distance;
}
