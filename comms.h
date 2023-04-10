#ifndef _SERIAL_PIXEL_SERIAL_H_
#define _SERIAL_PIXEL_SERIAL_H_

#include "display.h"

#define SERIAL_BUFFER_SIZE (256 * 8)

class Comms
{
public:
    Comms(Display *d) : _d(d), _index(0), _last(0) {}

    void update();

private:
    Display *_d;
    uint8_t _b[SERIAL_BUFFER_SIZE];
    int _index;
    int _last;

    void _processPacket();
    void _doInit();
    void _doRGB();
    void _doHSV();
    void _doShow();
    void _doClear();
    void _appendByte(uint8_t b);
    uint8_t _nextU8();
    uint8_t _nextByte();
    int _delta();
};

#endif
