#include <Arduino.h>
#include "HC-SR04.h"
#include "RBE-200n-Lib.h"

int counter = 0;

void setup()
{
  hcsr_1.init();
  delay(1000);

  Serial.begin(115200);
  Serial.println("Velkommen til");
}

void loop()
{
  while (counter < 200){
    hcsr_1.checkPingTimer();
    uint16_t echoLen = hcsr_1.checkEcho();
    if (echoLen > 4000) {
      Serial.println(echoLen);
      counter++;
    }
  }
  
}