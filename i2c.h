#ifndef __I2C_H__
#define __I2C_H__

#include "main.h"

#define IMU3000_addr 0b1101000
#define ADXL345_addr 0b1010011

uint8_t I2C_Write(uint8_t reg, uint8_t value);
uint8_t I2C_Read(uint8_t reg, uint8_t* buffer);
void I2C_SetAddress(uint8_t address);

#endif // __I2C_H__
