#include "Register8.h"

Register8::Register8(volatile uint8_t* argRegister) : mRegister(argRegister) {}


void Register8::write(uint8_t argRegisterValue) {
    *mRegister = argRegisterValue;
}

uint8_t Register8::read() const {
    return *mRegister;
}