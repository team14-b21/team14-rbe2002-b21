#include <Arduino.h>
#include "HC-SR04.h"
#include "SharpIR.h"
#include "RBE-200n-Lib.h"
#include "StandoffController.h"
#include "Chassis.h"

float dist = 0;
StandoffController standoff;

void setup()
{
  chassis.init();
  hcsr_1.init();
  ir_1.init();
  pinMode(0, INPUT_PULLUP);
  delay(1000);

  Serial.begin(115200);
  Serial.println("Velkommen til");
}

void loop() {
  if (hcsr_1.getDistance(dist)) {
    standoff.process(dist);
    chassis.setMotorEfforts(standoff.l(), standoff.r());
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