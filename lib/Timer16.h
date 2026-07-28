#pragma once

#include "Register16.h"
#include <stdint.h>


struct UniversalTimerRegisters
{
    Register16 &tccra;
    Register16 &tccrb;
    Register16 &timsk;
    Register16 &tifr;
};


struct Timer16SpecificRegisters
{
    volatile uint8_t *tccrc;

    volatile uint16_t *tcnt;

    volatile uint16_t *ocra;
    volatile uint16_t *ocrb;
    volatile uint16_t *ocrc;

    volatile uint16_t *icr;
};


class Timer16
{
public:

    enum class Prescaler
    {
        DIV_1,
        DIV_16,
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


    explicit Timer16(UniversalTimerRegisters argUniversalTimerRegisters,
           Timer16SpecificRegisters argTimer16SpecificRegisters);


    // Timer state control
    bool isRunning();
    void start();
    void stop();


    // Timer configuration
    void setPrescaler(Prescaler argPrescaler);
    void setMode(Mode argMode);


    // Output compare registers
    void writeCompareValueA(uint16_t argCompareValue);
    void writeCompareValueB(uint16_t argCompareValue);


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
    Timer16SpecificRegisters mTimer16SpecificRegisters;


    // Cached configuration state
    Prescaler mPrescaler = Prescaler::DIV_1;
    Mode mMode = Mode::NORMAL;
    OutputCompareMode mChannelAMode = OutputCompareMode::DISCONNECTED;
    OutputCompareMode mChannelBMode = OutputCompareMode::DISCONNECTED;
};