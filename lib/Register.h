#pragma once
#include <stdint.h>

class Register8 {
    public:
        bool getBit(uint8_t argBitPosition) {
            
        }
    private:
        volatile uint8_t mRegister;
        int mBits[8];
        
};