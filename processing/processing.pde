import processing.serial.*;
import ddf.minim.*;
import ddf.minim.ugens.*;

Minim          minim;
AudioOutput    audioOut;
AudioPlayer[]  sound = new AudioPlayer[4];

Serial         myPort;

void setup() {
  //init serial port
  String portName = Serial.list()[1];
  println(portName);
  myPort = new Serial(this, portName, 9600);
  
  initSound();
}

void draw() {
  if (myPort.available()>0) {
    println(myPort.readString().trim());
    int rnd = int(random(0,4));
    sound[rnd].play();
    sound[rnd].rewind();
  }
}

void initSound() {
  minim = new Minim(this);
  sound[0] = minim.loadFile("1.mp3");
  sound[1] = minim.loadFile("2.mp3");
  sound[2] = minim.loadFile("3.mp3");
  sound[3] = minim.loadFile("4.mp3");
}
