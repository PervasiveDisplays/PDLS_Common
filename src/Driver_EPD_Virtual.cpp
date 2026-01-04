//
// Driver_EPD_Virtual.cpp
// Class library C++ code
// ----------------------------------
//
// Project Pervasive Displays Library Suite
// Based on highView technology
//
// Created by Rei Vilo, 21 Nov 2024
//
// @copyright (c) Pervasive Displays Inc., 2021-2026
// Copyright (c) Etigues, 2010-2026
// Licence All rights reserved
// For exclusive use with Pervasive Displays screens
//
// Release 900: Added new driver library
// Release 902: Improved stability
// Release 906: Added fixes for GCC errors
// Release 912: Added temperature functions to driver
//

#include "Driver_EPD_Virtual.h"

Driver_EPD_Virtual::Driver_EPD_Virtual(eScreen_EPD_t eScreen_EPD, pins_t board)
{
    u_eScreen_EPD = eScreen_EPD;
    b_pin = board;
    // Added fixes for GCC errors on arm-none-eabi-gcc 10.2.1 20201103 and 12.2.1 20230214
    // . internal compiler error: in implicitly_declare_fn, at cp/method.c:2813
    // . default member initializer required before the end of its enclosing class
    u_temperature = 25;
    u_flagOTP = false; // OTP not read
}

void Driver_EPD_Virtual::begin()
{
    ;
}

void Driver_EPD_Virtual::setTemperatureC(int8_t temperatureC)
{
    u_temperature = temperatureC;
}

void Driver_EPD_Virtual::setTemperatureF(int16_t temperatureF)
{
    int8_t temperatureC = ((temperatureF - 32) * 5) / 9; // C = (F - 32) * 5 / 9
    setTemperatureC(temperatureC);
}

void Driver_EPD_Virtual::updateNormal(FRAMEBUFFER_CONST_TYPE frame,
                                      uint32_t size)
{
    ;
}

void Driver_EPD_Virtual::updateNormal(FRAMEBUFFER_CONST_TYPE frame1, FRAMEBUFFER_CONST_TYPE frame2,
                                      uint32_t size)
{
    ;
}

void Driver_EPD_Virtual::updateNormal(FRAMEBUFFER_CONST_TYPE frameM1, FRAMEBUFFER_CONST_TYPE frameM2,
                                      FRAMEBUFFER_CONST_TYPE frameS1, FRAMEBUFFER_CONST_TYPE frameS2,
                                      uint32_t size)
{
    ;
}

void Driver_EPD_Virtual::updateFast(FRAMEBUFFER_CONST_TYPE frame1, FRAMEBUFFER_CONST_TYPE frame2,
                                    uint32_t size)
{
    ;
}

void Driver_EPD_Virtual::updateFast(FRAMEBUFFER_CONST_TYPE frameM1, FRAMEBUFFER_CONST_TYPE frameM2,
                                    FRAMEBUFFER_CONST_TYPE frameS1, FRAMEBUFFER_CONST_TYPE frameS2,
                                    uint32_t size)
{
    ;
}

// void Driver_EPD_Virtual::COG_reset()
// {
//     ;
// }
//
// void Driver_EPD_Virtual::COG_getDataOTP()
// {
//     ;
// }
//
// void Driver_EPD_Virtual::COG_initial()
// {
//     ;
// }
//
// void Driver_EPD_Virtual::COG_sendImageDataNormal()
// {
//     ;
// }
//
// void Driver_EPD_Virtual::COG_update()
// {
//     ;
// }
//
// void Driver_EPD_Virtual::COG_stopDCDC()
// {
//     ;
// }

// void Driver_EPD_Virtual::d_beginTouch()
// {
//     ;
// }

void Driver_EPD_Virtual::d_getRawTouch(touch_t & touch)
{
    touch = { 0, 0, 0, 0};
}

bool Driver_EPD_Virtual::d_getInterruptTouch()
{
    return true;
}

STRING_CONST_TYPE Driver_EPD_Virtual::reference()
{
    return "";
}
