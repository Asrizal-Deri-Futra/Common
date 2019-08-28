#include <Servo.h>
Servo myServo;
int angle = 0;
int ulang = 0;
unsigned long start, finished, elapsed;

void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(3);
}

void loop() 
{
  start = millis();
  
  Serial.print("Start : ");
  Serial.println(start);
  
  for(int ulang = 0; ulang < 10; ulang++){  
  // put your main code here, to run repeatedly:
for(angle = 0; angle < 180; angle++){
  myServo.write(angle);
  //Serial.println(angle);
  delay(10);
}
 for(angle = 180; angle > 0; angle--){
  myServo.write(angle);
  //Serial.println(angle);
  delay(10); 
 }
 }
  finished = millis();
  Serial.print("finished : ");
  Serial.println(finished);
  elapsed = finished-start;
  Serial.print("elapsed : ");
  Serial.print(elapsed);
  Serial.println("  milliseconds");
  Serial.println(" ");
}
