// STM32F103 SPI1

// PB12  - (OUT)	SPI1_NSS
// PB13  - (OUT)	SPI1_SCK
// PB14  - (IN)	SPI1_MISO (Master In)
// PB15  - (OUT)	SPI1_MOSI (Master Out)

#define 	SPI_I2S_FLAG_BSY	((uint16_t)0x0080)
#define 	SPI2_NSS_ON()		GPIOB->BSRR = GPIO_BSRR_BR12
#define 	SPI2_NSS_OFF()		GPIOB->BSRR = GPIO_BSRR_BS12
#define LCD_DATA 1
#define LCD_COMMAND 0

#include "funct.h"

extern void initSPI2(void);
extern uint8_t SPI2SendByte(uint8_t data);
extern void SPI2_WriteReg(uint8_t address, uint8_t value);
extern uint8_t SPI2_ReadReg(uint8_t address);

extern void initSPIManual(void);
extern void lcdInit(void);
extern void transerData(char data, uint8_t command);
uint8_t transferComm(uint8_t com);
extern void LCDSetXY(uint8_t x, uint8_t y);
extern void LCDcls(void);
