#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

#include <MPU6050.h>
#include <I2Cdev.h>
#include <Wire.h>;
 
 
MPU6050 mpu;
 
int16_t ax, ay, az;
int16_t gx, gy, gz;
const int MPU_addr = 0x68; 
 
 
int val;
int prevVal;
 
int valax; 
int valay;
int valaz;

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "0000A";
 
void setup()
{
    Wire.write(0x6B);
    Wire.write(0);
    Wire.begin();
    Serial.begin(38400);
    Serial.println("Initialize MPU");
    mpu.initialize();
    Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();
}
 
void loop()
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  valax = map(ax, -17000, 17000, 0, 255) ;
  valay = map(ay, -17000, 17000, 0, 255);
  valaz = map(az, -17000, 17000, 0, 255);
  Serial.println("ax: ");
  Serial.println(valax);
  Serial.println("ay:");
  Serial.println(valay);
  Serial.println("az: ");
  Serial.println(valaz);
  Serial.println("");
  Serial.println("");
  delay(1000);

  radio.write(&valax, sizeof(valax));
  radio.write(&valay, sizeof(valay));
  radio.write(&valaz, sizeof(valaz));
  delay(500);
}
