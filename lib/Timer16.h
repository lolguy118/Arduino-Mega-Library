#pragma once

#include "Register8.h"
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
    volatile Register8 *tccrc;

    volatile Register16 *tcnt;

    volatile Register16 *ocra;
    volatile Register16 *ocrb;
    volatile Register16 *ocrc;

    volatile Register16 *icr;
};

struct PWMConfiguration
{
    PWMType type;
    PWMTop topSource;
};

enum class PWMType
{
    FAST,
    PHASE_CORRECT,
    PHASE_AND_FREQUENCY_CORRECT
};

enum class PWMTop
{
    FIXED_EIGHT_BIT_TOP,
    FIXED_NINE_BIT_TOP,
    FIXED_TEN_BIT_TOP,
    INPUT_CAPTURE_REGISTER,
    OUTPUT_COMPARE_REGISTER_A
};

class Timer16
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

    enum class CTCTop
    {
        INPUT_CAPTURE_REGISTER,
        OUTPUT_COMPARE_REGISTER_A
    };

    enum class Mode
    {
        NORMAL,
        CTC_COMPARE_A_TOP,
        CTC_ICR_TOP,
        FAST_PWM_8_BIT,
        FAST_PWM_9_BIT,
        FAST_PWM_10_BIT,
        FAST_PWM_COMPARE_A_TOP,
        FAST_PWM_ICR_TOP,
        PHASE_CORRECT_PWM_8_BIT,
        PHASE_CORRECT_PWM_9_BIT,
        PHASE_CORRECT_PWM_10_BIT,
        PHASE_CORRECT_PWM_COMPARE_A_TOP,
        PHASE_CORRECT_PWM_ICR_TOP,
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
    void writeCompareValueC(uint16_t argCompareValue);

    // Output compare channels
    void setChannelAMode(OutputCompareMode argChannelAMode);
    void setChannelBMode(OutputCompareMode argChannelBMode);
    void setChannelCMode(OutputCompareMode argChannelCMode);

    void writeInputCaptureValue(uint16_t argValue);

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
    OutputCompareMode mChannelCMode = OutputCompareMode::DISCONNECTED;
};