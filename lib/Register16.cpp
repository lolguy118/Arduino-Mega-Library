#include "Register16.h"

Register16::Register16(volatile uint16_t *argRegister) : mRegister(argRegister) {}

void Register16::write(uint16_t argRegisterValue)
{
    *mRegister = argRegisterValue;
}

uint16_t Register16::read() const
{
    return *mRegister;
}