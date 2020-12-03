#include <PID_v1.h>

float pulses;
int pulsesChanged;
int encA = 2;   // blue wire
int encB = 4;
int dirPinA = 12, pwmPinA = 3;
float ang = 0.0, rev = 0.0;
int stop_flag = 0;
int out_low = 40;

double Setpoint = 0.0, Input = 0.0, Output = 0.0;

// ***** TUNE THREE VALUES BELOW ***** //
float Kp = 1.0;
float Ki = 0.0;
float Kd = 0.0;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(9600);
  pinMode(encA, INPUT_PULLUP);
  pinMode(encB, INPUT_PULLUP);

  attachInterrupt(0, A_CHANGE, CHANGE);
  
  pinMode(dirPinA, OUTPUT);
  pinMode(pwmPinA, OUTPUT);
  digitalWrite(dirPinA, 0);
  digitalWrite(pwmPinA, 0);

  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(10);
  myPID.SetOutputLimits(-255, 255);

  Serial.print(Setpoint);
  Serial.print("\t");
  Serial.println(ang);  
}

void loop() {
  ang = pulses / 1960 * 360;
  Input = ang;
  myPID.Compute();

  if (Output > 0) {
    if (Output < out_low)  Output = out_low;
    digitalWrite(dirPinA, 1);
  }
  else if (Output < 0) {
    if (Output > -out_low) Output = -out_low;
    digitalWrite(dirPinA, 0);
  }
  
  if (stop_flag != 0)  analogWrite(pwmPinA, abs(int(Output)));
  else  analogWrite(pwmPinA, 0);

  char a = Serial.read();
  if (a == '1') {
    stop_flag = 1;
    Setpoint = 0.0;
  }
  else if (a == '2') {
    stop_flag = 1;
    Setpoint = 180.0;
  }
  else if (a == '3') {
    stop_flag = 1;
    Setpoint = 360.0;
  }
  else if (a == '4') {
    stop_flag = 0;
  }
  
  Serial.print(Setpoint);
  Serial.print("\t");
  Serial.println(ang);

  delay(10);
}

void A_CHANGE() {                                     
  if ( digitalRead(encB) == 0 ) {
    if ( digitalRead(encA) == 0 ) {
      // A fall, B is low
      pulses--; // Moving CCW
    } else {
      // A rise, B is low
      pulses++; // Moving CW
    }
  } else {
    if ( digitalRead(encA) == 0 ) {
      // A fall, B is high
      pulses++; // Moving CW
    } else {
      // A rise, B is high
      pulses--; // Moving CCW
    }
  }
  //pulsesChanged = 1;
}
