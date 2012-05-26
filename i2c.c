#include "i2c.h"
#include "TWI_Master.h"

uint8_t I2C_Write(uint8_t reg, uint8_t value)
{
  if (TWIM_Start(IMU3000_addr, TWIM_WRITE))
    if (TWIM_Write(reg))
      if (TWIM_Write(value))
      {
        TWIM_Stop();
        return 1;
      }
  TWIM_Stop();
  return 0;
}

uint8_t I2C_Read(uint8_t reg, uint8_t* buffer)
{
  if (TWIM_Start(IMU3000_addr, TWIM_WRITE))
    if (TWIM_Write(reg))
      if (TWIM_Start(IMU3000_addr, TWIM_READ))
      {
        *buffer = TWIM_ReadNack();
        TWIM_Stop();
        return 1;
      }
  TWIM_Stop();
  return 0;
}
