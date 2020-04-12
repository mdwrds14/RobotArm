#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <accelerate.h> 

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
RF24 radio(8, 9); // CE, CSN
const byte address[6] = "0000A"; // assign the channel

int servo1Pos, servo2Pos, servo3Pos, servo4Pos, servo5Pos, servo6Pos; // current position
int servo1PPos, servo2PPos, servo3PPos, servo4PPos, servo5PPos, servo6PPos; // previous position
int servo01SP[50], servo02SP[50], servo03SP[50], servo04SP[50], servo05SP[50], servo06SP[50]; // for storing positions/steps
int speedDelay = 20;
int index = 0;
String dataIn = "";

void setup() {
  Serial.begin(9600);
  
  servo1.attach(2); // waist
  servo2.attach(3); // shoulder
  servo3.attach(4); // elbow
  servo4.attach(5); // wrist roll
  servo5.attach(6); // wrist pitch
  servo6.attach(7); // grabber
  // Robot arm initial position
  // servo1PPos = 90;
  //servo1.write(servo1PPos);
  servo2PPos = 180;
  servo2.write(servo2PPos);
  delay(100);
  servo3PPos = 100;
  servo3.write(servo3PPos);
  delay(100);
  servo4PPos = 90;
  servo4.write(servo4PPos);
  delay(100);
  servo5PPos = 10;
  servo5.write(servo5PPos);
  delay(100);
  servo6PPos = 80;
  servo6.write(servo6PPos);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  
  if (radio.available()) {
    char valax[32] = "";
    char valay[32] = "";
    char valaz[32] = ""; 
    radio.write(&valax, sizeof(valax));
    radio.write(&valay, sizeof(valay));
    radio.write(&valaz, sizeof(valaz));
    Serial.println(valax);
    Serial.println(valay);
    Serial.println(valaz);
  }

  
}
