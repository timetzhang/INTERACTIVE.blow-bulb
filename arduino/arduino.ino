#include "Keyboard.h"

int count = 13;           // count of light
String inString = "";    // string to hold input
int volume = 800;          // volume from sensor

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
  Serial1.begin(9600);

  for (int i = 2; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void loop() {
  while (Serial1.available() > 0) {
    stopShine();
    int inChar = Serial1.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      Serial.println(inString.toInt());
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
      if (millis() > actionTime + lightTime) {
        shine_status = ENDING;
        actionTime = millis();
      }
      else {
        shining();
      }
      break;
    case ENDING:
      if (millis() > actionTime + map(volume, 900, 1000, 120, 10) * count) { //开始ENDED
        actionTime = millis();
        shine_status = ENDED;
      } else {
        endShine();
      }
      break;
  }
}

void startShine() {
  Keyboard.print('a');
}

void shining() {
  for (int i = 2; i < 2 + count; i++) {
    if (millis() > actionTime + i * map(volume, 900, 1000, 120, 10)) {
      digitalWrite(i, LOW);
    }
  }
}

void endShine() {
  for (int i = 2; i < 2 + count; i++) {
    if (millis() > actionTime + i * map(volume, 900, 1000, 120, 10)) {
      digitalWrite(i, HIGH);
    }
  }
}

void stopShine() {
  shine_status = ENDED;
  for (int i = 2; i < 2 + count; i++) {
    digitalWrite(i, HIGH);
  }
}
