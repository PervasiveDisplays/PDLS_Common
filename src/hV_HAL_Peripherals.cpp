//
// hV_HAL_Peripherals.cpp
// Library C++ code
// ----------------------------------
//
// Details Light hardware abstraction layer for peripherals
// Project highView Library Suite
//
// Created by Rei Vilo, 08 Jan 2024
//
// Copyright (c) Etigues, 2010-2026
// Licence All rights reserved
// For exclusive use with Pervasive Displays screens
//
// * Basic edition: for hobbyists and for basic usage
// Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
//
// * Evaluation edition: for professionals or organisations, evaluation only, no commercial usage
// All rights reserved
//
// * Commercial edition: for professionals or organisations, commercial usage
// All rights reserved
//
// Release 800: Added 3-wire SPI
// Release 801: Added SPI configuration
// Release 803: Improved stability
// Release 804: Improved power management
// Release 805: Improved stability
// Release 900: Shared peripherals
// Release 907: Added patches for ESP32 platform
// Release 908: Fixed SPI settings for ESP32 platform
// Release 909: Added I2C device availability check
// Release 911: Added delay on I²C write and read transfer
// Release 911: Added overtime check on I²C write and read transfer
// Release 922: Improved 3-wire SPI stability
// Release 922: Ported to C
//

// Library header
#include "hV_HAL_Peripherals.h"

//
// === General section
//
#if defined(ENERGIA)
///
/// @brief Proxy for SPISettings
/// @details Not implemented in Energia
/// @see https://www.arduino.cc/en/Reference/SPISettings
///
struct _SPISettings_s
{
    uint32_t clock; ///< in Hz, checked against SPI_CLOCK_MAX = 16000000
    uint8_t bitOrder; ///< LSBFIRST, MSBFIRST
    uint8_t dataMode; ///< SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3
};
///
/// @brief SPI settings for screen
///
_SPISettings_s _settingScreen;
#else
///
/// @brief SPI settings for screen
///
SPISettings _settingScreen;
#endif // ENERGIA

#ifndef SPI_CLOCK_MAX
#define SPI_CLOCK_MAX 16000000
#endif

struct h_pinSPI3_t
{
    uint8_t pinClock;
    uint8_t pinData;
};

h_pinSPI3_t h_pinSPI3;

void hV_HAL_begin()
{
    hV_HAL_Serial.begin(115200);
    hV_HAL_Serial_crlf();
    hV_HAL_log(LEVEL_INFO, "Begin");

    // #if defined(ARDUINO_XIAO_ESP32C3)
    //
    //     // Board Xiao ESP32-C3 crashes if pins are not specified.
    //     // SPI.begin(8, 9, 10); // SCK MISO MOSI
    //     hV_HAL_SPI3_define(8, 10) // SCK SDA=MOSI
    //
    // #elif defined(ARDUINO_ESP32_PICO)
    //
    //     // void begin(int8_t sck=-1, int8_t miso=-1, int8_t mosi=-1, int8_t ss=-1);
    //     // Board ESP32-Pico-DevKitM-2 crashes if pins are not specified.
    //     // SPI.begin(14, 12, 13); // SCK MISO MOSI
    //     hV_HAL_SPI3_define(14, 13); // SCK SDA=MOSI
    //
    // #if defined(ARDUINO_ARCH_ESP32)
    //
    //     // Other ESP32 boards crash if pins are not specified.
    //     // SPI.begin(14, 12, 13); // SCK MISO MOSI
    //     hV_HAL_SPI3_define(14, 13); // SCK SDA=MOSI
    //
    // #else // General case

    hV_HAL_SPI3_define(SCK, MOSI); // SCK SDA=MOSI

    // #endif // ARDUINO
}

void hV_HAL_exit(uint8_t code)
{
    hV_HAL_log(LEVEL_INFO, "Exit with code %i", code);
    hV_HAL_Serial_crlf();
    while (true)
    {
        hV_HAL_delayMilliseconds(1000);
    }
}
//
// === End of General section
//

//
// === GPIO section
//
void hV_HAL_GPIO_begin()
{
    ;
}

void hV_HAL_GPIO_undefine(uint8_t pin)
{
#if defined(ENERGIA)

#if defined(ENERGIA_ARCH_CC13X2) || defined(ENERGIA_ARCH_CC13XX)

#ifdef WITH_STOPDIGITALIO // --- Option 1

    stopDigitalIO(pin);

#else // --- Option 2

    GPIOCC26xx_release(pin);

#endif // WITH_STOPDIGITALIO

#endif // ENERGIA_ARCH_CC13X2 or ENERGIA_ARCH_CC13XX

#endif // ENERGIA
}

void hV_HAL_GPIO_waitFor(uint8_t pin, uint8_t state)
{
    while (hV_HAL_GPIO_get(pin) != state)
    {
        hV_HAL_delayMilliseconds(32); // non-blocking
    }
}
//
// === End of GPIO section
//

//
// === Time section
//

//
// === End of Time section
//

//
// === SPI section
//
bool flagSPI = false; // Some SPI implementations require unique initialisation

void hV_HAL_SPI_begin(uint32_t speed)
{
    if (flagSPI != true)
    {
        _settingScreen = {speed, MSBFIRST, SPI_MODE0};

#if defined(ENERGIA) // ENERGIA

        SPI.begin();
        SPI.setBitOrder(_settingScreen.bitOrder);
        SPI.setDataMode(_settingScreen.dataMode);
        SPI.setClockDivider(SPI_CLOCK_MAX / min(SPI_CLOCK_MAX, _settingScreen.clock));

#else  // ARDUINO

        // #if defined(ARDUINO_XIAO_ESP32C3)
        //
        //         // Board Xiao ESP32-C3 crashes if pins are specified.
        //         SPI.begin(8, 9, 10); // SCK MISO MOSI
        //
        // #elif defined(ARDUINO_ESP32_PICO)
        //
        //         // Board ESP32-Pico-DevKitM-2 crashes if pins are not specified.
        //         SPI.begin(14, 12, 13); // SCK MISO MOSI
        //
        // #elif defined(ARDUINO_ARCH_ESP32)
        //
        //         // Other ESP32 boards crash if pins are not specified.
        //         SPI.begin(14, 12, 13); // SCK MISO MOSI
        //         // hV_HAL_SPI3_define(14, 13); // SCK SDA=MOSI

#if defined(ARDUINO_ARCH_ESP32)

        // ESP32 boards crash if pins are not specified.
        SPI.begin(SCK, MISO, MOSI); // SCK MISO MOSI

#else // General case

        SPI.begin();

#endif // SPI specifics

        SPI.beginTransaction(_settingScreen);

#endif // ENERGIA

        flagSPI = true;
    }
}

void hV_HAL_SPI_end()
{
    if (flagSPI != false)
    {
        SPI.end();
        flagSPI = false;
    }
}

uint8_t hV_HAL_SPI_transfer(uint8_t data)
{
    return SPI.transfer(data);
}

//
// === End of SPI section
//

//
// === 3-wire SPI section
//
void hV_HAL_SPI3_begin()
{
    ;
}

void hV_HAL_SPI3_end()
{
    hV_HAL_GPIO_undefine(h_pinSPI3.pinClock);
    hV_HAL_GPIO_undefine(h_pinSPI3.pinData);
}

void hV_HAL_SPI3_define(uint8_t pinClock, uint8_t pinData)
{
    h_pinSPI3.pinClock = pinClock;
    h_pinSPI3.pinData = pinData;
}

uint8_t hV_HAL_SPI3_read()
{
    uint8_t value = 0;

    pinMode(h_pinSPI3.pinClock, OUTPUT);
    pinMode(h_pinSPI3.pinData, INPUT);

    for (uint8_t i = 0; i < 8; ++i)
    {
        digitalWrite(h_pinSPI3.pinClock, HIGH);
        delayMicroseconds(1);
        value |= digitalRead(h_pinSPI3.pinData) << (7 - i);
        digitalWrite(h_pinSPI3.pinClock, LOW);
        delayMicroseconds(1);
    }

    return value;
}

void hV_HAL_SPI3_write(uint8_t value)
{
    pinMode(h_pinSPI3.pinClock, OUTPUT);
    pinMode(h_pinSPI3.pinData, OUTPUT);

    for (uint8_t i = 0; i < 8; i++)
    {
        digitalWrite(h_pinSPI3.pinData, !!(value & (1 << (7 - i))));
        delayMicroseconds(1);
        digitalWrite(h_pinSPI3.pinClock, HIGH);
        delayMicroseconds(1);
        digitalWrite(h_pinSPI3.pinClock, LOW);
        delayMicroseconds(1);
    }
}
//
// === End of 3-wire SPI section
//

//
// === Wire section
//
bool flagWire = false; // Some Wire implementations require unique initialisation

void hV_HAL_Wire_begin()
{
    if (flagWire == false)
    {
        Wire.begin();

#if defined(ENERGIA)

#if defined(ENERGIA_ARCH_MSP430ELF)

        Wire.setClock(100000UL); // 100 kHz for MSP430

#endif // ENERGIA_ARCH_MSP430ELF

#else // ARDUINO

        Wire.setClock(400000L); // 400 kHz

#endif // ENERGIA ARDUINO
        flagWire = true;
    }
}

void hV_HAL_Wire_end()
{
    if (flagWire == true)
    {
        Wire.end();
        flagWire = true;
    }
}

uint8_t hV_HAL_Wire_transfer(uint8_t address, uint8_t * dataWrite, size_t sizeWrite, uint8_t * dataRead, size_t sizeRead, uint32_t us)
{
    uint8_t result = 0;

    if (sizeWrite > 0)
    {
        Wire.beginTransmission(address);

        for (uint8_t index = 0; index < sizeWrite; index++)
        {
            Wire.write(dataWrite[index]);
        }

        result = Wire.endTransmission();

#if defined(ENERGIA)

        // Energia-MT I2C thread may hang
        delay(4);

#endif // ENERGIA
    }

    if (us > 0)
    {
        hV_HAL_delayMicroseconds(us);
    }

    if (sizeRead > 0)
    {
        memset(dataRead, 0x00, sizeRead);
        Wire.requestFrom(address, sizeRead);
        uint8_t count = 8;
        while ((Wire.available() < sizeRead) and (count > 0))
        {
            delay(4);
            count -= 1;
        }

        if ((count == 0) and (Wire.available() < sizeRead))
        {
            // hV_HAL_log(LEVEL_ERROR, "I2C device 0x%02x overtime", address);
            return 1;
        }

        for (uint8_t index = 0; index < sizeRead; index++)
        {
            dataRead[index] = Wire.read();
        }
    }

    // endTransmission() returns a status code
    // 0: success.
    // 1: data too long to fit in transmit buffer.
    // 2: received NACK on transmit of address.
    // 3: received NACK on transmit of data.
    // 4: other error.
    // 5: timeout
    // See https://docs.arduino.cc/language-reference/en/functions/communication/wire/endTransmission/

    // #define RESULT_SUCCESS 0 ///< Success
    // #define RESULT_ERROR 1 ///< Error

    return (result == 0) ? 0 : 1;
}
//
// === End of Wire section
//

//
// === Serial section
//
void hV_HAL_Serial_printf(const char * format, ...)
{
    char buffer[LOG_TEXT_LENGTH] = {0x00};

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, 255, format, args);
    va_end(args);
    hV_HAL_Serial.print(buffer);
}

void hV_HAL_Serial_crlf()
{
    hV_HAL_Serial.println();
}
//
// === End of Serial section
//

//
// === Log system
//

void hV_HAL_log(uint16_t level, const char * format, ...)
{
    // --- Levels
    // #define LEVEL_CRITICAL 0x0001 ///< `*` Non-handled error, stop or exit
    // #define LEVEL_INFO 0x0008 ///< `.` Information
    // #define LEVEL_DEBUG 0x0010 ///< `-` Debug
    // #define LEVEL_SYSTEM 0x0020 ///< `=` System

    char buffer[LOG_TEXT_LENGTH] = {0x00};

    // Content
    char * frame = &buffer[strlen(buffer)];
    va_list args;
    va_start(args, format);
    vsnprintf(frame, 255, format, args);
    va_end(args);

    hV_HAL_Serial.print("hV _ ");
    hV_HAL_Serial.println(buffer);
}
//
// === End of Log system
//

//
// === Miscellaneous section
//
long hV_HAL_map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//
// === End of Miscellaneous section
//

