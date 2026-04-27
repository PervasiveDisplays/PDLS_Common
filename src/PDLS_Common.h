///
/// @file PDLS_Common.h
/// @brief Shared low-level libraries for the Pervasive Displays Library Suite
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @date 21 Apr 2026
/// @version 1005
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

#ifndef PDLS_COMMON_RELEASE
///
/// @brief Library release number
///
#define PDLS_COMMON_RELEASE 1005

///
/// @brief Edition
/// @details Basic edition
///
#define EDITION_BASIC

///
/// @brief SDK
/// @details Light HAL for drivers and PDLS
/// @see hV_HAL_Peripherals.h
///
#include "hV_HAL_Peripherals.h"

#if (hV_HAL_PERIPHERALS_RELEASE < 1000)
#error Required hV_HAL_PERIPHERALS_RELEASE 1000
#endif // hV_HAL_PERIPHERALS_RELEASE

#include "hV_Configuration.h"

#if (hV_CONFIGURATION_RELEASE < 1000)
#error Required hV_CONFIGURATION_RELEASE 1000
#endif // hV_HAL_PERIPHERALS_RELEASE

// Utilities
#include "hV_Utilities.h"

#if (hV_UTILITIES_RELEASE < 1000)
#error Required hV_UTILITIES_RELEASE 1000
#endif // hV_UTILITIES_RELEASE

#endif // PDLS_COMMON_RELEASE
