#ifndef __SHARPIR_H
#define __SHARPIR_H

/*
 * Datasheet: https://www.maxbotix.com/documents/LV-MaxSonar-EZ_Datasheet.pdf
 */

#include <Arduino.h>
#include <SPI.h>
#include "DistanceSensor.h"

#define ADC_READ    0x08

class SharpIR : public DistanceSensor
{
private:
    uint8_t state = 0;

    uint32_t lastADCread = 0;       // can't read the ADC too fast
public:
    SharpIR(void);  //ideally, this would take pins as parameters, but just hard-coded for now since we only have one
    void init(void);

    //Reads the MCP3002 ADC; returns ADC result
    uint16_t readMCP3002(bool force = false);

    /**
     * TODO: Write a getDistance() function for the distance method of your choice.
     * 
     * See the .cpp file.
     */
    bool getDistance(float& distance);
};

extern SharpIR ir_1; 

#endif