/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef BOARD_I2C_DEVICES__H_
#define BOARD_I2C_DEVICES__H_

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "hal_data.h"


uint8_t wrSWReg16_8(int regID, int regDat);
uint8_t rdSWReg16_8(uint16_t regID, uint8_t* regDat);
fsp_err_t board_i2c_read_reg8(uint8_t slave_addr, uint8_t reg, uint8_t *p_data, uint32_t len);

#endif /* BOARD_I2C_DEVICES__H_ */
