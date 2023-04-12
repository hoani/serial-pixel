#include "comms.h"
#include "arduino.h"

void Comms::update()
{
    while (true)
    {
        int b = Serial.read();
        if (b == -1)
        {
            return;
        }
        if (b == '\n')
        {
            _processPacket();
        }
        else
        {
            _appendByte((uint8_t)b);
        }
    }
}

void Comms::_processPacket()
{
    const uint8_t ctl = _nextByte();
    switch (ctl)
    {
    case 'I':
        Comms::_doInit();
        break;
    case 'R':
        Comms::_doRGB();
        break;
    case 'H':
        Comms::_doHSV();
        break;
    case 'S':
        Comms::_doShow();
        break;
    case 'C':
        Comms::_doClear();
        break;
    }
    _index = _last; // Make sure we have cleared out the current packet.
}

void Comms::_doInit()
{
    // Check for correct number of bytes.
    if (_delta() < 2)
    {
        return;
    }
    int n = _nextU8();

    // Short init command, no config.
    if (_delta() < 2)
    {
        _d->setup(n);
        return;
    }

    // Init with config (ie, used for setting different pixel types, like RGB, GRBW etc).
    int c = _nextU8();
    _d->setup(n, c);
}

void Comms::_doRGB()
{
    const int delta = _delta();
    // Check for correct number of bytes.
    if (delta < 8 || (delta % 6 != 2))
    {
        return;
    }
    int n = _nextU8();
    while (_index != _last)
    {
        uint8_t r = _nextU8();
        uint8_t g = _nextU8();
        uint8_t b = _nextU8();
        _d->setRGB(n, r, g, b);
        n++;
    }
}

void Comms::_doHSV()
{
    const int delta = _delta();
    // Check for correct number of bytes.
    if (delta < 8 || (delta % 6 != 2))
    {
        return;
    }
    int n = _nextU8();
    while (_index != _last)
    {
        uint8_t h = _nextU8();
        uint8_t s = _nextU8();
        uint8_t v = _nextU8();
        _d->setHSV(n, h, s, v);
        n++;
    }
}

void Comms::_doShow()
{
    _d->show();
}

void Comms::_doClear()
{
    _d->clear();
}

void Comms::_appendByte(uint8_t b)
{
    _b[_last] = b;
    _last++;
    if (_last == SERIAL_BUFFER_SIZE)
    {
        _last = 0;
    }
}

uint8_t Comms::_nextU8()
{
    const char str[2]{
        _nextByte(),
        _nextByte(),
    };

    char *end;
    return (uint8_t)strtol(str, &end, 16);
}

uint8_t Comms::_nextByte()
{
    if (_index == _last)
    {
        return 0; // Not good...
    }

    uint8_t b = _b[_index];
    _index++;
    if (_index == SERIAL_BUFFER_SIZE)
    {
        _index = 0;
    }
    return b;
}

int Comms::_delta()
{
    int last = _last;
    if (last < _index)
    {
        last += SERIAL_BUFFER_SIZE;
    }
    return last - _index;
}
