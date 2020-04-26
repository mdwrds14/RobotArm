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
 
int vala[3]; //x,y,z


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
 
void setup()
{
    Wire.write(0x6B);
    Wire.write(0);
    Wire.begin();
    Serial.begin(115200);
    Serial.println("Initialize MPU");
    mpu.initialize();
    Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening(); 
//    radio.setDataRate(RF24_250KBPS);
}
 
void loop()
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  vala[0] = map(ax, -17000, 17000, 0, 255);//x
  vala[1] = map(ay, -17000, 17000, 0, 255);//y
  vala[2] = map(az, -17000, 17000, 0, 255);//z
  Serial.println("ax: ");
  Serial.println(vala[0]);
  Serial.println("ay:");
  Serial.println(vala[1]);
  Serial.println("az: ");
  Serial.println(vala[2]);
  Serial.println("");
  Serial.println("");
  radio.write(vala,sizeof(vala));// transmit data
  
  delay(500);

}
