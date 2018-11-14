#include "Keyboard.h"
#include <CD74HC4067.h>

CD74HC4067 muxA(9, 10, 11, 12);  // create a new CD74HC4067 object with its four control pins
CD74HC4067 muxB(3, 4, 5, 6);  // create a new CD74HC4067 object with its four control pins
const int muxA_SIG = 8; // select a pin to share with the 16 channels of the CD74HC4067
const int muxB_SIG = 2; // select a pin to share with the 16 channels of the CD74HC4067


int count = 32;           // count of light
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

  //Init 74HC4067
  pinMode(muxA_SIG, OUTPUT);
  pinMode(muxB_SIG, OUTPUT);
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
      if (millis() > actionTime + map(volume, 900, 1000, 120, 10) * 2*count) { //开始ENDED
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
  digitalWrite(muxA_SIG, LOW);
  for (int i = 0; i < 16; i++) {
    if (millis() > actionTime + i * map(volume, 900, 1000, 120, 10)) {
      muxA.channel(i);
    }
  }
  digitalWrite(muxB_SIG, LOW);
  for (int i = 0; i < 16; i++) {
    if (millis() > actionTime + (i + 16) * map(volume, 900, 1000, 120, 10)) {
      muxB.channel(i);
    }
  }
}

void endShine() {
  digitalWrite(muxA_SIG, HIGH);
  for (int i = 0; i < 16; i++) {
    if (millis() > actionTime + i * map(volume, 900, 1000, 120, 10)) {
      muxA.channel(i);
    }
  }
  digitalWrite(muxB_SIG, HIGH);
  for (int i = 0; i < 16; iAAAAA) {
    if (millis() > actionTime + (i + 16) * map(volume, 900, 1000, 120, 10)) {
      muxB.channel(i);
    }
  }
}

void stopShine() {
  shine_status = ENDED;
  digitalWrite(muxA_SIG, HIGH);
  digitalWrite(muxB_SIG, HIGH);
  for (int i = 0; i < 16; ++i) {
    muxA.channel(i);
    muxB.channel(i);
  }
}
