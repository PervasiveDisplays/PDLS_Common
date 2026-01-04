///
/// @file hV_Utilities.h
/// @brief Utilities for Pervasive Displays Library Suite - Basic edition
///
/// @details Project Pervasive Displays Library Suite
/// @n Based on highView technology
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

// SDK
#include "hV_HAL_Peripherals.h"

#if (hV_HAL_PERIPHERALS_RELEASE < 1000)
#error Required hV_HAL_PERIPHERALS_RELEASE 1000
#endif // hV_HAL_PERIPHERALS_RELEASE

// Boards
#include "hV_List_Boards.h"

#if (hV_LIST_BOARDS_RELEASE < 1000)
#error Required hV_LIST_BOARDS_RELEASE 1000
#endif // hV_LIST_BOARDS_RELEASE

// Types
#include "hV_List_Types.h"

#if (hV_LIST_TYPES_RELEASE < 1000)
#error Required hV_LIST_TYPES_RELEASE 1000
#endif // hV_LIST_TYPES_RELEASE

// Constants
#include "hV_List_Constants.h"

#if (hV_LIST_CONSTANTS_RELEASE < 1000)
#error Required hV_LIST_CONSTANTS_RELEASE 1000
#endif // hV_LIST_CONSTANTS_RELEASE

#ifndef hV_UTILITIES_RELEASE
///
/// @brief Library release number
///
#define hV_UTILITIES_RELEASE 1000

///
/// @name Orientation constants
/// @{
///
#define ORIENTATION_PORTRAIT 6 ///< portrait or vertical, higher than large
#define ORIENTATION_LANDSCAPE 7 ///< landscape or horizontal, larger than high
/// @}
///

///
/// @brief Structure for touch
///
struct touch_t
{
    uint16_t x; ///< x coordinate
    uint16_t y; ///< y coordinate
    uint16_t z; ///< z coordinate = pressure
    uint16_t t; ///< event if available, otherwise 0
};

///
/// @name Text format functions
/// @brief Utilities to format float, 64-bit unsigned integer, hexadecimal and period into string
/// @{

///
/// @brief UTF-8 to ISO-8859-1 Converter
/// @param s UTF-8 string, input
/// @return ISO-8859-1 string, output
///
/// @deprecated No longer required. Use UTF-8 instead with gText(), Graphics and GUI elements (10.0.0)
///
/// @see The Unicode Consortium. The Unicode Standard, Version 6.2.0,
/// (Mountain View, CA: The Unicode Consortium, 2012. ISBN 978-1-936213-07-8)
/// http://www.unicode.org/versions/Unicode6.2.0/
///
STRING_TYPE utf2iso(STRING_TYPE s);

///
/// @brief UTF-8 to UTF-16 converter
/// @param[in] inUTF8 UTF-8 string, input
/// @param[out] outUTF16 UTF-16 string, output
/// @param[in] limit maximum number of characters converted, `0` = no check
/// @return number of UTF-16 characters converted
///
/// @see
/// * The Unicode Consortium. The Unicode Standard, Version 6.2.0,
/// (Mountain View, CA: The Unicode Consortium, 2012. ISBN 978-1-936213-07-8)
/// http://www.unicode.org/versions/Unicode6.2.0/
/// * https://stackoverflow.com/a/148766/1190049
///
uint16_t utf8to16(STRING_CONST_TYPE inUTF8, STRING16_BYREF_TYPE outUTF16, uint8_t limit = 0);

///
/// @brief Format string or char array
/// @details Based on vsprint
/// @param format format with standard codes
/// @param ... list of values
/// @return string or character array with values formatted
/// @note All inputs are const char *, use c_str() on Arduino strings
/// @see http://www.cplusplus.com/reference/cstdio/printf/?kw=printf for codes
///
STRING_TYPE formatString(const char * format, ...);

//
// --- Advanced edition
//

//
// --- End of Advanced edition
//

/// @}

///
/// @name Miscellaneous functions
/// @brief Swap and miscellaneous functions
///
/// @{
///
/// @brief Check value in range
/// @param value value to check
/// @param valueMin range minimum
/// @param valueMax range maximum
/// @return value within range
/// @note Assuming valueMin < valueMax
/// * if value < valueMin, return valueMin
/// * if value > valueMax, return valueMax
/// Otherwise, if valueMin > valueMax, valueMin and valueMax are swapped
///
template <typename T>
T checkRange(T value, T valueMin, T valueMax)
{
    T localMin = (valueMin < valueMax) ? valueMin : valueMax;
    T localMax = (valueMin > valueMax) ? valueMin : valueMax;

    // return min(max(localMin, value), localMax);
    T result = value;

    result = (localMin > result) ? localMin : result;
    result = (localMax < result) ? localMax : result;

    return result;
};

///
/// @brief Grid class, x- and y-axis
///
class GridXY
{
  public:
    ///
    /// Constructor
    ///
    GridXY();

    ///
    /// @brief Define the grid
    /// @param x0 origin coordinate, x-axis
    /// @param y0 origin coordinate, y-axis
    /// @param dx size of the grid, x-axis
    /// @param dy size of the grid, y-axis
    /// @param nX number of divisions in x-axis
    /// @param nY number of divisions in y-axis
    /// @param flagAdjust adjust origin, default false
    ///
    void define(uint16_t x0, uint16_t y0, uint16_t dx, uint16_t dy, uint16_t nX, uint16_t nY, bool flagAdjust = false);

    ///
    /// @brief Get size for number of divisions, x-axis
    /// @param i number of divisions, 0..n
    /// @return pixels of the divisions
    /// @note No check on i <= n
    ///
    uint16_t dX(uint16_t i = 1);

    ///
    /// @brief Get size for number of divisions, y-axis
    /// @param i number of divisions, 0..n
    /// @return pixels of the divisions
    /// @note No check on i <= n
    ///
    uint16_t dY(uint16_t i = 1);

    ///
    /// @brief Get coordinate at division, x-axis
    /// @param i index of the division, 0..n-1
    /// @return coordinate of the start of the division
    /// @note No check on i < n
    ///
    uint16_t x(uint16_t i = 0);

    ///
    /// @brief Get coordinate at division, y-axis
    /// @param i index of the division, 0..n-1
    /// @return coordinate of the start of the division
    /// @note No check on i < n
    ///
    uint16_t y(uint16_t i = 0);

  private:
    uint16_t _x0, _y0; ///< origin coordinates
    uint16_t _dx, _dy; ///< size of the division
};

//
// --- Advanced edition
//

/// @}
//
// --- End of Advanced edition
//

#endif // hV_UTILITIES_RELEASE
