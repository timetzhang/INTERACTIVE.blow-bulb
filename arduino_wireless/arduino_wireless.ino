#define MIC A3
#define LED 3

uint8_t Brightness = 0;
uint8_t Fadeness = 1;
uint8_t count = 8;

uint64_t micTime;
uint64_t ledTime;
bool micReady = true;



void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);

  analogReference(INTERNAL);

  pinMode(MIC, INPUT);
  pinMode(LED, OUTPUT);

  ledTime = millis();
  micTime = millis();
}

void loop() {

  int micDyn = analogRead(MIC);
  if (micDyn > 650 && micReady) {
    micReady = false;
    micTime = millis();
    //Serial.println(micDyn);
    Serial1.println(micDyn);
  }
  if (millis() > micTime + 300) {
    micReady = true;
  }

  if (micReady) {
    breath(10, 100);
  } else {
    breath(1, 100);
  }
}

void breath(int delayTime, int maxBrightness) {
  analogWrite(LED, Brightness);
  if (millis() > ledTime + delayTime) {
    ledTime = millis();
    Brightness = Brightness + Fadeness;
    if (Brightness <= 0 || Brightness >= maxBrightness) {
      Fadeness = -Fadeness;
    }
  }
}
