#define trigPin 13
#define echoPin 12

int redPin = 4;
int greenPin = 3;
int bluePin = 2;

int BUZZER = 6;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 17 / 1000;

  if (distance >= 200 || distance <= 0)
  {
    Serial.println("Unable to measure distance");
  }
  else
  {
    Serial.print(distance);
    Serial.println("cm");
  }
  if (distance > 30)
  {
    setColor(0, 255, 255); //blue
    delay(distance * 10);
  }
  else if (distance <= 30 && distance > 20)
  {
    setColor(255, 255, 0); //yellow
    delay(distance * 10);
  }

   else if (distance <= 20 && distance > 10)
  {
    setColor(255, 0, 0); //red
    delay(distance * 10);
  }
  else
  {
    delay(500);
  }
}

void setColor (int red, int green, int blue)
{
  analogWrite(redPin, 255 - red);
  analogWrite(greenPin, 255 - green);
  analogWrite(bluePin, 255 - blue);
}
