#include <Servo.h>
#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>

#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"

int angle = 0;

IoTMakers g_im;

#define deviceID    "asrizaD1566786136257"
#define authnRqtNo  "ob68u6jkn"
#define extrSysID   "OPEN_TCP_001PTL001_1000007615"

#define TAG_ID "Servo"
//Initialize IoT Makers connection
void init_iotmakers()
{
  while (1)
  {
    Serial.print(F("Connect to AP..."));
    while (g_im.begin(WIFI_SSID, WIFI_PASS) < 0)
    {
      Serial.println(F("retrying"));
      delay(100);
    }

    Serial.println(F("Success"));

    g_im.init(deviceID, authnRqtNo, extrSysID);

    Serial.print(F("Connect to platform..."));
    while (g_im.connect() < 0)
    {
      Serial.println(F("retrying."));
      delay(100);
    }
    Serial.println(F("Success"));

    Serial.print(F("Auth..."));
    if (g_im.auth_device() >= 0)
    {
      Serial.println(F("Success..."));
      return;
    }
  }
}

Servo myServo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(3);
  init_iotmakers();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (angle = 0; angle < 180; angle++) {
    myServo.write(angle);
    delay(15);
    static unsigned long tick = millis();
    if (g_im.isServerDisconnected() == 1) {
      init_iotmakers();
    }
    if ((millis() - tick) > 500) {
      send_data();
      tick = millis();
    }
    g_im.loop();
    //Serial.println(angle);

  }
  for (angle = 180; angle > 0; angle--) {
    myServo.write(angle);
    //Serial.println(angle);
    delay(15);

    static unsigned long tick = millis();
    if (g_im.isServerDisconnected() == 1)
    {
      init_iotmakers();
    }
    if ((millis() - tick) > 500) {
      send_data();
      tick = millis();
    }
    g_im.loop();
    //Serial.println(angle);
  }
}

int send_data()
{
  // This Scope is package of temperature sensor
  // Raw coding (with register address) look at "5_Temperature_Sensor Project"
 // sensors.requestTemperatures();
 
  Serial.println(angle);
  
  if(g_im.send_numdata(TAG_ID, (double)angle) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }
  return 0;
}
