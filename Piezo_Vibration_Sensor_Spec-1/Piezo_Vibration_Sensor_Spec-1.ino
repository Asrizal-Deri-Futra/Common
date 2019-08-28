#define V_Sensor A0
#define TOUCH 1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(V_Sensor, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int isTouch = digitalRead(V_Sensor);
  Serial.print (isTouch,   "   ");
  if(isTouch == 1)
  {Serial.println(" TOUCH");
  }
  else
  Serial.println(" ");
  delay(1000);
}
