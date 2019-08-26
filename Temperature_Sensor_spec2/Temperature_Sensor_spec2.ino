#include <OneWire.h>  

int period = 3000;
unsigned long time_now = 0;

OneWire ds(2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  byte i;
  byte present = 0;

  byte data[12];
  byte addr[8];
  float Temp;

  if (!ds.search(addr)) {
    ds.reset_search();
    return;
  }
  
  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end
  delay(1000);

  present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad

  for (i = 0; i < 9; i++) { 
    data[i] = ds.read();
  }

  Temp=(data[1]<<8)+data[0];
  Temp=Temp/16;

  if(millis() > time_now + period){
        time_now = millis();
  // Celsius
  Serial.print("C=");
  Serial.print(Temp);
  Serial.println(", ");

}
}
