

#include "main.h"
#include "usart.h"
#include "avr/interrupt.h"
#include "TWI_Master.h"
#include <stdio.h>
#include "i2c.h"
#include "imu3000.h"

int main(void)
{
  char buffer[40];
  uint8_t rd;
  uint8_t status;
  int16_t gx;
  int16_t gy;
  int16_t gz;
	USART0_Init();

	sei();

	DDRB |= (1<<PORTB5);
  TWIM_Init(400000);
  USART0_puts("Init\r\n");
  I2C_Read(0x16, &rd);
  I2C_Write(0x16, rd | 0b00000000);

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

    if (ReadReg16(GYRO_XOUT, &gx))
      if (ReadReg16(GYRO_YOUT, &gy))
        if (ReadReg16(GYRO_ZOUT, &gz))
        {
          sprintf(buffer, "%6i, %6i, %6i\r\n", (int16_t)gx, gy, gz);
          USART0_puts(buffer);
        }

		PORTB |= (1<<PORTB5);
		_delay_ms(30);
		PORTB &= ~(1<<PORTB5);
		_delay_ms(30);

	}

}





