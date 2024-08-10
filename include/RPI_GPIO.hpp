#pragma once
#include "GPIO.hpp"

class RPI_GPIO : public GPIO
{
private:
    virtual constexpr int32_t BASE_ADDRESS() const override{return 0x20000000;};
    virtual constexpr int32_t GPIO_BASE_ADDRESS() const override{return 0x20000000+BASE_ADDRESS();};

    virtual constexpr int32_t PAGE_SIZE() const override{return 4*1024;};
    virtual constexpr int32_t BLOCK_SIZE() const override{return 4*1024;};

    void INP_GPIO(const int& pin) const{
        *(GPIO_PINS+(pin/10)) &= ~(7<<((pin%10)*3));
    }

    void OUT_GPIO(const int& pin) const{ 
        *(GPIO_PINS+((pin)/10)) |=  (1<<(((pin)%10)*3)); 
    }

    void SET_GPIO_ALT(const int& pin, const int& alt) const{ 
        *(GPIO_PINS+(((pin)/10))) |= (((alt)<=3?(alt)+4:(alt)==4?3:2)<<(((pin)%10)*3));
    }
public:
    RPI_GPIO();
    ~RPI_GPIO();
};