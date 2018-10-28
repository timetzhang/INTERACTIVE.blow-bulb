int count = 8;
String inString = "";    // string to hold input

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(9600);

  for (int i = 2; i < 52; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void loop() {
  while (Serial3.available() > 0) {
    int inChar = Serial3.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      Serial.println(inString.toInt());
      //START to shining
      // clear the string for new input:
      inString = "";
    }
  }
}

void startShine() {
  Serial.println(1);
  for (int i = 3; i < 3 + count; i++) {
    digitalWrite(i, LOW);
    delay(200 - i * 10);
  }
}

void endShine() {
  for (int i = 3; i < 3 + count; i++) {
    digitalWrite(i, HIGH);
    delay(200 - i * 10);
  }
}
