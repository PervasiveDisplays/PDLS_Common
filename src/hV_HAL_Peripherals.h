///
/// @file hV_HAL_Peripherals.h
/// @brief Light hardware abstraction layer for peripherals
///
/// @details Based on highView technology
///
/// @date 21 Dec 2025
/// @version 1001
///
/// @copyright (c) Pervasive Displays Inc., 2021-2026
/// @copyright (c) Etigues, 2010-2026
/// @copyright All rights reserved
/// @copyright For exclusive use with Pervasive Displays screens
///
/// * Basic edition: for hobbyists and for basic usage
/// @n Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
/// @see https://creativecommons.org/licenses/by-sa/4.0/
///
/// @n Consider the Evaluation or Commercial editions for professionals or organisations and for commercial usage
///
/// * Evaluation edition: for professionals or organisations, evaluation only, no commercial usage
/// @n All rights reserved
///
/// * Commercial edition: for professionals or organisations, commercial usage
/// @n All rights reserved
///
/// * Viewer edition: for professionals or organisations
/// @n All rights reserved
///
/// * Documentation
/// @n All rights reserved
///

/// @deprecated Removed synonyms for GPIO (7.0.0)
/// + hV_HAL_GPIO_pinMode() is removed. Use hV_HAL_GPIO_define() instead (7.0.0)
/// + hV_HAL_GPIO_digitalWrite() is removed. Use hV_HAL_GPIO_write(), hV_HAL_GPIO_set() and hV_HAL_GPIO_clear() instead (7.0.0)
/// + hV_HAL_GPIO_digitalRead() is removed. Use hV_HAL_GPIO_read() or hV_HAL_GPIO_get() instead (7.0.0)
///
/// @deprecated Removed synonyms for Time (7.0.0)
/// + hV_HAL_delay() is removed. Use hV_HAL_delayMilliseconds() instead (7.0.0)
///
/// @deprecated Removed synonyms for Serial (7.0.0)
/// + hV_HAL_printf() is removed. Use hV_HAL_Serial_printf() instead (7.0.0)
/// + hV_HAL_crlf() is removed. Use hV_HAL_Serial_crlf() instead (7.0.0)
/// + hV_HAL_Serial_print() and hV_HAL_Serial_println() are not recommended. Use hV_HAL_Serial_printf() and hV_HAL_Serial_crlf() instead (7.0.0)
///
/// @deprecated Removed synonyms for SPI (7.0.0)
/// + hV_HAL_SPI_configure() is removed. Use hV_HAL_SPI_begin() instead (7.0.0)
///
/// @deprecated Removed synonyms for Wire (7.0.0)
/// + hV_HAL_Wire_writeRead() is removed. Use hV_HAL_Wire_transfer() instead (7.0.0)
///
/// @deprecated Removed hV_HAL_Serial_print() and hV_HAL_Serial_println() (10.0.0)
/// + Use hV_HAL_Serial_printf() and hV_HAL_Serial_crlf() instead (10.0.0)
///

#ifndef hV_HAL_PERIPHERALS_RELEASE
///
/// @brief Release
///
#define hV_HAL_PERIPHERALS_RELEASE 1001

///
/// @brief SDK library
/// @see References
/// * Arduino SDK https://www.arduino.cc/reference/en/
/// * Energia SDK https://energia.nu/reference/
///
#include <Arduino.h>

// // Options
// #include "hV_List_Options.h"
//
// #if (hV_LIST_OPTIONS_RELEASE < 1000)
// #error Required hV_LIST_OPTIONS_ERELEASE 1000
// #endif // hV_LIST_OPTIONS_RELEASE

///
/// @brief SDK other libraries
///
#include <SPI.h>
#include <Wire.h>

///
/// @brief Other libraries
///
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

///
/// @brief Serial port
/// @details Serial or Serial1
///
#define hV_HAL_Serial Serial

///
/// @brief Serial port, synonym
///
#define mySerial hV_HAL_Serial

/// @name General
/// @{

///
/// @brief General initialisation
/// @details hV_HAL_Serial initialised at hV_HAL_Serial_Speed
///
void hV_HAL_begin();

///
/// @brief General exit
/// @param code default = 0 = success, otherwise error
/// @note Only used on Linux
///
void hV_HAL_exit(uint8_t code = 0);

/// @}

///
/// @name GPIO
/// @warning
/// * Arduino: GPIO requires pin number, example 4
/// * Mbed: GPIO requires pin name, example D4 or PB_5
/// * Mbed: GPIO is created at call
/// * Mbed: GPIO not suitable for interrupts
/// * Viewer: For compatibility only, GPIO not implemented in Linux
/// @{
#define hV_HAL_GPIO_define(X, Y) (pinMode(X, Y))
#define hV_HAL_GPIO_set(X) (digitalWrite(X, HIGH))
#define hV_HAL_GPIO_clear(X) (digitalWrite(X, LOW))
#define hV_HAL_GPIO_get(X) (digitalRead(X))
#define hV_HAL_GPIO_write(X, Y) (digitalWrite(X, Y))
#define hV_HAL_GPIO_read(X) (digitalRead(X))

void hV_HAL_GPIO_begin(void);

///
/// @brief Undefine GPIO
///
/// @param pin pin number or pin name according to SDK
///
void hV_HAL_GPIO_undefine(uint8_t pin);

///
/// @brief Wait for GPIO
///
/// @param pin pin number or pin name according to SDK
/// @param state HIGH or LOW
///
void hV_HAL_GPIO_waitFor(uint8_t pin, uint8_t state);

/// @}

///
/// @name Time
/// @see https://www.arduino.cc/reference/en/#time
/// @{

#define hV_HAL_delayMilliseconds(X) (delay(X))
#define hV_HAL_delayMicroseconds(X) (delayMicroseconds(X))
#define hV_HAL_getMilliseconds() (millis())
/// @}

///
/// @name Serial console
/// @brief Formatted output to hV_HAL_Serial
/// @note Console already initialised at 115200 by hV_HAL_begin() (6.0.7)
///
/// @{

///
/// @brief Format and send to console
/// @param format see https://www.cplusplus.com/reference/cstdio/printf/ for tokens
/// @param args explicit variadic list required for hV_HAL_Serial_printf()
///
void hV_HAL_Serial_printf(const char * format, ...);

///
/// @brief Print carriage-return line-feed
///
void hV_HAL_Serial_crlf(void);

/// @}

///
/// @name SPI bus
/// @warning SPI.begin()
/// * Arduino: no parameters
/// * ESP32: required parameters for SCK, MOSI and MISO
/// @{

///
/// @brief Configure and start SPI
/// @param speed SPI speed in Hz, 8000000 = default
/// @note Other parameters are
/// * Bit order: MSBFIRST
/// * Data mode: SPI_MODE0
/// @note With check for unique initialisation
///
void hV_HAL_SPI_begin(uint32_t speed = 8000000);

///
/// @brief End SPI
/// @note With check for unique deinitialisation
///
void hV_HAL_SPI_end();

///
/// @brief Combined write and read of a single byte
/// @param data byte
/// @return read byte
/// @warning No check for previous initialisation
///
uint8_t hV_HAL_SPI_transfer(uint8_t data);
/// @}

///
/// @name 3-wire SPI bus
/// @warning
/// * Arduino does not support 3-wire SPI, bit-bang simulation
/// * Viewer: For compatibility only, not implemented in Linux
/// @note hV_HAL_SPI3_begin() sets the pins for 3-wire SPI.
/// @{

#if defined(ENERGIA)

#define SCK 7
#define MOSI 15

#endif // ENERGIA 

///
/// @name 3-wire SPI
/// @{
///

///
/// @brief Configure 3-wire SPI
/// @note Select default SCK as clock and MOSI as data (SDIO)
///
void hV_HAL_SPI3_begin();

///
/// @brief End 3-wire SPI
/// @warning Some platforms require freeing the GPIOs used by 3-wire SPI before starting SPI.
///
void hV_HAL_SPI3_end();

///
/// @brief Set the 3-wire SPI pins
/// @param pinClock clock, default = SCK
/// @param pinData combined data, default = MOSI
/// @note For manual configuration only
/// @warning SCK and MOSI provided by Arduino SDK
/// * Some boards require manual configuration
///
void hV_HAL_SPI3_define(uint8_t pinClock = SCK, uint8_t pinData = MOSI);

///
/// @brief Read a single byte
/// @return read byte
/// @note Configure the clock pin as output and data pin as input.
/// @warning /CS to be managed externally.
///
uint8_t hV_HAL_SPI3_read();

///
/// @brief Write a single byte
/// @param data byte
/// @note Configure the clock and data pins as output.
/// @warning /CS to be managed externally.
///
void hV_HAL_SPI3_write(uint8_t value);

/// @}

///
/// @name Wire bus
///
/// @{

///
/// @brief Configure and start Wire bus
/// @note Master mode only
/// @note With check for unique initialisation
///
void hV_HAL_Wire_begin();

///
/// @brief End Wire bus
/// @note With check for unique deinitialisation
///
void hV_HAL_Wire_end();

///
/// @brief Combined write and read with optional delay
///
/// @param[in] address I2C device address
/// @param[in] dataWrite buffer to write
/// @param[in] sizeWrite number of bytes
/// @param[out] dataRead buffer to read
/// @param[in] sizeRead number of bytes
/// @param[in] us delay in microseconds, default = 0 = no delay
/// @return uint8_t transmission status, RESULT_SUCCESS = 0 or RESULT_ERROR = 1
/// @note If sizeRead = 0, no read performed
/// @warning No check for previous initialisation
///
uint8_t hV_HAL_Wire_transfer(uint8_t address, uint8_t * dataWrite, size_t sizeWrite, uint8_t * dataRead = 0, size_t sizeRead = 0, uint32_t us = 0);

/// @}

///
/// @name Log system
/// @{
///

///
/// @brief Buffer size for log messages
/// @detail Recommended 256 for Viewer, 128 otherwise
#define LOG_TEXT_LENGTH 128

///
/// @brief Log level messages
/// @{
#define LEVEL_CRITICAL 0x0001 ///< `*` Non-handled error, stop or exit
#define LEVEL_INFO 0x0008 ///< `.` Information
#define LEVEL_DEBUG 0x0010 ///< `-` Debug
#define LEVEL_SYSTEM 0x0020 ///< `=` System
/// @}
///

///
/// @brief Send debug message to console
/// @param level Debug level message
/// @param format see https://www.cplusplus.com/reference/cstdio/printf/ for tokens
/// @note With final CR-LF
///
void hV_HAL_log(uint16_t level, const char * format, ...);

/// @}

///
/// @name Miscellaneous
/// @{

///
/// @brief Rescale a value
///
/// @param x input value
/// @param in_min minimal input value
/// @param in_max maximum input value
/// @param out_min minimum output value
/// @param out_max maximum output value
/// @return long output value
/// @note Formula is
/// @code {.cpp}
/// (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
/// @endcode
///
long hV_HAL_map(long x, long in_min, long in_max, long out_min, long out_max);

///
///
/// @brief Minimum of two numbers
///
/// @param a first number
/// @param b second number
/// @return minimum of a and b
///
/// @note Macro more robust than bugged implementation on some platforms
///
#define hV_HAL_min(a, b) ((a) < (b) ? (a) : (b))

///
/// @brief Maximum of two numbers
///
/// @param a first number
/// @param b second number
/// @return maximum of a and b
///
/// @note Macro more robust than bugged implementation on some platforms
///
#define hV_HAL_max(a, b) ((a) > (b) ? (a) : (b))

///
/// @brief Swap numbers
/// @param[out] x first number
/// @param[out] y second number
///
/// @note Macro more robust than template for some platforms
///
/// @code
/// template <typename T> T
/// hV_HAL_swap(T &x, T &y)
/// {
///     T w = x;
///     x = y;
///     y = w;
/// }
/// @endcode
///
/// @note `__typeof__` recommended over `typeof`
///
#define hV_HAL_swap(x, y) do { __typeof__(x) WORK = x; x = y; y = WORK; } while (0)

/// @}

#endif // hV_HAL_PERIPHERALS_RELEASE

