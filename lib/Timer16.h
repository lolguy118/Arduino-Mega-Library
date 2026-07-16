#include <stdint.h>
#include "Timer.h"

struct Timer16Registers
{
    volatile uint8_t *tccrc;

    volatile uint16_t *tcnt;

    volatile uint16_t *ocra;
    volatile uint16_t *ocrb;
    volatile uint16_t *ocrc;

    volatile uint16_t *icr;
};

class Timer16 : public Timer
{
public:
    explicit Timer16(UniversalTimerRegisters argUniversalTimerRegisters, Timer16Registers argTimer16Registers);

private:
    Timer16Registers mTimer16Registers;
};