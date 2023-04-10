#ifndef _SERIAL_PIXEL_PIXELS_H_
#define _SERIAL_PIXEL_PIXELS_H_

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include "display.h"

class Pixels : public Display
{
public:
    Pixels(int pin) : _pin(pin), _n(0) {}

    void setup(int n);
    void setup(int n, uint8_t config);
    void setRGB(int i, uint8_t r, uint8_t g, uint8_t b);
    void setHSV(int i, uint8_t h, uint8_t s, uint8_t v);
    void show();
    void clear();

private:
    int _pin;
    int _n;
    Adafruit_NeoPixel _pixels;

    void _setColor(int i, uint32_t c);
};

#endif
