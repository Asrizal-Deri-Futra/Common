#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>
#define V_Sensor A0
#define TOUCH 1
#define WIFI_SSID   "ICT-LAB-2.4G"                       
#define WIFI_PASS   "12345678" 


IoTMakers g_im;

#define deviceID    "asrizaD1566352161935"            
#define authnRqtNo  "limxfod06"            
#define extrSysID   "OPEN_TCP_001PTL001_1000007615"    

#define TAG_ID "Piezo"
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
  pinMode(V_Sensor, INPUT);
  init_iotmakers();
}

void loop() {
  // put your main code here, to run repeatedly:

   static unsigned long tick = millis();

  if(g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  if((millis() - tick) > 1000)
  {
    send_vibration_sensor();
    tick = millis();
  }

  g_im.loop();
}

int send_vibration_sensor()
{
  int isTouch = digitalRead(V_Sensor);
  Serial.print (isTouch,   "   ");
  if(isTouch == 1)
  {Serial.println(" TOUCH");
  }
  else
  Serial.println(" ");
   if(g_im.send_numdata(TAG_ID, (double)isTouch) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }
  return 0;
}
