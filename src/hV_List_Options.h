///
/// @file hV_List_Options.h
/// @brief List of options for Pervasive Displays Library Suite - Basic edition
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
///
/// @n Content
/// * 1- List of supported Pervasive Displays screens, deprecated, see drivers
/// * 2- List of pre-configured boards, see hV_List_Boards.h
/// * 3- Font mode, internal MCU for basic edition
/// * 4- Maximum number of fonts
/// * 5- SRAM memory, internal MCU for basic edition
/// * 6- Use self for basic edition, not implemented
/// * 7- Touch mode, activated or not, not implemented
/// * 8- Haptic feedback mode, not implemented
/// * 9. Set GPIO expander mode, not implemented
/// * 10. String object for basic edition
/// * 11. Set storage mode, not implemented
/// * 12. Set debug options, not implemented
/// * 13. Select board, deprecated, see hV_List_Boards
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

#ifndef hV_LIST_OPTIONS_RELEASE
///
/// @brief Release
///
#define hV_LIST_OPTIONS_RELEASE 1001

///
/// @name 1- List of supported Pervasive Displays screens
/// @deprecated The list of screens is deprecated. See the drivers header files for the list of supported screens (9.0.0)
///

///
/// @name 2- List of pre-configured boards
/// @see hV_List_Boards.h
///

///
/// @name 3- Set font mode
/// @details From header files or from external flash
/// * Basic edition: 8-bit Terminal font
/// * Evaluation edition: 16-bit Noto font as header
/// * Commercial edition: 16-bit Noto font as header
/// * Viewer edition: 16-bit Noto font as header
///
/// @note USE_FONT_HEADER requires addFont()
/// @note Font Manager requires USE_FONT_HEADER
/// @warning 8- and 16-bit MCUs may limit the size of the fonts. Use 32-bit MCUs for optimal performance.
///
/// @{
#define USE_FONT_TERMINAL 1 ///< Use default Terminal fonts

#define FONT_MODE USE_FONT_TERMINAL ///< Selected option
/// @}

///
/// @brief 4- Maximum number of fonts
/// @details With MCU Flash, based on available memory, check performed at compilation
/// * USE_FONT_TERMINAL: 1..4
/// * USE_FONT_HEADER: 1..64
///
/// With SPI Flash, based on the fonts previously uploaded
/// * USE_FONT_FLASH: eg. 64
///
#if (FONT_MODE == USE_FONT_TERMINAL)
#define MAX_FONT_SIZE 4
#else
#define MAX_FONT_SIZE 64
#endif

///
/// @name 5- Set SRAM memory
/// @details From internal MCU or external SPI
/// * Basic edition: MCU internal SRAM
/// * Commercial edition: MCU internal SRAM
/// * Evaluation edition: MCU internal or SPI external SRAM
/// * Viewer edition: MCU internal SRAM
///
/// @note Corresponding type defined at hV_List_Types.h
///
/// @{
/// @note Commercial edition only
/// @}

///
/// @name 6- Use virtual object
/// @details From hV_Screen_Virtual.h for extended compability
/// @note Declare additional variables if USE_hV_SCREEN_SELF
/// @n Virtual object requires <1 kB bytes.
/// * Basic edition: self option
/// * Evaluation edition: virtual option
/// * Commercial edition: self and virtual options
/// * Viewer edition: virtual option
///
/// @note Recommended: USE_hV_SCREEN_VIRTUAL
/// @warning Issues with virtual function on arm-none-eabi-g++ 4.9.3: use USE_hV_SCREEN_SELF instead.
///
/// @{
/// @note Commercial edition only
/// @}

///
/// @name 7- Set touch mode
/// @details Only two screens are ready for touch
/// * Basic edition: iTC 2.71 BW and iTC 3.70 BW
/// * Evaluation edition: iTC 2.71 BW and iTC 3.70 BW
/// * Commercial edition: iTC 2.71 BW and iTC 3.70 BW
/// * Viewer edition: iTC 2.71 BW and iTC 3.70 BW
///
/// @note Touch uses I2C and polling over interrupt
///
/// @{
/// @note Commercial edition only
/// @}

///
/// @name 8- Set haptic feedback mode
/// * Basic edition: no haptic feedback
/// * Evaluation edition: ERM or LRA
/// * Commercial edition: ERM or LRA
/// * Viewer edition: no haptic feedback
///
/// @{
/// @note Commercial edition only
/// @}

///
/// @name 9- Set GPIO expander mode
/// * Basic edition: no expander
/// * Evaluation edition: PCF8574 or PCA9536
/// * Commercial edition: PCF8574 or PCA9536
/// * Viewer edition: no expander
///
/// @{
/// @note Commercial edition only
/// @}

///
/// @name 10- Set string mode
/// * Basic edition: String object
/// * Evaluation edition: char array
/// * Commercial edition: String object or char array
/// * Viewer edition: char array
///
/// @note Corresponding type defined at hV_List_Types.h
///
/// @{
#define USE_STRING_OBJECT 1

#define STRING_MODE USE_STRING_OBJECT
/// @}

///
/// @name 11- Storage mode
/// * Basic edition: none
/// * Evaluation edition: none
/// * Commercial edition: option
/// * Viewer edition: option
///
/// @{
/// @note Advanced and Viewer editions only
/// @}

///
/// @name 12- Debug options
/// * Basic edition: none
/// * Evaluation edition: all
/// * Commercial edition: option
/// * Viewer edition: option
///
/// @{
/// @note Advanced and Viewer editions only
/// @}

///
/// @name 13- EXT boards
/// * Basic edition: EXT3 and EXT4
/// * Evaluation edition: EXT3
/// * Commercial edition: EXT3
/// * Viewer edition: EXT3
///
/// @note Corresponding boards defined at hV_List_Boards.h
/// @deprecated Check pins_t.scope instead (10.0.0)
/// @see hV_List_Boards.h
///

#endif // hV_LIST_OPTIONS_RELEASE

