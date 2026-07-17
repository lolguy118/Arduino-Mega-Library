#pragma once
#include "TimerBase.h"
#include <stdint.h>

struct Timer8Registers
{
    Register8 *tcnt;
    Register8 *ocra;
    Register8 *ocrb;
};

class Timer8 : public TimerBase
{
public:
    Timer8(UniversalTimerRegisters argUniversalTimerRegisters, Timer8Registers argTimer8Registers);

private:
    Timer8Registers mTimer8Registers;
};