//
// hV_Board.cpp
// Library C++ code
// ----------------------------------
//
// Project Pervasive Displays Library Suite
// Based on highView technology
//
// Created by Rei Vilo, 16 Aug 2023
//
// Copyright (c) Pervasive Displays Inc., 2021-2026
// Copyright (c) Etigues, 2010-2026
// Licence All rights reserved
// For exclusive use with Pervasive Displays screens
//
// Release 700: Initial release
// Release 801: Improved double-panel screen management
// Release 804: Improved power management
// Release 810: Added support for EXT4
// Release 900: Added new driver library
// Release 900: Consolidated constants
// Release 906: Added check for panel power
// Release 1000: Unified boards definition
// Release 1002: Added extra delays before commands
//

// Library header
#include "hV_Board.h"

hV_Board::hV_Board()
{
    b_fsmPowerScreen = FSM_OFF;
}

void hV_Board::b_begin(pins_t board, uint8_t family, uint16_t delayCS)
{
    b_pin = board;
    b_family = family;
    b_delayCS = delayCS;
    b_fsmPowerScreen = FSM_OFF;
}

void hV_Board::b_reset(uint32_t ms1, uint32_t ms2, uint32_t ms3, uint32_t ms4, uint32_t ms5)
{
    hV_HAL_delayMilliseconds(ms1); // Wait for power stabilisation
    hV_HAL_GPIO_set(b_pin.panelReset); // RESET = HIGH
    hV_HAL_delayMilliseconds(ms2);
    hV_HAL_GPIO_clear(b_pin.panelReset); // RESET = LOW
    hV_HAL_delayMilliseconds(ms3);
    hV_HAL_GPIO_set(b_pin.panelReset); // RESET = HIGH
    hV_HAL_delayMilliseconds(ms4);
    hV_HAL_GPIO_set(b_pin.panelCS); // CS = HIGH, unselect
    hV_HAL_delayMilliseconds(ms5);
}

void hV_Board::b_waitBusy(bool state)
{
    hV_HAL_GPIO_waitFor(b_pin.panelBusy, state); // non-blocking
}

void hV_Board::b_suspend()
{
    if ((b_fsmPowerScreen & FSM_GPIO_MASK) == FSM_GPIO_MASK)
    {
        // Optional power circuit
        if (b_pin.panelPower != NOT_CONNECTED) // generic
        {
            hV_HAL_GPIO_clear(b_pin.panelPower);
        }
        b_fsmPowerScreen &= ~FSM_GPIO_MASK;
    }
}

void hV_Board::b_resume()
{
    // Target FSM_ON
    // Source FSM_SLEEP -> FSM_SLEEP
    //        FSM_OFF   -> FSM_SLEEP

    if ((b_fsmPowerScreen & FSM_GPIO_MASK) != FSM_GPIO_MASK)
    {
        // Initialise GPIO expander
        hV_HAL_GPIO_begin();

        // Optional power circuit
        if (b_pin.panelPower != NOT_CONNECTED) // generic
        {
            hV_HAL_GPIO_define(b_pin.panelPower, OUTPUT);
            hV_HAL_GPIO_set(b_pin.panelPower);
        }

        // Configure GPIOs
        hV_HAL_GPIO_define(b_pin.panelBusy, INPUT);

        hV_HAL_GPIO_define(b_pin.panelDC, OUTPUT);
        hV_HAL_GPIO_set(b_pin.panelDC);

        hV_HAL_GPIO_define(b_pin.panelReset, OUTPUT);
        hV_HAL_GPIO_set(b_pin.panelReset);

        hV_HAL_GPIO_define(b_pin.panelCS, OUTPUT);
        hV_HAL_GPIO_set(b_pin.panelCS); // CS# = 1

        if (b_pin.panelCSS != NOT_CONNECTED) // generic
        {
            hV_HAL_GPIO_define(b_pin.panelCSS, OUTPUT);
            hV_HAL_GPIO_set(b_pin.panelCSS);
        }

        // External SPI memory
        if (b_pin.flashCS != NOT_CONNECTED) // generic
        {
            hV_HAL_GPIO_define(b_pin.flashCS, OUTPUT);
            hV_HAL_GPIO_set(b_pin.flashCS);
        }
        if (b_pin.flashCSS != NOT_CONNECTED) // generic
        {
            hV_HAL_GPIO_define(b_pin.flashCSS, OUTPUT);
            hV_HAL_GPIO_set(b_pin.flashCSS);
        }

        // External SD card
        if (b_pin.cardCS != NOT_CONNECTED) // generic
        {
            hV_HAL_GPIO_define(b_pin.cardCS, OUTPUT);
            hV_HAL_GPIO_set(b_pin.cardCS);
        }
        if (b_pin.cardDetect != NOT_CONNECTED) // generic
        {
            hV_HAL_GPIO_define(b_pin.cardCS, INPUT);
        }

        if (b_pin.scope == BOARD_EXT4)
        {
            if (b_pin.button != NOT_CONNECTED) // generic
            {
                hV_HAL_GPIO_define(b_pin.button, INPUT_PULLUP);
            }

            if (b_pin.ledData != NOT_CONNECTED) // generic
            {
                hV_HAL_GPIO_define(b_pin.ledData, OUTPUT);
            }

            if (b_pin.nfcFD != NOT_CONNECTED) // generic
            {
                hV_HAL_GPIO_define(b_pin.nfcFD, INPUT);
            }

            if (b_pin.imuInt1 != NOT_CONNECTED) // generic
            {
                hV_HAL_GPIO_define(b_pin.imuInt1, INPUT);
            }

            if (b_pin.imuInt2 != NOT_CONNECTED) // generic
            {
                hV_HAL_GPIO_define(b_pin.imuInt2, INPUT);
            }

            if (b_pin.weatherInt != NOT_CONNECTED) // generic
            {
                hV_HAL_GPIO_define(b_pin.weatherInt, INPUT);
            }
        } // BOARD_EXT4

        b_fsmPowerScreen |= FSM_GPIO_MASK;
    }
}

void hV_Board::b_sendIndexFixed(uint8_t index, uint8_t data, uint32_t size)
{
    hV_HAL_GPIO_clear(b_pin.panelDC); // DC Low = Command
    hV_HAL_GPIO_clear(b_pin.panelCS); // CS Low = Select

    hV_HAL_delayMicroseconds(b_delayCS);
    hV_HAL_SPI_transfer(index);
    hV_HAL_delayMicroseconds(b_delayCS);

    hV_HAL_GPIO_set(b_pin.panelDC); // DC High = Data

    hV_HAL_delayMicroseconds(b_delayCS);
    for (uint32_t i = 0; i < size; i++)
    {
        hV_HAL_SPI_transfer(data); // b_sendIndexFixed
    }
    hV_HAL_delayMicroseconds(b_delayCS);

    hV_HAL_GPIO_set(b_pin.panelCS); // CS High = Unselect
}

void hV_Board::b_sendIndexFixedSelect(uint8_t index, uint8_t data, uint32_t size, uint8_t select)
{
    hV_HAL_GPIO_clear(b_pin.panelDC); // DC Low = Command
    b_select(select); // Select half of large screen

    hV_HAL_delayMicroseconds(b_delayCS); // Longer delay for large screens
    hV_HAL_SPI_transfer(index);
    hV_HAL_delayMicroseconds(b_delayCS); // Longer delay for large screens

    hV_HAL_GPIO_set(b_pin.panelDC); // DC High = Data

    hV_HAL_delayMicroseconds(b_delayCS); // Longer delay for large screens
    for (uint32_t i = 0; i < size; i++)
    {
        hV_HAL_SPI_transfer(data); // b_sendIndexFixed
    }
    hV_HAL_delayMicroseconds(b_delayCS); // Longer delay for large screens

    hV_HAL_GPIO_set(b_pin.panelCS); // CS High = Unselect Master
    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        hV_HAL_GPIO_set(b_pin.panelCSS); // CSS High = Unselect Slave
    }
}

void hV_Board::b_sendIndexData(uint8_t index, const uint8_t * data, uint32_t size)
{
    // Command mode
    hV_HAL_GPIO_clear(b_pin.panelDC); // DC Low = Command

    // Select
    hV_HAL_GPIO_clear(b_pin.panelCS); // CS Low = Select
    if (b_family == FAMILY_LARGE) // panelCSS already checked
    {
        hV_HAL_GPIO_clear(b_pin.panelCSS);
        hV_HAL_delayMicroseconds(450); // 450 + 50 = 500
    }
    hV_HAL_delayMicroseconds(b_delayCS);

    // Send command
    hV_HAL_SPI_transfer(index);
    hV_HAL_delayMicroseconds(b_delayCS);

    // Data mode
    hV_HAL_GPIO_set(b_pin.panelDC); // DC High = Data

    hV_HAL_delayMicroseconds(b_delayCS);

    // Send data
    for (uint32_t i = 0; i < size; i++)
    {
        hV_HAL_SPI_transfer(data[i]);
    }

    // Unselect
    hV_HAL_delayMicroseconds(b_delayCS);
    hV_HAL_GPIO_set(b_pin.panelCS); // CS High
    if (b_family == FAMILY_LARGE) // panelCSS already checked
    {
        hV_HAL_delayMicroseconds(450); // 450 + 50 = 500
        hV_HAL_GPIO_set(b_pin.panelCSS);
    }
    hV_HAL_delayMicroseconds(b_delayCS);
}

// Software SPI Master protocol setup
void hV_Board::b_sendIndexDataSelect(uint8_t index, const uint8_t * data, uint32_t size, uint8_t select)
{
    hV_HAL_GPIO_clear(b_pin.panelDC); // DC Low = Command
    b_select(select); // Select half of large screen

    hV_HAL_delayMicroseconds(b_delayCS); // Longer delay for large screens
    hV_HAL_SPI_transfer(index);
    hV_HAL_delayMicroseconds(b_delayCS); // Longer delay for large screens

    hV_HAL_GPIO_set(b_pin.panelDC); // DC High = Data

    hV_HAL_delayMicroseconds(b_delayCS); // Longer delay for large screens
    for (uint32_t i = 0; i < size; i++)
    {
        hV_HAL_SPI_transfer(data[i]);
    }
    hV_HAL_delayMicroseconds(b_delayCS); // Longer delay for large screens

    hV_HAL_GPIO_set(b_pin.panelCS); // CS High = Unselect Master
    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        hV_HAL_GPIO_set(b_pin.panelCSS); // CSS High = Unselect Slave
    }
}

void hV_Board::b_select(uint8_t select)
{
    switch (select)
    {
        case PANEL_CS_MASTER:

            hV_HAL_GPIO_clear(b_pin.panelCS); // CS Low = Select Master
            if (b_pin.panelCSS != NOT_CONNECTED)
            {
                hV_HAL_GPIO_set(b_pin.panelCSS); // CSS High = Unselect Slave
            }
            break;

        case PANEL_CS_SLAVE:

            hV_HAL_GPIO_set(b_pin.panelCS); // CS High = Unselect Master
            if (b_pin.panelCSS != NOT_CONNECTED)
            {
                hV_HAL_GPIO_clear(b_pin.panelCSS); // CSS Low = Select Slave
            }
            break;

        default:

            hV_HAL_GPIO_clear(b_pin.panelCS); // CS Low = Select Master
            if (b_pin.panelCSS != NOT_CONNECTED)
            {
                hV_HAL_GPIO_clear(b_pin.panelCSS); // CSS Low = Select Slave
            }
            break;
    }

    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        hV_HAL_delayMicroseconds(450); // 450 + 50 = 500
    }
    hV_HAL_delayMicroseconds(b_delayCS); // Longer delay for large screens
}

void hV_Board::b_sendCommandDataSelect8(uint8_t command, uint8_t data, uint8_t select)
{
    // For an unknown reason, extra delay required for some MCUs
    hV_HAL_delayMilliseconds(1); // Ensure minimum timing

    hV_HAL_GPIO_clear(b_pin.panelDC); // LOW = command
    b_select(select); // Select half of large screen

    hV_HAL_SPI_transfer(command);

    hV_HAL_GPIO_set(b_pin.panelDC); // HIGH = data
    hV_HAL_SPI_transfer(data);

    hV_HAL_GPIO_set(b_pin.panelCS);
    if (b_pin.panelCSS != NOT_CONNECTED)
    {
        hV_HAL_GPIO_set(b_pin.panelCSS);
    }
}

void hV_Board::b_sendCommand8(uint8_t command)
{
    // For an unknown reason, extra delay required for some MCUs
    hV_HAL_delayMilliseconds(1); // Ensure minimum timing

    hV_HAL_GPIO_clear(b_pin.panelDC);
    hV_HAL_GPIO_clear(b_pin.panelCS);

    hV_HAL_SPI_transfer(command);

    hV_HAL_GPIO_set(b_pin.panelCS);
}

void hV_Board::b_sendCommandData8(uint8_t command, uint8_t data)
{
    // For an unknown reason, extra delay required for some MCUs
    hV_HAL_delayMilliseconds(1); // Ensure minimum timing

    hV_HAL_GPIO_clear(b_pin.panelDC); // LOW = command
    hV_HAL_GPIO_clear(b_pin.panelCS);

    hV_HAL_SPI_transfer(command);

    hV_HAL_GPIO_set(b_pin.panelDC); // HIGH = data
    hV_HAL_SPI_transfer(data);

    hV_HAL_GPIO_set(b_pin.panelCS);
}

