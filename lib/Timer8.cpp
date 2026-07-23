#include "Timer8.h"
#include <stdint.h>

Timer8::Timer8(UniversalTimerRegisters argUniversalTimerRegisters, Timer8SpecificRegisters argTimer8Registers) : mUniversalRegisters(argUniversalTimerRegisters), mTimer8SpecificRegisters(argTimer8Registers) {}

void Timer8::setPrescaler(Prescaler argPrescalar) {
    mPrescaler = argPrescalar;
    writePrescaler();
}

void Timer8::writePrescaler() {
    uint8_t temp = mUniversalRegisters.tccrb.read();
    temp &= ~(0b00000111);
    switch (mPrescaler)
    {
    case Prescaler::DIV_1:
        temp |= 0b00000001;
        break;
    case Prescaler::DIV_8:
        temp |= 0b00000010;
        break;
    case Prescaler::DIV_64:
        temp |= 0b00000100;
        break;
    case Prescaler::DIV_256:
        temp |= 0b00000110;
        break;
    case Prescaler::DIV_1024:
        temp |= 0b00000111;
        break;
    default:
        // Handle unknown prescaler value
        break;
    }
    mUniversalRegisters.tccrb.write(temp);
}

void Timer8::setMode(Mode argMode) {
    mMode = argMode;
    switch (mMode)
    {
    case Mode::NORMAL:
        disableCTC();
        disablePWM();
        break;
    case Mode::CTC:
        enableCTC();
        disablePWM();
        break;
    case Mode::FAST_PWM:
        enablePWM();
        break;
    case Mode::PHASE_CORRECT_PWM:
        enablePWM();
        break;
    default:
        // Handle unknown mode
        break;
    }
}

void Timer8::setCompareValueA(int argCompareValue) {
    mCompareValueA = argCompareValue;
    writeCompareValueA();
}

void Timer8::setCompareValueB(int argCompareValue) {
    mCompareValueB = argCompareValue;
    writeCompareValueB();
}

