#include "pixels.h"

void Pixels::setup(int n)
{
    setup(n, NEO_GRB + NEO_KHZ800);
}

void Pixels::setup(int n, uint8_t config = NEO_GRB + NEO_KHZ800)
{
    if (_n != 0)
    {
        return;
    }
    _pixels = Adafruit_NeoPixel(n, _pin, config);
    _pixels.begin();
    _n = n;
}

void Pixels::setRGB(int i, uint8_t r, uint8_t g, uint8_t b)
{
    if (_n == 0)
    {
        return;
    }
    _setColor(i, _pixels.Color(r, g, b));
}

void Pixels::setHSV(int i, uint8_t h, uint8_t s, uint8_t v)
{
    if (_n == 0)
    {
        return;
    }
    _setColor(i, _pixels.ColorHSV((uint16_t)h << 8, s, v));
}

void Pixels::show()
{
    if (_n == 0)
    {
        return;
    }
    _pixels.show();
}

void Pixels::clear()
{
    if (_n == 0)
    {
        return;
    }
    _pixels.clear();
}

// Private

void Pixels::_setColor(int i, uint32_t c)
{
    if (i > _n)
    {
        return;
    }
    _pixels.setPixelColor(i, _pixels.gamma32(c));
}
