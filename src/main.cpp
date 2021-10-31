#include <Arduino.h>
#include "HC-SR04.h"
#include "SharpIR.h"
#include "RBE-200n-Lib.h"
#include "StandoffController.h"
#include "Chassis.h"
#include "Filters.h"

float dist = 0;
StandoffController standoff = StandoffController(2);
AvgFilter<float, 5> ultraFilter;


void setup()
{
  chassis.init();
  hcsr_1.init();
  //ir_1.init();
  pinMode(0, INPUT_PULLUP);
  delay(1000);
  standoff.setTarget(20);

  Serial.begin(115200);
  Serial.println("Velkommen til");
}

void loop() {
  hcsr_1.checkPingTimer();
  if (hcsr_1.getDistance(dist)) {
    ultraFilter.addDatum(dist);
    //standoff.process(ultraFilter.getMedian());
    //chassis.setMotorEfforts(-standoff.l(), -standoff.r());
    Serial.println(ultraFilter.getMedian());
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