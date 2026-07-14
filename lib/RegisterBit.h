#pragma once
#include <stdint.h>
#include "Register8.h"

class RegisterBit {
    public:
        explicit RegisterBit(Register8* argRegister, uint8_t argBitPosition);
        void setBit();
        void clearBit();
        bool readBit() const;
    private:
        Register8* mRegister;
        uint8_t mBitPosition;
};