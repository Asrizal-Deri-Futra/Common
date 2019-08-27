#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>
#define LIGHT A3
#define WIFI_SSID   "ICT-LAB-2.4G"                       
#define WIFI_PASS   "12345678" 

int BUZZER = 6;

IoTMakers g_im;

#define deviceID    "asrizaD1566884254378"            
#define authnRqtNo  "pl4u5s6t5"            
#define extrSysID   "OPEN_TCP_001PTL001_1000007615"    

#define TAG_ID "LIGHT"
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

void setup() 
{
  Serial.begin(9600);
  pinMode(LIGHT, INPUT);
  pinMode(BUZZER, OUTPUT);
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
    send_lightdata();
    tick = millis();
  }

  g_im.loop();
}

int send_lightdata()
{
  // This Scope is package of temperature sensor
  // Raw coding (with register address) look at "5_Temperature_Sensor Project"
 // sensors.requestTemperatures();
  int value = analogRead(LIGHT);
  int data = map(value, 0, 1023, 1023, 0);

  Serial.print("LIGHT : ");
  Serial.println(data);
  
  if(g_im.send_numdata(TAG_ID, (double)data) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }
  return 0;
}

 
 
