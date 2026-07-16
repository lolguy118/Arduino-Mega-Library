#pragma once
#include <stdint.h>
#include "Register8.h"

class RegisterBit
{
public:
    explicit RegisterBit(Register8 *argRegister, uint8_t argBitPosition);
    void setBit();
    void clearBit();
    void toggleBit();
    bool readBit() const;

private:
    Register8 *const mRegister;
    uint8_t mBitPosition;
};