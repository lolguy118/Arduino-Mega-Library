#pragma once
#include <stdint.h>
// TODO: extract shared functionality between Register 16 and Register 8
class Register16
{
public:
    explicit Register16(volatile uint16_t *argRegister);
    void write(uint16_t argRegisterValue);
    uint16_t read() const;
    Register16(const Register16 &) = delete;
    Register16 &operator=(const Register16 &) = delete;

private:
    volatile uint16_t *const mRegister;
};