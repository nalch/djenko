int incomingByte = 0; // for incoming serial data

int PIN_GREEN = 4;
int PIN_YELLOW = 3;
int PIN_RED = 2;

void setup() {

  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_RED, OUTPUT);

  Serial.begin(9600);

}



void loop() {

  if (Serial.available() > 0) {
    incomingByte = Serial.read();
  }

  if (incomingByte == 'g') {
    green();
  } else if (incomingByte == 'y') {
    yellow();
  } else if (incomingByte == 'r') {
    red();
  } else if (incomingByte == 'a') {
    all();
  }

}

void green() {

  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_YELLOW, LOW);
  digitalWrite(PIN_RED, LOW);
  delay(1000);

}

void yellow() {

  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_YELLOW, HIGH);
  digitalWrite(PIN_RED, LOW);
  delay(1000);

}

void red() {

  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_YELLOW, LOW);
  digitalWrite(PIN_RED, HIGH);
  delay(1000);

}

void all() {

  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_YELLOW, HIGH);
  digitalWrite(PIN_RED, HIGH);
  delay(1000);

}
