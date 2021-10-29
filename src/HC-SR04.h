#ifndef __HCSR04_H
#define __HCSR04_H

#include <Arduino.h>
#include <SPI.h>
#include "DistanceSensor.h"

#define ECHO_RECD   0x02

#define USE_CTRL_PIN    0x01
#define USE_ECHO        0x026


class HCSR04 : public DistanceSensor
{
public:
    bool echoRecd = false;
private:
    uint32_t lastPing = 0;          // for keeping track of intervals
    uint32_t pingInterval = 200;    // default to 200 ms

    uint32_t pulseStart = 0;
    uint32_t pulseEnd = 0;
public:
    HCSR04(void);  //ideally, this would take pins as parameters, but just hard-coded for now since we only have one
    void init(void);
    void init(uint8_t interfaces);

    //checks to see if it's time for a ping
    bool checkPingTimer(void);

    //Checks to see if a pulse echo has been registered
    uint16_t checkEcho(void);

    /**
     * TODO: Write a getDistance() function for the distance method of your choice.
     * 
     * See the .cpp file.
     */
    bool getDistance(float& distance);

    //ISR for the MaxBotix sensor
    void HCSR_ISR(void);
};

extern HCSR04 hcsr_1; 

#endif