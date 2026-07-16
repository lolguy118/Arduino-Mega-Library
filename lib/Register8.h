#pragma once
#include <stdint.h>

class Register8
{
public:
    explicit Register8(volatile uint8_t *argRegister);
    void write(uint8_t argRegisterValue);
    uint8_t read() const;
    Register8(const Register8 &) = delete;
    Register8 &operator=(const Register8 &) = delete;

private:
    volatile uint8_t *const mRegister;
};