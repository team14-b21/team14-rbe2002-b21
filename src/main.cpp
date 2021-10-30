#include <Arduino.h>
#include "Filters.h"
#include "SharpIR.h"
#include "RBE-200n-Lib.h"


int counter = 0;
float dist = 0;
AvgFilter<float, 5> filter;
float YInt = 4.46147;
float slope = 9112.68;

void setup()
{
  ir_1.init();
  pinMode(0, INPUT_PULLUP);
  delay(1000);

  Serial.begin(115200);
  Serial.println("Velkommen til");
}


void loop()
{
  float irResult = slope/(ir_1.readMCP3002()-YInt);
  //uint16_t irResult = ir_1.readMCP3002();
  if (irResult > 0.1) {
    filter.addDatum(irResult);
    Serial.print(irResult);
    Serial.print("\t|\t");
    Serial.print(filter.getAvg());
    Serial.print("\t|\t");
    Serial.println(filter.getMedian());
  }
  /*
  while (counter < 200){
    hcsr_1.checkPingTimer();
    uint16_t echoLen = hcsr_1.checkEcho();
    if (echoLen > 4000) {
      Serial.println(echoLen);
      counter++;
    }
  }
  */
}

