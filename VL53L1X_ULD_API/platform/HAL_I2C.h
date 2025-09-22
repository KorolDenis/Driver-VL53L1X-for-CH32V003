/*
 * HAL_I2C.h
 *
 *  Created on: Nov 25, 2024
 *      Author: Δενθρ
 */

#ifndef VL53L1X_ULD_API_PLATFORM_HAL_I2C_H_
#define VL53L1X_ULD_API_PLATFORM_HAL_I2C_H_

#include "ch32v00x.h"

#define MEM_ADDR_8B      0
#define MEM_ADDR_16B     1

#define I2C_SUCCES       0
#define I2C_BUSY         1
#define I2C_START_ERROR  2
#define I2C_ADRR_NAC     3
#define I2C_DATA_ERROR   4

uint8_t I2C_Write_Mem(I2C_TypeDef *i2cHandle,uint8_t i2cAddr,uint16_t addr,uint8_t *buff,uint16_t size,uint32_t timeout,uint8_t addr_size);
uint8_t I2C_Read_Mem(I2C_TypeDef *i2cHandle,uint8_t i2cAddr,uint16_t addr,uint8_t *buff,uint16_t size,uint32_t timeout,uint8_t addr_size);
uint8_t HAL_I2C_Master_Transmit(I2C_TypeDef *i2cHandle,uint8_t i2cAddr,uint8_t *buff,uint16_t size,uint32_t timeout);
uint8_t HAL_I2C_Master_Receive(I2C_TypeDef *i2cHandle,uint8_t i2cAddr,uint8_t *buff,uint16_t size,uint32_t timeout);

#endif /* VL53L1X_ULD_API_PLATFORM_HAL_I2C_H_ */
