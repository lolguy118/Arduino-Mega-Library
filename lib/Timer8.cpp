#include "Timer8.h"
#include <stdint.h>

Timer8::Timer8(UniversalTimerRegisters argUniversalTimerRegisters, Timer8Registers argTimer8Registers) : TimerBase(argUniversalTimerRegisters), mTimer8Registers(argTimer8Registers) {}

void TimerBase::enableCTC() {
    
}
