#pragma once
#include <stdint.h>
#include "Register8.h"

struct UniversalTimerRegisters
{
    Register8 &tccra;
    Register8 &tccrb;
    Register8 &timsk;
    Register8 &tifr;
};

class TimerBase
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
        NORMAL,
        CTC,
        FAST_PWM
    };
    TimerBase(UniversalTimerRegisters argUniversalTimerRegisters);
    void setPrescaler(Prescaler argPrescalar);
    void setMode(Mode argMode);
    void start();
    void stop();

private:
    void updatePrescaler();
    void enableCTC();
    void disableCTC();
    void enablePWM();
    void disablePWM();
    UniversalTimerRegisters mUniversalRegisters;
    Prescaler mPrescaler = Prescaler::DIV_1;
    Mode mMode = Mode::NORMAL;
    bool mIsOn = false;
};