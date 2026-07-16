#include <stdint.h>

struct UniversalTimerRegisters
{
    volatile uint8_t* tccra;
    volatile uint8_t* tccrb;
    volatile uint8_t* timsk;
    volatile uint8_t* tifr;
};

class Timer
{
public:
    enum class Prescaler // will be overloaded/reimplemented in dedicated Timer2 class to include DIV_32 and other uniqueness
    {
        DIV_1,
        DIV_8,
        DIV_64,
        DIV_256,
        DIV_1024
    };
    enum class Mode
    {
        OFF,
        NORMAL,
        CTC,
        FAST_PWM
    };
    explicit Timer(UniversalTimerRegisters argUniversalTimerRegisters);
    void start();
    void stop();
    void setMode(Mode argMode); // calls the appropriate enable and disable functions
    void setPrescalar(Prescaler argPrescaler);

private:
    UniversalTimerRegisters mUniversalTimerRegisters;
    Prescaler mPrescalar = Prescaler::DIV_1;
    void enableCTC();
    void disableCTC();
    void enablePWM();
    void disablePWM();
};