#ifndef _SERIAL_PIXEL_DISPLAY_H_
#define _SERIAL_PIXEL_DISPLAY_H_

#include <stdint.h>

// Virtual display interface.
class Display
{
public:
    virtual void setup(int n) = 0;
    virtual void setup(int n, uint8_t config) = 0;
    virtual void setRGB(int i, uint8_t r, uint8_t g, uint8_t b) = 0;
    virtual void setHSV(int i, uint8_t h, uint8_t s, uint8_t v) = 0;
    virtual void show() = 0;
    virtual void clear() = 0;
};

#endif
