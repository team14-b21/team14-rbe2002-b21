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
const float Ki = 0.3;
const float Kd = 4;

float dist = 0;
// StandoffController standoff = StandoffController(2);
AvgFilter<float, 5> ultraFilter;
float accumulator = 0;
float setPoint = 50;
float error;
float lastError = 0;
float speed = 50;
float diff = 0;
bool stopped = false;

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
  hcsr_1.init();
  delay(100);
  decoder.init();
  delay(100);
  chassis.init();

  Serial.begin(115200);
  Serial.println("Velkommen til");
}


void loop() {
  hcsr_1.checkPingTimer();
  if (hcsr_1.getDistance(dist)) {
    ultraFilter.addDatum(dist);
    lastError = error;
    error = dist - setPoint;
    accumulator += error*0.1;
    speed = Kp * error + Ki * accumulator - Kd * (error - lastError);
    Serial.print(Kp * error);
    Serial.print("\t|\t");
    Serial.print(Ki * accumulator);
    Serial.print("\t|\t");
    Serial.print(Kd * (error - lastError));
    Serial.print("\t|\t");
    Serial.println(error);
    if (!stopped)
      chassis.setMotorEfforts(speed, speed);
  }

  keyPressed = decoder.getKeyCode();
  if (keyPressed > 0) {
    Serial.println(keyPressed);
    switch (keyPressed) {
      case 5:
        if (setPoint >= 20) {
          setPoint -= 10;
          Serial.println(setPoint);
        }
        break;
      case 13:
        if (setPoint <= 100) {
          setPoint += 10;
          Serial.println(setPoint);
        }
        break;
      case 6:
        stopped = !stopped;
        if (stopped) chassis.stop();
        break;
      default:
        if (keyPressed >= 16 && keyPressed <= 26) {
          setPoint = keyMap[keyPressed] * 10;
        }
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