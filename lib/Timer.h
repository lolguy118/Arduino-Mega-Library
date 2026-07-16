#pragma once
#include <stdint.h>
#include "Register8.h"

struct UniversalTimerRegisters
{
    volatile Register8 *tccra;
    volatile Register8 *tccrb;
    volatile Register8 *timsk;
    volatile Register8 *tifr;
};

class Timer
{
public:
    enum class Prescaler
    {
        DIV_1,
        DIV_8,
        DIV_32, // If passed into a timer that isn't timer 2, will be implemented to throw exception
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
    void setPrescalar(Prescaler argPrescalar);
    void setMode(Mode argMode);
    void start();
    void stop();

private:
    void enableCTC();
    void disableCTC();
    void enablePWM();
    void disablePWM();
    UniversalTimerRegisters mUniversalRegisters;
    Prescaler mPrescaler = Prescaler::DIV_1;
    Mode mMode = Mode::OFF;
};