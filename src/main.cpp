
#include <Arduino.h>
#include <HC-SR04.h>

const int Trig = 16;
const int Echo = 17;

Rangefinder rangefinder;

void setup()
{
  delay(1000);
  
  Serial.begin(115200);
  Serial.println("Velkommen til");

  rangefinder.attach(Trig, Echo);
}

void loop() 
{
  Serial.print("Distance: ");
  Serial.print(rangefinder.getDistanceCM());
}