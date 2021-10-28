#include "HC-SR04.h"

#define TRIG_PIN 16      //for pinging -- not a great choice since this can hamper uploading
#define PULSE_PIN 17    //for reading pulse

#define MB_WINDOW_DUR 50    //ms

// Here is the mb_ez1 object that we declared as in extern in the .h file
HCSR04 hcsr_1;

//ISR for reading the echoes. Or is it echos?
void ISR_HCSR(void)
{
    hcsr_1.HCSR_ISR();
}

// Constructor. Nothing to see here. Move along.
HCSR04::HCSR04(void) {}

// Default init engages all interfaces
void HCSR04::init(void)
{
    init(USE_ECHO | USE_CTRL_PIN);
}

// Allows the user to select the interface
void HCSR04::init(uint8_t interfaces)
{
    if(interfaces & USE_ECHO)
    {
        // assert ECHO pin is an input
        pinMode(PULSE_PIN, INPUT);
        attachInterrupt(PULSE_PIN, ISR_HCSR, CHANGE);
    }

    if(interfaces & USE_CTRL_PIN)
    {
        //control pin for commanding pings
        pinMode(TRIG_PIN, OUTPUT);
    }
}

/**
 * checkPingTimer check to see if it's time to send a new ping.
 * You must select USE_CTRL_PIN in init() for this to work.
 */
uint8_t HCSR04::checkPingTimer(void)
{
    //check if we're ready to ping
    if(millis() - lastPing >= pingInterval)
    {
        Serial.print("pt");
        Serial.println(state);
        pulseEnd = pulseStart = 0;

        //clear out any leftover states
        //state = 0;

        lastPing = millis();    //not perfectly on schedule, but safer and close enough

        digitalWrite(TRIG_PIN, HIGH); //commands a ping; leave high for the duration
        delayMicroseconds(30); //datasheet says hold HIGH for >20us; we'll use 30 to be 'safe'
        digitalWrite(TRIG_PIN, LOW); //unclear if pin has to stay HIGH
    }

    return state;
}

uint16_t HCSR04::checkEcho(void)
{
    Serial.print("ec");
    Serial.println(state);
    uint16_t echoLength = 0;
    if(state & ECHO_RECD)
    {
        Serial.println("hi");
        echoLength = pulseEnd - pulseStart;
        state &= ~ECHO_RECD;
    }

    return echoLength;
}

//ISR for echo pin
void HCSR04::HCSR_ISR(void)
{
    if(digitalRead(PULSE_PIN))  //transitioned to HIGH
    {
        pulseStart = micros();
    }
    else                        //transitioned to LOW
    {
        pulseEnd = micros();
        state |= ECHO_RECD;
    }
}

/**
 * TODO: Write a getDistance() function for the distance method of your choice.
 * 
 * getDistance should return true whenever there is a new reading, and put the result
 * in distance, which is _passed by reference_ so that you can "return" a value
 */
bool HCSR04::getDistance(float& distance)
{
    distance = -99;
    return false;
}