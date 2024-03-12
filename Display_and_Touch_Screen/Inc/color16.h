/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file color16.h
 * @brief This file contains API for Color 16 Click Driver.
 */

#ifndef COLOR16_H
#define COLOR16_H



#include "usbd_cdc_if.h"
#include "SSD1963.h"
#include "STMPE610.h"
#include "GUI.h"
#include "LCDConf.h"
#include <stdint.h>
#include <stdio.h>
#include "stm32_hal_legacy.h"

/*!
 * @addtogroup color16 Color 16 Click Driver
 * @brief API for configuring and manipulating Color 16 Click driver.
 * @{
 */

/**
 * @defgroup color16_reg Color 16 Registers List
 * @brief List of registers of Color 16 Click driver.
 */

/**
 * @addtogroup color16_reg
 * @{
 */

/**
 * @brief Color 16 register list.
 * @details Specified register list of Color 16 Click driver.
 */
#define COLOR16_REG_AUXID                   0x58
#define COLOR16_REG_REVID                   0x59
#define COLOR16_REG_ID                      0x5A
#define COLOR16_REG_CFG_12                  0x66
#define COLOR16_REG_ENABLE                  0x80
#define COLOR16_REG_ATIME                   0x81
#define COLOR16_REG_WTIME                   0x83
#define COLOR16_REG_SP_TH_L_LSB             0x84
#define COLOR16_REG_SP_TH_L_MSB             0x85
#define COLOR16_REG_SP_TH_H_LSB             0x86
#define COLOR16_REG_SP_TH_H_MSB             0x87
#define COLOR16_REG_STATUS                  0x93
#define COLOR16_REG_ASTATUS                 0x94
#define COLOR16_REG_DATA_0_L                0x95
#define COLOR16_REG_DATA_0_H                0x96
#define COLOR16_REG_DATA_1_L                0x97
#define COLOR16_REG_DATA_1_H                0x98
#define COLOR16_REG_DATA_2_L                0x99
#define COLOR16_REG_DATA_2_H                0x9A
#define COLOR16_REG_DATA_3_L                0x9B
#define COLOR16_REG_DATA_3_H                0x9C
#define COLOR16_REG_DATA_4_L                0x9D
#define COLOR16_REG_DATA_4_H                0x9E
#define COLOR16_REG_DATA_5_L                0x9F
#define COLOR16_REG_DATA_5_H                0xA0
#define COLOR16_REG_DATA_6_L                0xA1
#define COLOR16_REG_DATA_6_H                0xA2
#define COLOR16_REG_DATA_7_L                0xA3
#define COLOR16_REG_DATA_7_H                0xA4
#define COLOR16_REG_DATA_8_L                0xA5
#define COLOR16_REG_DATA_8_H                0xA6
#define COLOR16_REG_DATA_9_L                0xA7
#define COLOR16_REG_DATA_9_H                0xA8
#define COLOR16_REG_DATA_10_L               0xA9
#define COLOR16_REG_DATA_10_H               0xAA
#define COLOR16_REG_DATA_11_L               0xAB
#define COLOR16_REG_DATA_11_H               0xAC
#define COLOR16_REG_DATA_12_L               0xAD
#define COLOR16_REG_DATA_12_H               0xAE
#define COLOR16_REG_DATA_13_L               0xAF
#define COLOR16_REG_DATA_13_H               0xB0
#define COLOR16_REG_DATA_14_L               0xB1
#define COLOR16_REG_DATA_14_H               0xB2
#define COLOR16_REG_DATA_15_L               0xB3
#define COLOR16_REG_DATA_15_H               0xB4
#define COLOR16_REG_DATA_16_L               0xB5
#define COLOR16_REG_DATA_16_H               0xB6
#define COLOR16_REG_DATA_17_L               0xB7
#define COLOR16_REG_DATA_17_H               0xB8
#define COLOR16_REG_STATUS_2                0x90
#define COLOR16_REG_STATUS_3                0x91
#define COLOR16_REG_STATUS_5                0xBB
#define COLOR16_REG_STATUS_4                0xBC
#define COLOR16_REG_CFG_0                   0xBF
#define COLOR16_REG_CFG_1                   0xC6
#define COLOR16_REG_CFG_3                   0xC7
#define COLOR16_REG_CFG_6                   0xF5
#define COLOR16_REG_CFG_8                   0xC9
#define COLOR16_REG_CFG_9                   0xCA
#define COLOR16_REG_CFG_10                  0x65
#define COLOR16_REG_PERS                    0xCF
#define COLOR16_REG_GPIO                    0x6B
#define COLOR16_REG_ASTEP_LSB               0xD4
#define COLOR16_REG_ASTEP_MSB               0xD5
#define COLOR16_REG_CFG_20                  0xD6
#define COLOR16_REG_LED                     0xCD
#define COLOR16_REG_AGC_GAIN_MAX            0xD7
#define COLOR16_REG_AZ_CONFIG               0xDE
#define COLOR16_REG_FD_TIME_1               0xE0
#define COLOR16_REG_FD_TIME_2               0xE2
#define COLOR16_REG_FD_CFG_0                0xDF
#define COLOR16_REG_FD_STATUS               0xE3
#define COLOR16_REG_INTENAB                 0xF9
#define COLOR16_REG_CONTROL                 0xFA
#define COLOR16_REG_FIFO_MAP                0xFC
#define COLOR16_REG_FIFO_LVL                0xFD
#define COLOR16_REG_FDATA_L                 0xFE
#define COLOR16_REG_FDATA_H                 0xFF

/*! @} */ // color16_reg

/**
 * @defgroup color16_set Color 16 Registers Settings
 * @brief Settings for registers of Color 16 Click driver.
 */

/**
 * @addtogroup color16_set
 * @{
 */

/**
 * @brief Color 16 ENABLE register setting.
 * @details Specified setting for ENABLE register of Color 16 Click driver.
 */
#define COLOR16_ENABLE_FDEN                 0x40
#define COLOR16_ENABLE_SMUXEN               0x10
#define COLOR16_ENABLE_WEN                  0x08
#define COLOR16_ENABLE_SP_EN                0x02
#define COLOR16_ENABLE_PON                  0x01
#define COLOR16_ENABLE_POFF                 0x00

/**
 * @brief Color 16 CFG_0 register setting.
 * @details Specified setting for CFG_0 register of Color 16 Click driver.
 */
#define COLOR16_CFG_0_LOW_POWER             0x20
#define COLOR16_CFG_0_REG_BANK              0x10
#define COLOR16_CFG_0_WLONG                 0x04

/**
 * @brief Color 16 CFG_1 register setting.
 * @details Specified setting for CFG_1 register of Color 16 Click driver.
 */
#define COLOR16_CFG_1_AGAIN_0p5             0x00
#define COLOR16_CFG_1_AGAIN_1               0x01
#define COLOR16_CFG_1_AGAIN_2               0x02
#define COLOR16_CFG_1_AGAIN_4               0x03
#define COLOR16_CFG_1_AGAIN_8               0x04
#define COLOR16_CFG_1_AGAIN_16              0x05
#define COLOR16_CFG_1_AGAIN_32              0x06
#define COLOR16_CFG_1_AGAIN_64              0x07
#define COLOR16_CFG_1_AGAIN_128             0x08
#define COLOR16_CFG_1_AGAIN_256             0x09
#define COLOR16_CFG_1_AGAIN_512             0x0A
#define COLOR16_CFG_1_AGAIN_1024            0x0B
#define COLOR16_CFG_1_AGAIN_2048            0x0C
#define COLOR16_CFG_1_AGAIN_MASK            0x1F

/**
 * @brief Color 16 CFG_20 register setting.
 * @details Specified setting for CFG_20 register of Color 16 Click driver.
 */
#define COLOR16_CFG_20_FD_FIFO_8BIT         0x80
#define COLOR16_CFG_20_AUTO_SMUX_6CH        0x00
#define COLOR16_CFG_20_AUTO_SMUX_12CH       0x40
#define COLOR16_CFG_20_AUTO_SMUX_18CH       0x60
#define COLOR16_CFG_20_AUTO_SMUX_MASK       0x60

/**
 * @brief Color 16 CONTROL register setting.
 * @details Specified setting for CONTROL register of Color 16 Click driver.
 */
#define COLOR16_CONTROL_SW_RESET            0x08
#define COLOR16_CONTROL_SP_MAN_AZ           0x04
#define COLOR16_CONTROL_FIFO_CLR            0x02
#define COLOR16_CONTROL_CLEAR_SAI_ACT       0x01

/**
 * @brief Color 16 LED register setting.
 * @details Specified setting for LED register of Color 16 Click driver.
 */
#define COLOR16_LED_OFF                     0x00
#define COLOR16_LED_ON                      0x80
#define COLOR16_LED_DRIVE_CURR_MIN          4
#define COLOR16_LED_DRIVE_CURR_MAX          258
#define COLOR16_LED_DRIVE_CURR_STEP         2
#define COLOR16_LED_DRIVE_CURR_DEFAULT      8

/**
 * @brief Color 16 STATUS register setting.
 * @details Specified setting for STATUS register of Color 16 Click driver.
 */
#define COLOR16_STATUS_ASAT                 0x80
#define COLOR16_STATUS_AINT                 0x08
#define COLOR16_STATUS_FINT                 0x04
#define COLOR16_STATUS_SINT                 0x01

/**
 * @brief Color 16 ASTATUS register setting.
 * @details Specified setting for ASTATUS register of Color 16 Click driver.
 */
#define COLOR16_ASTATUS_ASAT                0x80
#define COLOR16_ASTATUS_AGAIN_MASK          0x0F

/**
 * @brief Color 16 STATUS_2 register setting.
 * @details Specified setting for STATUS_2 register of Color 16 Click driver.
 */
#define COLOR16_STATUS_2_AVALID             0x40
#define COLOR16_STATUS_2_ASAT_DIG           0x10
#define COLOR16_STATUS_2_ASAT_ANA           0x08
#define COLOR16_STATUS_2_FDSAT_ANA          0x02
#define COLOR16_STATUS_2_FDSAT_DIG          0x01

/**
 * @brief Color 16 device ID value.
 * @details Specified device ID value of Color 16 Click driver.
 */
#define COLOR16_DEVICE_ID                   0x81

/**
 * @brief Color 16 register bank access setting.
 * @details Specified setting for register bank access of Color 16 Click driver.
 */
#define COLOR16_ACCESS_REG_BANK_ABOVE_80H   0
#define COLOR16_ACCESS_REG_BANK_20H_7FH     1

/**
 * @brief Color 16 integration time setting.
 * @details Specified setting for integration time of Color 16 Click driver.
 */
#define COLOR16_SINGLE_STEP_MS              0.00278f
#define COLOR16_ATIME_MAX                   255
#define COLOR16_ASTEP_MAX                   65534
#define COLOR16_INTEGRATION_TIME_MAX        ( ( float ) ( COLOR16_ATIME_MAX + 1 ) * ( COLOR16_ASTEP_MAX + 1 ) * COLOR16_SINGLE_STEP_MS )
#define COLOR16_INTEGRATION_TIME_MIN        COLOR16_SINGLE_STEP_MS
#define COLOR16_INTEGRATION_TIME_DEFAULT    90.0f
#define COLOR16_WAIT_STEP_MS                2.78f
#define COLOR16_WTIME_MAX                   255
#define COLOR16_WAIT_TIME_MAX                ( ( float ) ( COLOR16_WTIME_MAX + 1 ) * COLOR16_WAIT_STEP_MS )
#define COLOR16_WAIT_TIME_MIN               COLOR16_WAIT_STEP_MS
#define COLOR16_WAIT_TIME_DEFAULT           100.0f

/**
 * @brief Color 16 device address setting.
 * @details Specified setting for device slave address selection of
 * Color 16 Click driver.
 */
#define COLOR16_DEVICE_ADDRESS              0x39

/*! @} */ // color16_set

/**
 * @defgroup color16_map Color 16 MikroBUS Map
 * @brief MikroBUS pin mapping of Color 16 Click driver.
 */

/**
 * @addtogroup color16_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of Color 16 Click to the selected MikroBUS.
 */
#define COLOR16_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.ldr = MIKROBUS( mikrobus, MIKROBUS_AN ); \
    cfg.int_pin = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // color16_map
/*! @} */ // color16

/**
 * @brief Color 16 Click data object.
 * @details Data object definition of Color 16 Click driver.
 */

typedef struct
{
    uint8_t status;
    uint8_t astatus;
    uint16_t ch_fz;
    uint16_t ch_fy;
    uint16_t ch_fxl;
    uint16_t ch_nir;
    uint16_t ch_2x_vis_1;
    uint16_t ch_fd_1;
    uint16_t ch_f2;
    uint16_t ch_f3;
    uint16_t ch_f4;
    uint16_t ch_f6;
    uint16_t ch_2x_vis_2;
    uint16_t ch_fd_2;
    uint16_t ch_f1;
    uint16_t ch_f5;
    uint16_t ch_f7;
    uint16_t ch_f8;
    uint16_t ch_2x_vis_3;
    uint16_t ch_fd_3;

} color16_data_t;

uint8_t COLOR16_init(I2C_HandleTypeDef i2c_handle);
void color16_read_register(uint8_t reg, uint8_t *data_out);
void color16_write_register(uint8_t reg, uint8_t data_in);
void color16_write_register_word(uint8_t reg, uint16_t data_in);
void color16_read_register_word(uint8_t reg, uint16_t *data_out);
void enable_register(void);
void measure_enable(void);
void color16_generic_read(uint8_t reg, uint8_t *data_out, uint8_t len);
void color16_set_reg_bank_access(uint8_t reg_bank);
void color16_set_integration_time_ms(float int_time_ms );
void color16_set_wait_time_ms(float wait_time_ms );
void color16_read_data (color16_data_t *data_out);
void color16_default_cfg (void);
void sp_th_configure (void);

#endif
