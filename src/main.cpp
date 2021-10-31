#include <Arduino.h>
#include "HC-SR04.h"
#include "SharpIR.h"
#include "RBE-200n-Lib.h"
#include "StandoffController.h"
#include "Chassis.h"
#include "Filters.h"
#include "IRDecoder.h"

const float KP = 2;
const float KI = 0.0;
const float KD = 0.0;

float dist = 0;
// StandoffController standoff = StandoffController(2);
AvgFilter<float, 5> ultraFilter;
float setPoint = 20;
float error;
float integral = 0;
float deltaError = 0;
float speed = 0;

IRDecoder decoder(15);

//IR Codes
const int Forward = -100286720;
const int Backward = -233980160;
const int Stop = -167133440;
int keyPressed = 0;
int lastKeyPressed = 0;

void setup()
{
  chassis.init();
  hcsr_1.init();
  decoder.init();
  delay(1000);

  Serial.begin(115200);
  Serial.println("Velkommen til");
}

void loop() {
  hcsr_1.checkPingTimer();
  if (hcsr_1.getDistance(dist)) {
    ultraFilter.addDatum(dist);
    //standoff.process(ultraFilter.getMedian());
    //chassis.setMotorEfforts(-standoff.l(), -standoff.r());
    //Serial.println(ultraFilter.getMedian());
  }
  keyPressed = decoder.getCode();
  if (keyPressed == Forward && lastKeyPressed != Forward && setPoint >= 20) {
    setPoint -= 10;
  }
  if (keyPressed == Backward && lastKeyPressed != Backward && setPoint <= 100) {
    setPoint += 10;
  }
  if (keyPressed == Stop) {
    chassis.stop();
  }
  //Serial.print("Setpoint: ");
  //Serial.println(setPoint);
  error = dist - setPoint;
  Serial.println(error);
  speed = error * KP + integral * KI +  deltaError * KD;
  chassis.setMotorEfforts(speed, speed);
  delay(50);

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