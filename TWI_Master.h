#ifndef _TWIM
#define _TWIM

#define TWIM_READ    1
#define TWIM_WRITE   0

uint8_t	TWIM_Init (uint32_t TWI_Bitrate);
uint8_t TWIM_Start (uint8_t address, uint8_t TWIM_Type);
void	TWIM_Stop (void);
uint8_t	TWIM_Write (uint8_t byte);
uint8_t	TWIM_ReadAck (void);
uint8_t	TWIM_ReadNack (void);

#endif
