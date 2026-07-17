#include <stdint.h>
#include "Timer.h"

Timer::Timer(UniversalTimerRegisters argUniversalTimerRegisters) : mUniversalRegisters(argUniversalTimerRegisters) {}

void Timer::start() {
    uint8_t temp;
    switch (mPrescaler)
    {
    case Prescaler::DIV_1:
        temp = Timer::mUniversalRegisters.tccrb->read();
        
        break;
    
    default:
        break;
    }
}