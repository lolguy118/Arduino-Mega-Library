#pragma once
#include <stdint.h>

struct UniversalTimerRegisters
{
    volatile uint8_t *tccra;
    volatile uint8_t *tccrb;
    volatile uint8_t *timsk;
    volatile uint8_t *tifr;
};

class Timer
{
public:
    enum class Prescaler
    {
        DIV_1,
        DIV_8,
        DIV_32, //If passed into a timer that isn't timer 2, will be implemented to throw exception
        DIV_64,
        DIV_128,
        DIV_256,
        DIV_1024
    };
    enum class Mode
    {
        OFF,
        NORMAL,
        CTC,
        FAST_PWM
    };
    Timer(UniversalTimerRegisters argUniversalTimerRegisters);

private:
    UniversalTimerRegisters mUniversalRegisters;
    Prescaler mPrescaler = Prescaler::DIV_1;
    Mode mMode = Mode::OFF;
};