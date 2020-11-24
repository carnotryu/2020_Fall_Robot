int encA = 2;   // blue wire (encoder)
int encB = 4;   // green wire (encoder)
int dirPinA = 12;
int pwmPinA = 3;
int dira = 0;
int pwma = 150;   // 0 ~ 255 --> 0.0 V ~ 5.0 V

void setup() {
  Serial.begin(9600);
  pinMode(encA, INPUT_PULLUP);
  pinMode(encB, INPUT_PULLUP);
  pinMode(dirPinA, OUTPUT);
  pinMode(pwmPinA, OUTPUT);
  digitalWrite(dirPinA, 0);
  digitalWrite(pwmPinA, 0);
}

void loop() {

  int aa = digitalRead(encA);
  int bb = digitalRead(encB);

  Serial.print(aa);
  Serial.print("\t");
  Serial.println(bb);

  char a = Serial.read();
  if (a == '1') {
    m_cw();
  }
  else if (a == '2') {
    m_ccw();
  }
  else if (a == '3') {
    m_stop();
  }

  delay(10);

}

void m_cw() {
  digitalWrite(dirPinA, 1);
  analogWrite(pwmPinA, pwma);  
}

void m_ccw() {
  digitalWrite(dirPinA, 0);
  analogWrite(pwmPinA, pwma);    
}

void m_stop() {
  digitalWrite(dirPinA, 0);
  digitalWrite(pwmPinA, 0);  
}
