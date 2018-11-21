const int LAMP_COUNT = 32;
const int LAMP_START_PIN = 22;
const int VOLUME_MIN = 450;
const int VOLUME_MAX = 600;

String inString = "";    // string to hold input
int volume = 1000;          // volume from sensor

unsigned long actionTime;
int lightTime = 2000;    // the time last of light on

enum SHINE_STATUS {
  STARTING,
  ENDING,
  ENDED
};
SHINE_STATUS shine_status = ENDED;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(9600);

  for (int i = LAMP_START_PIN; i < LAMP_START_PIN + LAMP_COUNT; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void loop() {
  while (Serial3.available() > 0) {
    stopShine();
    int inChar = Serial3.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      //START to shining
      shine_status = STARTING;
      volume = inString.toInt();
      actionTime = millis();
      startShine(); //play sound
      // clear the string for new input:
      inString = "";
    }
  }

  switch (shine_status) {
    case STARTING:
      //开始ENDING,如果已经亮了2000ms, 开始关灯
      if (millis() > actionTime + lightTime + int(map(volume, VOLUME_MIN, VOLUME_MAX, 60, 20)) * LAMP_COUNT) {
        shine_status = ENDING;
        actionTime = millis();
      }
      else {
        shining();
      }
      break;
    case ENDING:
      if (millis() > actionTime + int(map(volume, VOLUME_MIN, VOLUME_MAX, 30, 10)) * LAMP_COUNT) { //开始ENDED
        actionTime = millis();
        shine_status = ENDED;
      } else {
        endShine();
      }
      break;
  }
}

void startShine() {
  Serial.println('1');
}

void shining() {
  for (int i = 0; i < LAMP_COUNT; i++) {
    if (millis() > actionTime + i * int(map(volume, VOLUME_MIN, VOLUME_MAX, 60, 20))) {
      digitalWrite(i + LAMP_START_PIN, LOW);
    }
  }
}

void endShine() {
  for (int i = 0; i < LAMP_COUNT; i++) {
    if (millis() > actionTime + i * int(map(volume, VOLUME_MIN, VOLUME_MAX, 30, 10))) {
      digitalWrite(i + LAMP_START_PIN, HIGH);
    }
  }
}

void stopShine() {
  shine_status = ENDED;
  for (int i = LAMP_START_PIN; i < LAMP_START_PIN + LAMP_COUNT; i++) {
    digitalWrite(i, HIGH);
  }
}
