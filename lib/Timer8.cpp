#include "Timer8.h"
#include <assert.h>

Timer8::Timer8(UniversalTimerRegisters argUniversalTimerRegisters, Timer8SpecificRegisters argTimer8Registers) : mUniversalRegisters(argUniversalTimerRegisters), mTimer8SpecificRegisters(argTimer8Registers) {}

bool Timer8::isRunning()
{
    uint8_t temp = mUniversalRegisters.tccrb.read();
    return (temp & 0b00000111) != 0;
}

void Timer8::setPrescaler(Prescaler argPrescalar)
{
    mPrescaler = argPrescalar;
    if (isRunning())
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
        assert(mPrescaler == Prescaler::DIV_1 || mPrescaler == Prescaler::DIV_8 || mPrescaler == Prescaler::DIV_64 || mPrescaler == Prescaler::DIV_256 || mPrescaler == Prescaler::DIV_1024);
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
        break;
    default:
        assert(mMode == Mode::NORMAL || mMode == Mode::CTC || mMode == Mode::FAST_PWM || mMode == Mode::PHASE_CORRECT_PWM);
        break;
    }
}

void Timer8::writeCompareValueA(uint8_t argCompareValue)
{
    mTimer8SpecificRegisters.ocra.write(argCompareValue);
}

void Timer8::writeCompareValueB(uint8_t argCompareValue)
{
    mTimer8SpecificRegisters.ocrb.write(argCompareValue);
}

void Timer8::start()
{
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

void Timer8::setChannelAMode(OutputCompareMode argChannelAMode)
{
    uint8_t temp = mUniversalRegisters.tccra.read();
    temp &= ~(0b11 << 6);
    switch (argChannelAMode)
    {
    case OutputCompareMode::DISCONNECTED:
        break;
    case OutputCompareMode::TOGGLE:
        temp |= (1 << 6);
        break;
    case OutputCompareMode::NON_INVERTING_PWM:
        temp |= (1 << 7);
        break;
    case OutputCompareMode::INVERTING_PWM:
        temp |= (0b11 << 6);
        break;
    default:
        assert(argChannelAMode == OutputCompareMode::DISCONNECTED || argChannelAMode == OutputCompareMode::TOGGLE || argChannelAMode == OutputCompareMode::NON_INVERTING_PWM || argChannelAMode == OutputCompareMode::INVERTING_PWM);
        break;
    }
    mUniversalRegisters.tccra.write(temp);
    mChannelAMode = argChannelAMode;
}

void Timer8::setChannelBMode(OutputCompareMode argChannelBMode)
{
    uint8_t temp = mUniversalRegisters.tccra.read();
    temp &= ~(0b11 << 4);
    switch (argChannelBMode)
    {
    case OutputCompareMode::DISCONNECTED:
        break;
    case OutputCompareMode::TOGGLE:
        temp |= (1 << 4);
        break;
    case OutputCompareMode::NON_INVERTING_PWM:
        temp |= (1 << 5);
        break;
    case OutputCompareMode::INVERTING_PWM:
        temp |= (0b11 << 4);
        break;
    default:
        assert(argChannelBMode == OutputCompareMode::DISCONNECTED || argChannelBMode == OutputCompareMode::TOGGLE || argChannelBMode == OutputCompareMode::NON_INVERTING_PWM || argChannelBMode == OutputCompareMode::INVERTING_PWM);
        break;
    }
    mUniversalRegisters.tccra.write(temp);
    mChannelBMode = argChannelBMode;
}

/*
Compare Output Mode (COM) Bits - TCCRnA

Channel A:
COMnA1 COMnA0

00 = Normal port operation (OCnA disconnected)
01 = Toggle OCnA on compare match*
10 = Non-inverting PWM
11 = Inverting PWM

Channel B:
COMnB1 COMnB0

00 = Normal port operation (OCnB disconnected)
01 = Toggle OCnB on compare match*
10 = Non-inverting PWM
11 = Inverting PWM

* Toggle mode is only available in certain timer modes (refer to the
  datasheet for mode-specific behavior). It is not a general PWM mode.
*/