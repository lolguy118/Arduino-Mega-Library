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
    Register8 &tcnt;
    Register8 &ocra;
    Register8 &ocrb;
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


    enum class OutputCompareMode
    {
        DISCONNECTED,
        TOGGLE,
        NON_INVERTING_PWM,
        INVERTING_PWM
    };


    Timer8(UniversalTimerRegisters argUniversalTimerRegisters,
           Timer8SpecificRegisters argTimer8SpecificRegisters);


    // Timer state control
    bool isRunning();
    void start();
    void stop();


    // Timer configuration
    void setPrescaler(Prescaler argPrescaler);
    void setMode(Mode argMode);


    // Output compare registers
    void writeCompareValueA(uint8_t argCompareValue);
    void writeCompareValueB(uint8_t argCompareValue);


    // Output compare channels
    void setChannelAMode(OutputCompareMode argChannelAMode);
    void setChannelBMode(OutputCompareMode argChannelBMode);


private:

    // Hardware register writers
    void writePrescaler();


    // Waveform generation configuration
    void enableCTC();
    void enableFastPWM();
    void enableFastPWMCompareATop();
    void enablePhaseCorrectPWM();
    void enablePhaseCorrectPWMCompareATop();


private:

    UniversalTimerRegisters mUniversalRegisters;
    Timer8SpecificRegisters mTimer8SpecificRegisters;


    // Cached configuration state
    Prescaler mPrescaler = Prescaler::DIV_1;
    Mode mMode = Mode::NORMAL;
    OutputCompareMode mChannelAMode = OutputCompareMode::DISCONNECTED;
    OutputCompareMode mChannelBMode = OutputCompareMode::DISCONNECTED;
};