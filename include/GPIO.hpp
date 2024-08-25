#pragma once
#include <cstdint>

class GPIO
{
private:
    virtual constexpr int32_t BASE_ADDRESS() const = 0;
    virtual constexpr int32_t GPIO_BASE_ADDRESS() const = 0;

    virtual constexpr int32_t PAGE_SIZE() const = 0;
    virtual constexpr int32_t BLOCK_SIZE() const = 0;
protected:
    int MemoryFD=0;
    char* GPIOMap=nullptr; //raw since we're not allocating memory here
    volatile char* GPIO_PINS=nullptr; //raw since we're not allocating memory here

public:
    GPIO();
    ~GPIO();
};
