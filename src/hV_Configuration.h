///
/// @file hV_Configuration.h
/// @brief Configuration of the options for Pervasive Displays Library Suite
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @n Content
/// * 1- List of supported Pervasive Displays screens
/// * 2- List of pre-configured boards
/// * 3- Font mode, internal MCU or external SPI Flash
/// * 4- Maximum number of fonts
/// * 5- SRAM memory, internal MCU or external SPI
/// * 6- Use self or virtual object
/// * 7- Touch mode, activated or not
/// * 8- Haptic feedback mode, activated or not
/// * 9. Set GPIO expander mode, not implemented
/// * 10. String object of char array options for string.
/// * 11. Set storage mode, serial console by default
/// * 12. Set debug options
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

///
/// @brief Board
/// @details Board low level management
/// @see hV_Board.h
///
#include "hV_Board.h"

#if (hV_BOARD_RELEASE < 1000)
#error Required hV_BOARD_RELEASE 1000
#endif // hV_BOARD_RELEASE

///
/// @brief Constants
/// @details Constants for boards and screens
/// @see hV_List_Constants.h
///
#include "hV_List_Constants.h"

#if (hV_LIST_CONSTANTS_RELEASE < 1000)
#error Required hV_LIST_CONSTANTS_RELEASE 1000
#endif // hV_LIST_CONSTANTS_RELEASE

///
/// @brief Types
/// @details Types for teext and frame-buffer
/// @see hV_List_Types.h
///
#include "hV_List_Types.h"

#if (hV_LIST_TYPES_RELEASE < 1000)
#error Required hV_LIST_TYPES_RELEASE 1000
#endif // hV_LIST_TYPES_RELEASE

#ifndef hV_CONFIGURATION_RELEASE
///
/// @brief Release
///
#define hV_CONFIGURATION_RELEASE 1000

///
/// @brief Licensee
///
// #define LICENSEE_NAME "Name of licensee"

///
/// @brief Boards
/// @details 2- List of pre-configured boards
/// @see hV_List_Boards.h
///
#include "hV_List_Boards.h"

#if (hV_LIST_BOARDS_RELEASE < 1000)
#error Required hV_LIST_BOARDS_RELEASE 1000
#endif // hV_LIST_BOARDS_RELEASE

///
/// @brief Other options
/// @details * 3- Font mode, internal MCU or external SPI Flash
/// * 4- Maximum number of fonts
/// * 5- SRAM memory, internal MCU or external SPI
/// * 6- Use self or virtual object
/// * 7- Touch mode, activated or not
/// * 8- Haptic feedback mode, activated or not
/// * 9. Set GPIO expander mode, not implemented
/// * 10. String object of char array options for string.
/// * 11. Set storage mode, serial console by default
/// * 12. Set debug options
///
/// @see hV_List_Options.h
///
#include "hV_List_Options.h"

#if (hV_LIST_OPTIONS_RELEASE < 1000)
#error Required hV_LIST_OPTIONS_ERELEASE 1000
#endif // hV_LIST_OPTIONS_RELEASE

#endif // hV_CONFIGURATION_RELEASE

