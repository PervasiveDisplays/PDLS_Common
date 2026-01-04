///
/// @file hV_List_Constants.h
/// @brief List of constants for Pervasive Displays Library Suite
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @date 21 Nov 2025
/// @version 1000
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

// SDK
#include "stdint.h"

#ifndef hV_LIST_CONSTANTS_RELEASE
///
/// @brief Release
///
#define hV_LIST_CONSTANTS_RELEASE 1000

///
/// @name Touch events
/// @note Numbers are sequential and exclusive
///
/// @{
#define TOUCH_EVENT_NONE 0 ///< No touch event
#define TOUCH_EVENT_PRESS 1 ///< Touch press event
#define TOUCH_EVENT_RELEASE 2 ///< Touch release event
#define TOUCH_EVENT_MOVE 3 ///< Touch move event
/// @}
///

///
/// @name Results
/// @note Numbers are sequential and exclusive
///
/// @{
#define RESULT_SUCCESS 0 ///< Success
#define RESULT_ERROR 1 ///< Error
/// @}
///

///
/// @name Orientation constants
/// @note Numbers are sequential and exclusive
/// @{
///
#define ORIENTATION_PORTRAIT 6 ///< Portrait or vertical, higher than large
#define ORIENTATION_LANDSCAPE 7 ///< Landscape or horizontal, larger than high
/// @}
///

///
/// @deprecated Screen name format (8.0.0)
/// * Name format eScreen_EPD_EXT3_<size>_<driver>_<suffix> is deprecated (8.0.0)
/// * Use name format eScreen_EPD_<size>_<film>_<driver> instead (8.0.0)
///

///
/// @brief Screen type
///
#define eScreen_EPD_t uint32_t

///
/// @brief Function for screen macros
///
#define SCREEN(S, F, D) ((uint32_t)((S & 0x0fff) << 16 | (F & 0xff) << 8 | (D & 0xff)))

///
/// @brief Function for extra macros
///
#define EXTRA(E) ((uint32_t)((E & 0x0f) << 28))

///
/// @name Functions for features from screen macros
///
#define SCREEN_SIZE(X) ((uint16_t)((X >> 16) & 0x0fff)) ///< Get size
#define SCREEN_FILM(X) ((uint8_t)((X >> 8) & 0xff)) ///< Get family
#define SCREEN_DRIVER(X) ((uint8_t)(X & 0xff)) ///< Get type
#define SCREEN_EXTRA(X) ((uint8_t)((X >> 28) & 0x0f)) ///< Get extra

///
/// @name Size, mask 0x0fff = 0..4095
/// @{
///
#define SIZE_NONE 0x00 ///< Unknown
#define SIZE_150 150 ///< 1.50"
#define SIZE_152 152 ///< 1.52"
#define SIZE_154 154 ///< 1.54"
#define SIZE_206 206 ///< 2.06"
#define SIZE_213 213 ///< 2.13"
#define SIZE_215 215 ///< 2.15"
#define SIZE_266 266 ///< 2.66"
#define SIZE_271 271 ///< 2.71"
#define SIZE_287 287 ///< 2.87"
#define SIZE_290 290 ///< 2.90"
#define SIZE_340 340 ///< 3.40"
#define SIZE_343 343 ///< 3.43"
#define SIZE_350 350 ///< 3.50"
#define SIZE_370 370 ///< 3.70"
#define SIZE_417 417 ///< 4.17"
#define SIZE_437 437 ///< 4.37"
#define SIZE_565 565 ///< 5.65"
#define SIZE_581 581 ///< 5.81"
#define SIZE_741 741 ///< 7.41"
#define SIZE_969 969 ///< 9.69"
#define SIZE_B98 1198 ///< 11.98"
#define SIZE_1198 1198 ///< 11.98", synonym for `SIZE_B98`
/// @}

///
/// @name Film type, mask 0xff
/// @{
///
#define FILM_NONE 0x00 ///< Unknown
#define FILM_C 'C' ///< Film C, Standard
#define FILM_E 'E' ///< Film E, BWR, deprecated
#define FILM_F 'F' ///< Film E, BWR, deprecated
#define FILM_G 'G' ///< Film G, BWY, deprecated
#define FILM_H 'H' ///< Film H, Freezer
#define FILM_J 'J' ///< Film J, BWR, "Spectra"
#define FILM_K 'K' ///< Film K, Wide temperature and embedded fast update
#define FILM_P 'P' ///< Film P, Embedded fast update
#define FILM_Q 'Q' ///< Film Q, BWRY, "Spectra 4"
#define FILM_T 'T' ///< Film T, proxy for `P` or `K` with touch
/// @}

///
/// @name Driver type, mask 0xff
/// @{
///
#define DRIVER_NONE 0x00 ///< Unknown
#define DRIVER_5 '5' ///< Driver 5
#define DRIVER_6 '6' ///< Driver 6
#define DRIVER_8 '8' ///< Driver 8
#define DRIVER_9 '9' ///< Driver 9
#define DRIVER_A 'A' ///< Driver A
#define DRIVER_B 'B' ///< Driver B
#define DRIVER_C 'C' ///< Driver C
#define DRIVER_D 'D' ///< Driver D
#define DRIVER_E 'E' ///< Driver E
#define DRIVER_F 'F' ///< Driver F
#define DRIVER_G 'G' ///< Driver G
#define DRIVER_H 'H' ///< Driver H
#define DRIVER_J 'J' ///< Driver J
/// @}

///
/// @name Extra, mask 0x0f = 0..15
/// @{
///
#define EXTRA_TOUCH 1 ///< Touch
#define EXTRA_DEMO 2 ///< Demo
/// @}

///
/// @name Screens families
/// @note Numbers are sequential and exclusive
/// @{
#define FAMILY_SMALL 0x01 ///< Small screens
#define FAMILY_MEDIUM 0x02 ///< Medium-sized screens
#define FAMILY_LARGE 0x03 ///< Large screens with two controllers
/// @}

///
/// @brief Function for COG macros
///
#define COG(F, Y) ((uint16_t)((F & 0xff) << 8 | (Y & 0xff)))

///
/// @name Functions for features from screen macros
///
#define COG_FILM(X) ((uint8_t)((X >> 8) & 0xff)) ///< Get film
#define COG_FAMILY(X) ((uint8_t)(X & 0xff)) ///< Get family

///
/// @name List of COG variants
/// @note Numbers are sequential and exclusive
/// @{
///
#define COG_NONE 0x0000 ///< Unknown 
#define COG_NORMAL_LARGE COG(FILM_C, FAMILY_LARGE) ///< Large screens with normal update, C or J or H film 
#define COG_NORMAL_MEDIUM COG(FILM_C, FAMILY_MEDIUM) ///< Medium screens with normal update, C or J or H film
#define COG_NORMAL_SMALL COG(FILM_C, FAMILY_SMALL) ///< Small screens with normal update, C or J or H film
#define COG_FAST_LARGE COG(FILM_P, FAMILY_LARGE) ///< Medium screens with embedded fast update, P film
#define COG_FAST_MEDIUM COG(FILM_P, FAMILY_MEDIUM) ///< Large screens with embedded fast update, P film
#define COG_FAST_SMALL COG(FILM_P, FAMILY_SMALL) ///< Small screens with embedded fast update, P film
#define COG_BWRY_LARGE COG(FILM_Q, FAMILY_LARGE) ///< Large screens with BWRY colours, Q film
#define COG_BWRY_MEDIUM COG(FILM_Q, FAMILY_MEDIUM) ///< Medium screens with BWRY colours, Q film
#define COG_BWRY_SMALL COG(FILM_Q, FAMILY_SMALL) ///< Small screens with BWRY colours, Q film
#define COG_WIDE_LARGE COG(FILM_K, FAMILY_LARGE) ///< Large screens with wide temperature and embedded fast update, K film
#define COG_WIDE_MEDIUM COG(FILM_K, FAMILY_MEDIUM) ///< Medium screens with wide temperature and embedded fast update, K film
#define COG_WIDE_SMALL COG(FILM_K, FAMILY_SMALL) ///< Small screens with wide temperature and embedded fast update, K film
#define COG_TOUCH_SMALL COG(FILM_T, FAMILY_SMALL) ///< Small screens with wide temperature and embedded fast update, T film
/// @}
///

///
/// @name List of screens
/// @deprecated Screens are now listed in each driver (9.0.0)
///
/// @{

/// @}

///
/// @name Large screens sub-panels selection
/// @note Numbers are sequential and exclusive
/// @{
#define PANEL_CS_MASTER 0x01 ///< Large screens sub-panels: first panel only
#define PANEL_CS_SLAVE 0x02 ///< Large screens sub-panels: second panel only
#define PANEL_CS_BOTH 0x03 ///< Large screens sub-panels: both panels
/// @}

///
/// @name Scopes for power profile
/// @note Numbers are sequential and exclusive
/// @{
#define POWER_SCOPE_NONE 0x00 ///< Nothing suspended
#define POWER_SCOPE_GPIO_ONLY 0x01 ///< GPIO only and if panelPower defined
#define POWER_SCOPE_BUS_GPIO 0x11 ///< Both bus and GPIO suspended
/// @}

///
/// @name Modes for power profile
/// @note Numbers are sequential and exclusive
/// @{
#define POWER_MODE_MANUAL 0x00 ///< Managed by the application code
#define POWER_MODE_AUTO 0x01 ///< Managed by the screen library
/// @}

///
/// @name Power and GPIO state
/// @note Numbers are sequential and exclusive, except MASK
/// @{
#define FSM_OFF 0x00 ///< Bus off, GPIO off or undefined
#define FSM_ON 0x11 ///< Bus on, GPIO on or defined
#define FSM_SLEEP 0x10 ///< Bus on, GPIO and Power off or undefined
#define FSM_GPIO_MASK 0x01 ///< Mask for GPIO on or defined
#define FSM_BUS_MASK 0x10 ///< Mask for bus on
/// @}

///
/// @name Update mode
/// @note Numbers are sequential and exclusive
/// @deprecated Partial update is removed. Use fast update instead (7.0.0)
/// @deprecated GLOBAL_UPDATE is removed. Use UPDATE_NORMAL instead (9.0.0)
/// @{
#define UPDATE_NONE 0x00 ///< No update
#define UPDATE_NORMAL 0x01 ///< Normal update, default
#define UPDATE_FAST 0x02 ///< Fast update
#define UPDATE_PARTIAL 0x03 ///< Partial update, deprecated
/// @}

///
/// @name Large screens sub-panels selection
/// @note Numbers are sequential and exclusive
/// @{
#define PANEL_CS_MASTER 0x01 ///< Large screens sub-panels: first panel only
#define PANEL_CS_SLAVE 0x02 ///< Large screens sub-panels: second panel only
#define PANEL_CS_BOTH 0x03 ///< Large screens sub-panels: both panels
/// @}

///
/// @name Frame-buffer sizes
/// @details
/// * Black-white-red screens and monochrome screens
/// @n Frame-buffer size = width * height / 8 * depth, uint32_t
/// @n Depth = 2
/// * Black-white-red-yellow screens
/// @n Frame-buffer size = width * height / 4 * depth, uint32_t
/// @n Depth = 1
/// @{
///
#define frameSize_EPD_150 (uint32_t)(10000) ///< reference 150-xS-0x
#define frameSize_EPD_152 (uint32_t)(10000) ///< reference 152-xS-0x
#define frameSize_EPD_154 (uint32_t)(5776) ///< reference 154-xS-0x
#define frameSize_EPD_206 (uint32_t)(7936) ///< reference 206-xS-0x
#define frameSize_EPD_213 (uint32_t)(5512) ///< reference 213-xS-0x
#define frameSize_EPD_266 (uint32_t)(11248) ///< reference 266-xS-0x
#define frameSize_EPD_270 (uint32_t)(11616) ///< reference 271-xS-0x, legacy name
#define frameSize_EPD_271 (uint32_t)(11616) ///< reference 271-xS-0x
#define frameSize_EPD_287 (uint32_t)(9472) ///< reference 287-xS-0x
#define frameSize_EPD_290 (uint32_t)(16128) ///< reference 290-xS-0x
#define frameSize_EPD_340 (uint32_t)(22344) ///< reference 340-xS-0x
#define frameSize_EPD_343 (uint32_t)(22344) ///< reference 343-xS-0x, legacy name
#define frameSize_EPD_350 (uint32_t)(24960) ///< reference 350-xS-0x
#define frameSize_EPD_370 (uint32_t)(24960) ///< reference 370-xS-0x
#define frameSize_EPD_417 (uint32_t)(30000) ///< reference 417-xS-0x
#define frameSize_EPD_437 (uint32_t)(21120) ///< reference 437-xS-0x
#define frameSize_EPD_565 (uint32_t)(33600) ///< reference 565-xS-0x
#define frameSize_EPD_581 (uint32_t)(46080) ///< reference 581-xS-0x
#define frameSize_EPD_741 (uint32_t)(96000) ///< reference 741-xS-0x
#define frameSize_EPD_969 (uint32_t)(161280) ///< reference 969-xS-0x
#define frameSize_EPD_B98 (uint32_t)(184320) ///< reference xE21198xS0xx
/// @}

#endif // hV_LIST_CONSTANTS_RELEASE

