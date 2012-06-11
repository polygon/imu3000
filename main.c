

#include "main.h"
#include "usart.h"
#include "avr/interrupt.h"
#include "TWI_Master.h"
#include <stdio.h>
#include "i2c.h"
#include "imu3000.h"

//volatile uint8_t ind;

/*ISR(TIMER1_COMPA_vect)
{
  ind = 0;
}*/

int main(void)
{
  char buffer[40];
  uint8_t rd;
  uint8_t status;
  int16_t gx;
  int16_t gy;
  int16_t gz;
  int16_t ax, ay, az;
  int32_t offx, offy, offz;
  int32_t ang_x, ang_y, ang_z;
  double a_x, a_y, a_z;
	USART0_Init();

	sei();
	DDRB |= (1<<PORTB5);
  TWIM_Init(400000);
  USART0_puts("Init\r\n");
  I2C_SetAddress(IMU3000_addr);

  // Initialize Gyro
  WriteReg(PWR_MGM, 0x87);
  WriteReg(PWR_MGM, 0x01);
  WriteReg(SMPLRT_DIV, 10);
  WriteReg(DLPF_FS, FS_SEL_2000 | DLPF_CFG_42);
  ReadReg16(X_OFFS, &gx);
  ReadReg16(Y_OFFS, &gy);
  ReadReg16(Z_OFFS, &gz);
//  sprintf(buffer, "X: %i, Y: %i, Z: %i\r\n", gx, gy, gz);
//  USART0_puts(buffer);
  WriteReg16(X_OFFS, (int16_t)110);
  WriteReg16(Y_OFFS, (int16_t)0);
  WriteReg16(Z_OFFS, (int16_t)88);

  // Initialize Auxilliary Accelerometer

  WriteReg(AUX_SLV_ADDR, ADXL345_addr);
  WriteReg(AUX_BURST_ADDR, 0x32);
  WriteReg(USER_CTRL, AUX_IF_RST);

  I2C_SetAddress(ADXL345_addr);
  WriteReg(0x2D, 8);
  WriteReg(0x31, 11);

  I2C_SetAddress(IMU3000_addr);
  WriteReg(USER_CTRL, AUX_IF_RST | AUX_IF_EN);

  ang_x = ang_y = ang_z = 0;
//  TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
//  TIMSK1 |= (1 << OCIE1A);
//  OCR1A = 2500;
  uint16_t i;
  int16_t test1; uint16_t test2;
  uint8_t rdy;

	while(1)
	{
/*    if (!TWIM_Start(0b1101000, TWIM_WRITE))
    {
      TWIM_Stop();
      USART0_puts("Error\r\n");
    }
    else
    {
      TWIM_Write(0x1D);
      TWIM_Start(0b1101000, TWIM_READ);
      sprintf(buffer, "%i\r\n", (int8_t)TWIM_ReadNack());
      TWIM_Stop();
      USART0_puts(buffer);
    }*/
    /*if (status = I2C_Read(0x1D, &rd))
      sprintf(buffer, "OK: %i, %i\r\n", (int8_t)rd, status);
    else
      sprintf(buffer, "Error!\r\n");
    USART0_puts(buffer);*/

    ReadReg16(GYRO_XOUT, &gx);
    ReadReg16(GYRO_YOUT, &gy);
    ReadReg16(GYRO_ZOUT, &gz);
    ReadReg16Inv(AUX_XOUT, &ax);
    ReadReg16Inv(AUX_YOUT, &ay);
    ReadReg16Inv(AUX_ZOUT, &az);

    offx += gx; offy += gy; offz += gz;

    ReadReg(INT_STATUS, &rdy);
    WriteReg(INT_STATUS, rdy &= RAW_DATA_RDY^0xff);

    i++;
    if (i == 1000)
    {
      sprintf(buffer, "OFFX: %d, OFFY: %d, OFFZ: %d\r\n", (int16_t)(offx / 1000), (int16_t)(offy / 1000), (int16_t)(offz / 1000));
 //     USART0_puts(buffer);
      i = 0;
      offx = 0; offy = 0; offz = 0;
    }
//    sprintf(buffer, "%d\r\n", (((int16_t)-4) >> 1));
//    USART0_puts(buffer);

    ang_x += (int32_t)gx; ang_y += (int32_t)gy; ang_z += (int32_t)gz;
    sprintf(buffer, "%d, %d, %d, %d, %d, %d\r\n", gx, gy, gz, ax, ay, az);
    USART0_puts(buffer);
    a_x = (2000.0 * (double)ang_x) / (3276800.0);
    a_y = (2000.0 * (double)ang_y) / (3276800.0);
    a_z = (2000.0 * (double)ang_z) / (3276800.0);
//    sprintf(buffer, "X: %d, Y: %d, Z: %d\r\n", (int16_t)a_x, (int16_t)a_y, (int16_t)a_z);
//    USART0_puts(buffer);
//    ind = 1;
    
//    while (ind) {}
    
    do
    {
      ReadReg(INT_STATUS, &rdy);
      rdy = rdy & RAW_DATA_RDY;
    }
    while (!rdy);
	}

}





