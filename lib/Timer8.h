#pragma once
#include "Register8.h"
#include <stdint.h>

struct UniversalTimerRegisters
{
    Register8 &tccra;
    Register8 &tccrb;
    Register8 &timsk;
    Register8 &tifr;
};

struct Timer8SpecificRegisters
{
    Register8 *tcnt;
    Register8 *ocra;
    Register8 *ocrb;
};

class Timer8
{
public:
    enum class Prescaler
    {
        DIV_1,
        DIV_8,
        DIV_64,
        DIV_256,
        DIV_1024
    };
    enum class Mode
    {
        NORMAL,
        CTC,
        FAST_PWM,
        FAST_PWM_COMPARE_A_TOP,
        PHASE_CORRECT_PWM,
        PHASE_CORRECT_PWM_COMPARE_A_TOP
    };
    Timer8(UniversalTimerRegisters argUniversalTimerRegisters, Timer8SpecificRegisters argTimer8SpecificRegisters);
    void setPrescaler(Prescaler argPrescalar);
    void setMode(Mode argMode);
    void setCompareValueA(int argCompareValue);
    int getCompareValueA();
    void setCompareValueB(int argCompareValue);
    void getCompareValueB();
    void setCompareATop(bool argCompareAIsTop);
    void start();
    void stop();
    void enableChannelA();
    void disableChannelA();
    void setChannelADutyCycle();
    void enableChannelB();
    void disableChannelB();
    void setChannelBDutyCycle();

private:
    void writePrescaler();
    void writeCompareValueA();
    void writeCompareValueB();
    void enableCTC();
    void enableFastPWM();
    void enableFastPWMCompareATop();
    void enablePhaseCorrectPWM();
    void enablePhaseCorrectPWMCompareATop();
    UniversalTimerRegisters mUniversalRegisters;
    Timer8SpecificRegisters mTimer8SpecificRegisters;
    Prescaler mPrescaler = Prescaler::DIV_1;
    Mode mMode = Mode::NORMAL;
    bool mIsOn = false;
    int mCompareValueA = 255;
    int mCompareValueB = 255;
    bool mChannelAIsOn = false;
    bool mChannelBIsOn = false;
    uint8_t mChannelADutyCycle;
    uint8_t mChannelBDutyCycle;
};