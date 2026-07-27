#include "Timer8.h"
#include <stdint.h>
#include <assert.h>

Timer8::Timer8(UniversalTimerRegisters argUniversalTimerRegisters, Timer8SpecificRegisters argTimer8Registers) : mUniversalRegisters(argUniversalTimerRegisters), mTimer8SpecificRegisters(argTimer8Registers) {}

void Timer8::setPrescaler(Prescaler argPrescalar)
{
    mPrescaler = argPrescalar;
    if (mIsOn)
    {
        writePrescaler();
    }
}

void Timer8::writePrescaler()
{
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
        assert(mPrescaler == Prescaler::DIV_1 && mPrescaler == Prescaler::DIV_8 && mPrescaler == Prescaler::DIV_64 && mPrescaler == Prescaler::DIV_256 && mPrescaler == Prescaler::DIV_1024);
        break;
    }
    mUniversalRegisters.tccrb.write(temp);
}

void Timer8::setMode(Mode argMode)
{
    mMode = argMode;
    switch (mMode)
    {
    case Mode::NORMAL:
        // disableCTC();
        // disablePWM();
        break;
    case Mode::CTC:
        enableCTC();
        break;
    case Mode::FAST_PWM:
        enableFastPWM();
        break;
    case Mode::FAST_PWM_COMPARE_A_TOP:
        enableFastPWMCompareATop();
        break;
    case Mode::PHASE_CORRECT_PWM:
        enablePhaseCorrectPWM();
        break;
    case Mode::PHASE_CORRECT_PWM_COMPARE_A_TOP:
        enablePhaseCorrectPWMCompareATop();
    default:
        assert(mMode == Mode::NORMAL && mMode == Mode::CTC && mMode == Mode::FAST_PWM && mMode == Mode::PHASE_CORRECT_PWM);
        break;
    }
}

void Timer8::setCompareValueA(int argCompareValue)
{
    mCompareValueA = argCompareValue;
    writeCompareValueA();
}

void Timer8::setCompareValueB(int argCompareValue)
{
    mCompareValueB = argCompareValue;
    writeCompareValueB();
}

void Timer8::writeCompareValueA()
{
    mTimer8SpecificRegisters.ocra->write(mCompareValueA);
}

void Timer8::writeCompareValueB()
{
    mTimer8SpecificRegisters.ocrb->write(mCompareValueB);
}

void Timer8::start()
{
    mIsOn = true;
    writePrescaler();
}

void Timer8::stop()
{
    uint8_t temp = mUniversalRegisters.tccrb.read();
    temp &= ~(0b00000111);
    mUniversalRegisters.tccrb.write(temp);
}

void Timer8::enableCTC()
{
    uint8_t temp = mUniversalRegisters.tccra.read();
    temp &= ~(0b00000011);
    temp |= (1 << 1);
    mUniversalRegisters.tccra.write(temp);
    temp = mUniversalRegisters.tccrb.read();
    temp &= ~(1 << 3);
    mUniversalRegisters.tccrb.write(temp);
}

void Timer8::enableFastPWM()
{
    uint8_t temp = mUniversalRegisters.tccra.read();
    temp |= (0b00000011);
    mUniversalRegisters.tccra.write(temp);
    temp = mUniversalRegisters.tccrb.read();
    temp &= ~(1 << 3);
    mUniversalRegisters.tccrb.write(temp);
}

void Timer8::enableFastPWMCompareATop()
{
    uint8_t temp = mUniversalRegisters.tccra.read();
    temp |= (0b00000011);
    mUniversalRegisters.tccra.write(temp);
    temp = mUniversalRegisters.tccrb.read();
    temp |= (1 << 3);
    mUniversalRegisters.tccrb.write(temp);
}

void Timer8::enablePhaseCorrectPWM()
{
    uint8_t temp = mUniversalRegisters.tccra.read();
    temp &= ~(0b00000011);
    temp |= (1 << 0);
    mUniversalRegisters.tccra.write(temp);
    temp = mUniversalRegisters.tccrb.read();
    temp &= ~(1 << 3);
    mUniversalRegisters.tccrb.write(temp);
}

void Timer8::enablePhaseCorrectPWMCompareATop()
{
    uint8_t temp = mUniversalRegisters.tccra.read();
    temp &= ~(0b00000011);
    temp |= (1 << 0);
    mUniversalRegisters.tccra.write(temp);
    temp = mUniversalRegisters.tccrb.read();
    temp |= (1 << 3);
    mUniversalRegisters.tccrb.write(temp);
}