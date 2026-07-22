#include <stdint.h>
#include "TimerBase.h"

TimerBase::TimerBase(UniversalTimerRegisters argUniversalTimerRegisters) : mUniversalRegisters(argUniversalTimerRegisters) {}

void TimerBase::setPrescaler(Prescaler argPrescalar)
{
    mPrescaler = argPrescalar;
    updatePrescaler();
}

void TimerBase::setMode(Mode argMode)
{
    if (mMode == argMode)
    {
        return;
    }
    switch (argMode)
    {
    case Mode::NORMAL:
        disableCTC();
        disablePWM();
        break;
    case Mode::CTC:
        disablePWM();
        enableCTC();
        break;
    case Mode::FAST_PWM:
        disableCTC();
        enablePWM();
        break;
    default:
        break;
    }
    mMode = argMode;
}

void TimerBase::start()
{
    updatePrescaler();
    mIsOn = true;
}

void TimerBase::stop()
{
    uint8_t temp = mUniversalRegisters.tccrb.read();
    temp &= ~0b111;
    mUniversalRegisters.tccrb.write(temp);
    mIsOn = false;
}

void TimerBase::updatePrescaler()
{
    uint8_t temp = mUniversalRegisters.tccrb.read();
    temp &= ~0b111;
    switch (mPrescaler)
    {
    case Prescaler::DIV_1:
        temp |= 0b001;
        break;
    case Prescaler::DIV_8:
        temp |= 0b010;
        break;
    case Prescaler::DIV_64:
        temp |= 0b011;
        break;
    case Prescaler::DIV_256:
        temp |= 0b100;
        break;
    case Prescaler::DIV_1024:
        temp |= 0b101;
        break;
    default:
        break;
    }
    mUniversalRegisters.tccrb.write(temp);
}