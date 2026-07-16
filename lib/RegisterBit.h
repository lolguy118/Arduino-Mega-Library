#pragma once
#include <stdint.h>
#include "Register8.h"

class RegisterBit
{
public:
    explicit RegisterBit(RegisterBit *argRegister, uint8_t argBitPosition);
    void setBit();
    void clearBit();
    void toggleBit();
    bool readBit() const;
    RegisterBit(const RegisterBit &) = delete;
    RegisterBit &operator=(const RegisterBit &) = delete;

private:
    RegisterBit *const mRegister;
    uint8_t mBitPosition;
};