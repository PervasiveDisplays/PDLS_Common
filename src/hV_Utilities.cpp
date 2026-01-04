//
// hV_Utilities.cpp
// Library C++ code
// ----------------------------------
//
// Project Pervasive Displays Library Suite
// Based on highView technology
//
// Copyright (c) Pervasive Displays Inc., 2021-2026,
// Copyright (c) Etigues, 2010-2026
// Licence All rights reserved
// For exclusive use with Pervasive Displays screens
//
// See hV_Utilities.h for references
//
// Release 521: Added getDecimalPlaces
// Release 605: Added scaleValue()
// Release 607: Refactored peripherals
// Release 610: Refactored peripherals
// Release 611: Refactored functions
// Release 700: Refactored screen and board functions
// Release 803: Added types for string and frame-buffer
// Release 806: Added Wire debugging
// Release 900: Improved formatString()
// Release 900: Added new driver library
// Release 900: Consolidated constants
// Release 902: Improved power management
// Release 902: Simplified touch options
// Release 907: Increased buffer size
// Release 908: Added ISO translations for UTF ' and "
// Release 909: Added GridXY class
// Release 1000: Added support for UTF-8 strings
// Release 1000: Added support for UTF-16 strings
// Release 1000: Added support for 16-bit fonts
// Release 1000: Added UTF-16 characters traceability
// Release 1001: Improved 16-bit font generation
//

// Library header
#include "hV_Utilities.h"
#include "stdarg.h"
#include "stdio.h"

// Buffers for formatString
char bufferIn[BUFFER_LENGTH];
char bufferOut[BUFFER_LENGTH];

STRING_TYPE formatString(const char * format, ...)
{
    // --- Option 1
    char bufferWork[BUFFER_LENGTH] = {0};
    // memset(&bufferWork, 0x00, sizeof(bufferOut));

    va_list args;
    va_start(args, format);
    vsnprintf(bufferWork, (BUFFER_LENGTH - 1), format, args);
    va_end(args);

    memset(&bufferOut, 0x00, sizeof(bufferOut));
    memcpy(bufferOut, bufferWork, strlen(bufferWork));

    return String(bufferOut);
}

STRING_TYPE utf2iso(STRING_TYPE s)
{
#if (STRING_MODE == USE_STRING_OBJECT)

    return s;

#elif (STRING_MODE == USE_CHAR_ARRAY)

    memset(&bufferOut, 0x00, sizeof(bufferOut));
    strncpy(bufferOut, s, sizeof(bufferOut) - 1);
    return bufferOut;

#endif // STRING_MODE
}

//
// --- Viewer edition only
//

//
// --- End of Viewer edition
//

uint16_t utf8to16(STRING_CONST_TYPE inUTF8, STRING16_BYREF_TYPE outUTF16, uint8_t limit)
{
    uint16_t char16;
    uint16_t i16 = 0;

    memset(bufferIn, 0x00, sizeof(bufferIn));
    inUTF8.toCharArray(bufferIn, BUFFER_LENGTH);
    const char * _work8 = bufferIn;

    if (strlen(_work8) == 0)
    {
        outUTF16[0] = 0x0000;
        return 0;
    }

    bool flag = true;

    while ((*_work8 != 0) and flag)
    {
        // unsigned char char8 = static_cast<unsigned char>(*_work8);
        uint8_t char8 = (*_work8);
        if (char8 <= 0x7f)
        {
            char16 = char8;
        }
        else if (char8 <= 0xbf)
        {
            char16 = (char16 << 6) | (char8 & 0x3f);
        }
        else if (char8 <= 0xdf)
        {
            char16 = char8 & 0x1f;
        }
        else if (char8 <= 0xef)
        {
            char16 = char8 & 0x0f;
        }
        else
        {
            char16 = char8 & 0x07;
        }
        ++_work8;

        if (((*_work8 & 0xc0) != 0x80) and (char16 <= 0xffff))
        {
            // Checks specific to Basic edition
            if (char16 == 0x20ac)
            {
                char16 = 0x80; // Specific Font_Terminal code
            }
            else if (char16 > 0x00ff)
            {
                char16 = 0xb7; // Code for non-supported characters
            }
            outUTF16[i16++] = char16;
        }
    }
    outUTF16[i16] = 0x0000; // Null-terminate the output array
    return i16;
}

//
// --- Viewer edition only
//

//
// --- End of Viewer edition
//

//
// --- Advanced edition
//

//
// --- End of Advanced edition
//

GridXY::GridXY()
{
    _x0 = 0;
    _y0 = 0;
    _dx = 0;
    _dy = 0;
}

void GridXY::define(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t nX, uint16_t nY, bool flagAdjust)
{
    _x0 = x0;
    _y0 = y0;
    _dx = dx / nX;
    _dy = dy / nY;

    if (flagAdjust == true)
    {
        _x0 += (dx - nX * _dx) / 2;
        _y0 += (dy - nY * _dy) / 2;
    }
}

uint16_t GridXY::dX(uint16_t i)
{
    return (i * _dx);
}

uint16_t GridXY::dY(uint16_t i)
{
    return (i * _dy);
}

uint16_t GridXY::x(uint16_t i)
{
    return (_x0 + i * _dx);
}

uint16_t GridXY::y(uint16_t i)
{
    return (_y0 + i * _dy);
}
