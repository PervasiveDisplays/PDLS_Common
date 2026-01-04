///
/// @file Driver_EPD_Virtual.h
/// @brief Generic driver class library - Basic edition
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

// SDK and configuration
#include "PDLS_Common.h"

#if (PDLS_COMMON_RELEASE < 1000)
#error Required PDLS_COMMON_RELEASE 1000
#endif // PDLS_COMMON_RELEASE

#ifndef DRIVER_EPD_VIRTUAL_RELEASE
///
/// @brief Library release number
///
#define DRIVER_EPD_VIRTUAL_RELEASE 1000

// Board
#include "hV_Board.h"

#if (hV_BOARD_RELEASE < 1000)
#error Required hV_BOARD_RELEASE 1000
#endif // hV_BOARD_RELEASE

// Utilities
#include "hV_Utilities.h"

#if (hV_UTILITIES_RELEASE < 1000)
#error Required hV_UTILITIES_RELEASE 1000
#endif // hV_UTILITIES_RELEASE

///
/// @brief Generic driver class
/// @details This class provides the functions for the drivers
///
class Driver_EPD_Virtual: public hV_Board
{
    friend class Screen_EPD;

  public:

    ///
    /// @brief Constructor
    ///
    Driver_EPD_Virtual() = default;

    ///
    /// @brief Constructor
    /// @param eScreen_EPD
    /// @param board
    ///
    Driver_EPD_Virtual(eScreen_EPD_t eScreen_EPD, pins_t board);

    ///
    /// @brief Destructor
    ///
    ~Driver_EPD_Virtual() = default;

    ///
    /// @brief Initialisation
    /// @warning Definition for this method is compulsory.
    ///
    virtual void begin();

    ///
    /// @brief Driver reference
    ///
    /// @return STRING_CONST_TYPE scope and release number
    ///
    virtual STRING_CONST_TYPE reference();

    ///
    /// @brief Set temperature in Celsius
    /// @details Set the temperature for update
    /// @param temperatureC temperature in °C, default = 25 °C
    /// @note Refer to data-sheets for authorised operating temperatures
    ///
    void setTemperatureC(int8_t temperatureC = 25);

    ///
    /// @brief Set temperature in Fahrenheit
    /// @details Set the temperature for update
    /// @param temperatureF temperature in °F, default = 77 °F = 25 °C
    /// @note Refer to data-sheets for authorised operating temperatures
    ///
    void setTemperatureF(int16_t temperatureF = 77);

    ///
    /// @brief Normal update
    /// @details Scope
    /// * Normal BW small and medium screens
    /// * BWRY small and medium screens, with BWRY colours
    /// * Fast BW small and medium screens, with embedded fast update
    /// * Wide BW small and medium screens, with wide temperature and embedded fast update
    ///
    /// @param frame next image
    /// @param sizeFrame size of the frame
    ///
    virtual void updateNormal(FRAMEBUFFER_CONST_TYPE frame,
                              uint32_t sizeFrame);

    ///
    /// @brief Normal update
    /// @details Scope
    /// * Normal BW large screens
    /// * Normal BWR small and medium screens
    /// @param frame1 next image, black
    /// @param frame2 next image, red
    ///
    /// * Fast BW large screens, with wide temperature and embedded fast update
    /// * Wide BW large screens, with wide temperature and embedded fast update
    /// @param frame1 next image, black, master
    /// @param frame2 next image, black, slave
    ///
    /// @param sizeFrame size of the frame
    ///
    virtual void updateNormal(FRAMEBUFFER_CONST_TYPE frame1, FRAMEBUFFER_CONST_TYPE frame2,
                              uint32_t sizeFrame);

    ///
    /// @brief Normal update
    /// @details Scope
    /// * Normal BWR large screens
    /// @param frameM1 next image, black, master
    /// @param frameM2 next image, red, master
    /// @param frameS1 next image, black, slave
    /// @param frameS2 next image, red, slave
    /// @param sizeFrame size of the frame
    ///
    virtual void updateNormal(FRAMEBUFFER_CONST_TYPE frameM1, FRAMEBUFFER_CONST_TYPE frameM2,
                              FRAMEBUFFER_CONST_TYPE frameS1, FRAMEBUFFER_CONST_TYPE frameS2,
                              uint32_t sizeFrame);

    ///
    /// @brief Fast update
    /// @details Scope
    /// * Fast BW small and medium screens, with embedded fast update
    /// * Wide BW small and medium screens, with wide temperature and embedded fast update
    /// @param frame1 next image
    /// @param frame2 previous image
    /// @param sizeFrame size of the frame
    ///
    virtual void updateFast(FRAMEBUFFER_CONST_TYPE frame1, FRAMEBUFFER_CONST_TYPE frame2,
                            uint32_t sizeFrame);

    ///
    /// @brief Fast update
    /// @details Scope
    /// * Fast BW large screens, with embedded fast update
    /// * Wide BW large screens, with wide temperature and embedded fast update
    /// @param frameM1 next image, master
    /// @param frameM2 previous image, master
    /// @param frameS1 next image, slave
    /// @param frameS2 previous image, slave
    /// @param sizeFrame size of the frame
    ///
    virtual void updateFast(FRAMEBUFFER_CONST_TYPE frameM1, FRAMEBUFFER_CONST_TYPE frameM2,
                            FRAMEBUFFER_CONST_TYPE frameS1, FRAMEBUFFER_CONST_TYPE frameS2,
                            uint32_t sizeFrame);

  protected:

    eScreen_EPD_t u_eScreen_EPD;
    int8_t u_temperature = 25;
    // uint8_t u_suspendMode = POWER_MODE_AUTO;
    // uint8_t u_suspendScope = POWER_SCOPE_GPIO_ONLY;
    bool u_flagOTP = false; // true = OTP read
    uint16_t d_COG; // Identifier with film and family

    //
    // === Touch section
    //
    virtual void d_getRawTouch(touch_t & touch);
    virtual bool d_getInterruptTouch();
    //
    // === End of Touch section
    //

  private:
    // virtual void d_beginTouch();

    // void COG_reset();
    // void COG_getDataOTP();
    // void COG_initial();
    // void COG_sendImageDataNormal();
    // void COG_sendParameters();
    // void COG_startDCDC();
    // void COG_update();
    // void COG_stopDCDC();
};

#endif // DRIVER_EPD_VIRTUAL_RELEASE
