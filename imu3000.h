#ifndef __IMU3000_H__
#define __IMU3000_H__

#include "main.h"

// Register Adresses
#define WHO_AM_I        0x00
#define X_OFFS_USRH     0x0C
#define X_OFFS_USRL     0x0D
#define Y_OFFS_USRH     0x0E
#define Y_OFFS_USRL     0x0F
#define Z_OFFS_USRH     0x10
#define Z_OFFS_USRL     0x11
#define FIFO_EN         0x12
#define AUX_VDDIO       0x13
#define AUX_SLV_ADDR    0x14
#define AUX_SMPLRT_DIV  0x15
#define DLPF_FS         0x16
#define INT_CFG         0x17
#define AUX_BURST_ADDR  0x18
#define INT_STATUS      0x1A
#define TEMP_OUT_H      0x1B
#define TEMP_OUT_L      0x1C
#define GYRO_XOUT_H     0x1D
#define GYRO_XOUT_L     0x1E
#define GYRO_YOUT_H     0x1F
#define GYRO_YOUT_L     0x20
#define GYRO_ZOUT_H     0x21
#define GYRO_ZOUT_L     0x22
#define AUX_XOUT_H      0x23
#define AUX_XOUT_L      0x24
#define AUX_YOUT_H      0x25
#define AUX_YOUT_L      0x26
#define AUX_ZOUT_H      0x27
#define AUX_ZOUT_L      0x28
#define FIFO_COUNTH     0x3A
#define FIFO_COUNTL     0x3B
#define FIFO_R          0x3C
#define USER_CTRL       0x3D
#define PWR_MGM         0x3E

// 16 Bit registers
#define X_OFFS      X_OFFS_USRH
#define Y_OFFS      Y_OFFS_USRH
#define Z_OFFS      Z_OFFS_USRH
#define TEMP_OUT    TEMP_OUT_H
#define GYRO_XOUT   GYRO_XOUT_H
#define GYRO_YOUT   GYRO_YOUT_H
#define GYRO_ZOUT   GYRO_ZOUT_H
#define AUX_XOUT    AUX_XOUT_H
#define AUX_YOUT    AUX_YOUT_H
#define AUX_ZOUT    AUX_ZOUT_H
#define FIFO_COUNT  FIFO_COUNTH

// Masks and Values by register
// WHO_AM_I
#define ID        0b01111110

// FIFO_EN
#define TEMP_OUT_EN    0b10000000
#define GYRO_XOUT_EN   0b01000000
#define GYRO_YOUT_EN   0b00100000
#define GYRO_ZOUT_EN   0b00010000
#define AUX_XOUT_EN    0b00001000
#define AUX_YOUT_EN    0b00000100
#define AUX_ZOUT_EN    0b00000010
#define FIFO_FOOTER_EN 0b00000001

// AUX_VDDIO
#define AUX_VDDIO_BIT 0b00000100

// AUX_SLV_ADDR
#define CLKOUT_EN     0b10000000
#define AUX_ID        0b01111111

// AUX_SMPLRT_DIV
#define SMPLRT_DIV    0b01111111

// DLPF_FS
#define FS_SEL        0b00011000
#define FS_SEL_250    0b00000000
#define FS_SEL_500    0b00001000
#define FS_SEL_1000   0b00010000
#define FS_SEL_2000   0b00011000
#define DLPF_CFG      0b00000111
#define DLPF_CFG_256  0b00000000
#define DLPF_CFG_188  0b00000001
#define DLPF_CFG_98   0b00000010
#define DLPF_CFG_42   0b00000011
#define DLPF_CFG_20   0b00000100
#define DLPF_CFG_10   0b00000101
#define DLPF_CFG_5    0b00000110

// INT_CFG
#define ACTL              0b10000000
#define OPEN              0b01000000
#define LATCH_INT_EN      0b00100000
#define INT_ANYRD_2CLEAR  0b00010000
#define I2C_MST_ERR_EN    0b00001000
#define IMU_RDY_EN        0b00000100
#define DMP_DONE_EN       0b00000010
#define RAW_RDY_EN        0b00000001

// INT_STATUS
#define FIFO_FULL         0b10000000
#define I2C_MST_ERR       0b00001000
#define IMU_RDY           0b00000100
#define DMP_DONE          0b00000010
#define RAW_DATA_RDY      0b00000001

// USER_CTRL
#define DMP_EN            0b10000000
#define FIFO_EN_BIT       0b01000000
#define AUX_IF_EN         0b00100000
#define AUX_IF_RST        0b00001000
#define DMP_RST           0b00000100
#define FIFO_RST          0b00000010
#define GYRO_RST          0b00000001

// PWR_MGM
#define H_RESET           0b10000000
#define SLEEP             0b01000000
#define STBY_XG           0b00100000
#define STBY_YG           0b00010000
#define STBY_ZG           0b00001000
#define CLK_SEL           0b00000111

// Low Level Functions
uint8_t WriteReg(uint8_t reg, uint8_t value);
uint8_t ReadReg(uint8_t reg, uint8_t* buffer);
uint8_t WriteReg16(uint8_t reg, uint16_t value);
uint8_t ReadReg16(uint8_t reg, uint16_t* buffer);

#endif // __IMU3000_H__
