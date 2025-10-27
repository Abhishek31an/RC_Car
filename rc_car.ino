// Motor and sensor pins
int in1 = 2;
int in2 = 3;
int in3 = 4;
int in4 = 7;
int enable1 = 5;
int enable2 = 6;

// Receiver Channel Inputs
int channel_1 = 9;  //for left right
int channel_3 = A1; //for forward backward (MOVED from 10)
int channel_7 = 12; //for head led
int channel_8 = 8;  //for ground led (MOVED from 11)
int channel_10 = 13; //for back led

// Accessory Outputs
int hled = 10; //head led (Stays on 10)
int gled = A0; //ground led
int bled = A2; //back led
int buzzer = 11; //siren buzzer (Stays on 11)

// Variables
int pwm1;
int pwm3;
int pwm7;
int pwm10;
int bs = 120;
int i, k, ls, rs;
int ch1, ch3, ch7, ch10, ch8;

void setup() {
  // Set Input Pins (Receiver)
  pinMode(channel_1, INPUT);
  pinMode(channel_3, INPUT);
  pinMode(channel_7, INPUT);
  pinMode(channel_8, INPUT);
  pinMode(channel_10, INPUT);

  // Set Output Pins (Motors)
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);

  // Set Output Pins (Accessories)
  pinMode(hled, OUTPUT);
  pinMode(gled, OUTPUT);
  pinMode(bled, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  
  //One time show
  tone(buzzer, 1000);
  analogWrite(hled, 255);
  digitalWrite(gled, LOW);
  delay(500);
  noTone(buzzer);
  analogWrite(hled, 0);
  digitalWrite(gled, HIGH);
  delay(500);
  tone(buzzer, 1000);
  analogWrite(hled, 255);
  digitalWrite(gled, LOW);
  delay(500);
  noTone(buzzer);
  analogWrite(hled, 0);
  digitalWrite(gled, HIGH);
  delay(500);
  //show end
}

//Police siren sound
void siren() {
  // Play siren sound
  for (int i = 500; i < 1000; i++) {
    tone(buzzer, i);
    delay(5);
  }
  for (int i = 999; i > 500; i--) {
    tone( buzzer, i);
    delay(5);
  }
}
//Car horn sound
void horn() {
  // Play horn sound
  tone(buzzer, 500);
  delay(500);
  tone(buzzer, 1000);
  delay(500);
}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(bled, HIGH);
  delay(50);
  digitalWrite(bled, LOW);
  delay(50);
}

void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enable1, 0);
  analogWrite(enable2, 0);
}

void loop() {
  int ch1 = pulseIn(channel_1, HIGH);
  int ch3 = pulseIn(channel_3, HIGH);
  int ch7 = pulseIn(channel_7, HIGH);
  int ch8 = pulseIn(channel_8, HIGH);
  int ch10 = pulseIn(channel_10, HIGH);

  //For hled brightness
  pwm10 = map(ch10, 990, 1990, 0, 255);
  analogWrite(hled, pwm10);

  //for buzzer
  if (ch7 >= 1485 && ch7 <= 1490)
    horn();
  else if (ch7 >= 1985)
    siren();
  else
    noTone(buzzer);

  //For gled
  if (ch8 >= 1980) {
    digitalWrite(gled, LOW);
  }
  else
    digitalWrite(gled, HIGH);

  //Forward
  if (ch3 >= 1520 && ch3 <= 1990) {
    k = map(ch3, 1510, 1990, 0, 80);
  }

  //Left
  if (ch1 > 1510 && ch1 <= 1990) {
    i = map(ch1, 1510, 1990, 0, 70);
    left();
    rs = bs + i + k;
    ls = bs - i + k;
    ls = constrain(ls, 0, 255);
    rs = constrain(rs, 0, 255);
    analogWrite(enable1, ls);
    analogWrite(enable2, rs);
  }
  //Middele
  if (ch1 > 1470 && ch1 < 1510) {
    forward();
    i = 70;
    rs = bs + i + k;
    ls = bs + i + k;
    ls = constrain(ls, 0, 255);
    rs = constrain(rs, 0, 255);
    analogWrite(enable1, ls);
    analogWrite(enable2, rs);
  }
  //Right
  if (ch1 >= 997 && ch1 <= 1470) {
    i = map(ch1, 1470, 997, 0, 70);
    right();
    rs = bs - i + k;
    ls = bs + i + k;
    ls = constrain(ls, 0, 255);
    rs = constrain(rs, 0, 255);
    analogWrite(enable1, ls);
    analogWrite(enable2, rs);
  }
  //Stop
  if (ch3 > 1470 && ch3 < 1520) {
    stop();
  }
  //Backward
  if (ch3 <= 1470 && ch3 >= 1000) {
    pwm3 = map(ch3, 1470, 1000, 30, 255);
    backward();
    analogWrite(enable1, pwm3);
    analogWrite(enable2, pwm3);
  }
  delay(10);
}