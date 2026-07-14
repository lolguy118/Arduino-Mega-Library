#include "RegisterBit.h"
#include <stdint.h>

RegisterBit::RegisterBit(Register8* argRegister, uint8_t argBitPosition) : mRegister(argRegister), mBitPosition(argBitPosition) {}