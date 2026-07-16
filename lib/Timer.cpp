#include <stdint.h>
#include "Timer.h"

Timer::Timer(UniversalTimerRegisters argUniversalTimerRegisters) : mUniversalRegisters(argUniversalTimerRegisters) {}

void Timer::start() {
    switch (mPrescaler)
    {
    case Prescaler::DIV_1:
        /* code */
        break;
    
    default:
        break;
    }
}