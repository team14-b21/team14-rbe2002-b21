#include <Arduino.h>
#include "HC-SR04.h"
#include "RBE-200n-Lib.h"

HCSR04 hcsr;


void setup()
{
  hcsr.init();
  delay(1000);
  
  Serial.begin(115200);
  Serial.println("Velkommen til");
}

void loop() 
{
  hcsr.checkPingTimer();
  //if (hcsr.checkPingTimer() & ECHO_RECD) {
    hcsr.checkEcho();
  //}
}