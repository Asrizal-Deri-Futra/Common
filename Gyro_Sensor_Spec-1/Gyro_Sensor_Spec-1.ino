#include<Wire.h>
const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0xF8);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0xF8);
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);

  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  Tmp = Wire.read() << 8 | Wire.read();
  GyX = Wire.read() << 8 | Wire.read();
  GyY = Wire.read() << 8 | Wire.read();
  GyZ = Wire.read() << 8 | Wire.read();

  int xAxis = (AcX - 1090);
  int yAxis = (AcY - 930);
  int zAxis = (AcZ - 1000);

  Serial.print(xAxis);
  Serial.print(" ");
  Serial.print(yAxis);
  Serial.print(" ");
  Serial.print(zAxis);
  Serial.println(" ");

  Serial.print(GyX);
  Serial.print(" ");
  Serial.print(GyY);
  Serial.print(" ");
  Serial.print(GyZ);
  Serial.println(" ");

  Serial.print(Tmp);
  Serial.println(" ");
  

  delay(500);
  // put your main code here, to run repeatedly:

}
