#include "imu3000.h"
#include "i2c.h"

uint8_t WriteReg(uint8_t reg, uint8_t value)
{
  return I2C_Write(reg, value);
}

uint8_t ReadReg(uint8_t reg, uint8_t* buffer)
{
  return I2C_Read(reg, buffer);
}

uint8_t WriteReg16(uint8_t reg, uint16_t value)
{
  if (I2C_Write(reg, (uint8_t)(value >> 8)))
    if (I2C_Write(reg, (uint8_t)(value & 0b11111111)))
      return 1;
  return 0;
}

uint8_t ReadReg16(uint8_t reg, uint16_t* buffer)
{
  uint8_t h, l;
  if (I2C_Read(reg, &h))
    if (I2C_Read(reg+1, &l))
    {
      *buffer = (((uint16_t)h) << 8) + (uint16_t)l;
      return 1;
    }
  return 0;
}
