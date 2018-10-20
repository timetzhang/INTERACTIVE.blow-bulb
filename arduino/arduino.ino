#define MIC A0
#define LED 2

uint8_t Brightness = 0;
uint8_t Fadeness = 1;
uint8_t count = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(MIC, INPUT);
  pinMode(LED, OUTPUT);
  for(int i=3; i<52; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void loop() {

  int micDyn = analogRead(MIC);
  if (micDyn > 1000) {
    startShine();
    delay(30);
    endShine();
  }
  else {

    Brightness = Brightness + Fadeness;
    if (Brightness <= 0 || Brightness >= 100) {
      Fadeness = -Fadeness;
    }
    analogWrite(LED, Brightness);
    delay(20);
  }
}

void startShine() {
  Serial.println(1);
  for (int i = 3; i < 3 + count; i++) {
    digitalWrite(i, LOW);
    delay(200-i*10);
  }
}

void endShine() {
  for (int i = 3; i < 3 + count; i++) {
    digitalWrite(i, HIGH);
    delay(200-i*10);
  }
}
