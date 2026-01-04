///
/// @file hV_List_Types.h
/// @brief List of types for Pervasive Displays Library Suite - Basic edition
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

#ifndef hV_LIST_TYPES_RELEASE
///
/// @brief Release
///
#define hV_LIST_TYPES_RELEASE 1000

// SDK
#include "hV_HAL_Peripherals.h"

#if (hV_HAL_PERIPHERALS_RELEASE < 1000)
#error Required hV_HAL_PERIPHERALS_RELEASE 1000
#endif // hV_HAL_PERIPHERALS_RELEASE

// Options
#include "hV_List_Options.h"

#if (hV_LIST_OPTIONS_RELEASE < 1000)
#error Required hV_LIST_OPTIONS_RELEASE 1000
#endif // hV_LIST_OPTIONS_RELEASE

///
/// @brief Type for frame-buffer
/// @details Based on SRAM_MODE selection
///
#define FRAMEBUFFER_TYPE uint8_t *
#define FRAMEBUFFER_CONST_TYPE const uint8_t *

///
/// @brief Buffer size
#define BUFFER_LENGTH 128

#define STRING16_TYPE uint16_t *
#define STRING16_BYREF_TYPE uint16_t *
#define STRING16_CONST_TYPE const uint16_t *

///
/// @brief Type for string
/// @details Based on STRING_MODE selection
///
#define STRING_TYPE String
#define STRING_BYREF_TYPE String &
#define STRING_CONST_TYPE String

#endif // hV_LIST_TYPES_RELEASE

