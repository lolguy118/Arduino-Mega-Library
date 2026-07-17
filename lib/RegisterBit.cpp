#include "RegisterBit.h"
#include <stdint.h>

explicit RegisterBit::RegisterBit(Register8 *argRegister, uint8_t argBitPosition) : mRegister(argRegister), mBitPosition(argBitPosition) {}

void RegisterBit::setBit()
{
    uint8_t temp = mRegister->read();
    temp |= (1u << mBitPosition);
    mRegister->write(temp);
}

void RegisterBit::clearBit()
{
    uint8_t temp = mRegister->read();
    temp &= ~(1u << mBitPosition);
    mRegister->write(temp);
}

void RegisterBit::toggleBit()
{
    uint8_t temp = mRegister->read();
    temp ^= (1u << mBitPosition);
    mRegister->write(temp);
}

bool RegisterBit::readBit() const
{
    return mRegister->read() & (1u << mBitPosition);
}