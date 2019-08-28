#include<Wire.h>
#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>

#define WIFI_SSID   "ICT-LAB-2.4G"                       
#define WIFI_PASS   "12345678" 

const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

IoTMakers g_im;

#define deviceID    "asrizaD1566354020528"            
#define authnRqtNo  "ewai9lx4c"            
#define extrSysID   "OPEN_TCP_001PTL001_1000007615"    

#define TAG_ID "GYRO"
//Initialize IoT Makers connection


void init_iotmakers()

{
  while(1)
  {
    Serial.print(F("Connect to AP..."));
    while(g_im.begin(WIFI_SSID, WIFI_PASS) < 0)
    {
      Serial.println(F("retrying"));
      delay(100);
    }

    Serial.println(F("Success"));

    g_im.init(deviceID, authnRqtNo, extrSysID);
  
    Serial.print(F("Connect to platform..."));
    while(g_im.connect() < 0)
    {
      Serial.println(F("retrying."));
      delay(100);
    }
    Serial.println(F("Success"));
  
    Serial.print(F("Auth..."));
    if(g_im.auth_device() >= 0)
    {
      Serial.println(F("Success..."));
      return;
    }
  }
}

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
  init_iotmakers();
}

void loop() {
   static unsigned long tick = millis();

  if(g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  if((millis() - tick) > 1000)
  {
    send_gyro();
    tick = millis();
  }

  g_im.loop();
}

int send_gyro()
{
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
  

  if(g_im.send_numdata(TAG_ID, (double)xAxis) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }
   if(g_im.send_numdata(TAG_ID, (double)yAxis) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }
  if(g_im.send_numdata(TAG_ID, (double)zAxis) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }
  if(g_im.send_numdata(TAG_ID, (double)GyX) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }
  if(g_im.send_numdata(TAG_ID, (double)GyY) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }
  if(g_im.send_numdata(TAG_ID, (double)GyZ) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }
   if(g_im.send_numdata(TAG_ID, (double)Tmp) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }
  return 0;

}
