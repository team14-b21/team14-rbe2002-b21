#include <Arduino.h>
#include <map>
#include "HC-SR04.h"
#include "SharpIR.h"
#include "RBE-200n-Lib.h"
#include "StandoffController.h"
#include "Chassis.h"
#include "Filters.h"
#include "IRDecoder.h"

const float Kp = 3;
const float Ki = 0;
const float Kd = 5;

float dist = 0;
// StandoffController standoff = StandoffController(2);
AvgFilter<float, 5> ultraFilter;
float accumulator = 0;
float setPoint = 15;
float error;
float lastError = 0;
float speed = 25;
float diff = 0;
float lastT = 0;
bool stopped = true;

IRDecoder decoder(15);

//IR Codes
const int Forward = -100286720;
const int Backward = -233980160;
const int Stop = -167133440;
int keyPressed = 0;
int lastKeyPressed = 0;
std::map<int, int> keyMap = { {16, 1}, {17, 2}, {18, 3}, {20, 4}, {21, 5}, {22, 6}, {24, 7}, {25, 8}, {26, 9} };

void setup()
{
  delay(100);
  ir_1.init();
  delay(100);
  decoder.init();
  delay(100);
  chassis.init();

  Serial.begin(115200);
  Serial.println("Velkommen til");
}


void loop() {
  if (ir_1.getDistance(dist)) {
    ultraFilter.addDatum(dist);
    lastError = error;
    error = ultraFilter.getAvg() - setPoint;
    accumulator += error*0.1;
    diff = Kp * error + Ki * accumulator - (Kd * (error - lastError))/(millis() - lastT);
    /*Serial.print(Kp * error);
    Serial.print("\t|\t");
    Serial.print(Ki * accumulator);
    Serial.print("\t|\t");
    Serial.print(Kd * (error - lastError));
    Serial.print("\t|\t");
    Serial.println(error);*/
    lastT = millis();
    Serial.println(dist);
    diff = constrain(diff, -20, 20);
    if (!stopped)
      chassis.setWheelSpeeds(16.37*(speed+diff), 16.37*(speed-diff));
  }

  keyPressed = decoder.getKeyCode();
  if (keyPressed > 0) {
    Serial.println(keyPressed);
    switch (keyPressed) {
      case 5:
        if (speed >= 5) {
          speed -= 5;
        }
        break;
      case 13:
        if (speed <= 50) {
          speed += 5;
        }
        break;
      case 6:
        stopped = !stopped;
        if (stopped) chassis.stop();
        break;
      default:
        if (keyPressed >= 16 && keyPressed <= 26) {
          setPoint = keyMap[keyPressed] * 5;
        }
        if (stopped) stopped = !stopped;
        break;
    }
  }
}

/*
void loop()
{
  if (!digitalRead(0)) {
    for (int i = 0; i < 200;) {
      uint16_t irResult = ir_1.readMCP3002();
      if (irResult) {
        Serial.println(irResult);
        i++;
      }
    }
  }
}
*/