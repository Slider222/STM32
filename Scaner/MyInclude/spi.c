// STM32F103 SPI1

// PB12  - (OUT)	SPI1_NSS
// PB13 - (OUT)	SPI1_SCK
// PB14  - (IN)	SPI1_MISO (Master In)
// PB15  - (OUT)	SPI1_MOSI (Master Out)

#define CS_LOW (GPIOB->BSRR = GPIO_BSRR_BR2)
#define CS_HI  (GPIOB->BSRR = GPIO_BSRR_BS2)

#define RST_LOW (GPIOA->BSRR = GPIO_BSRR_BR14)
#define RST_HI  (GPIOA->BSRR = GPIO_BSRR_BS14)

#define A0_LOW (GPIOA->BSRR = GPIO_BSRR_BR15)
#define A0_HI  (GPIOA->BSRR = GPIO_BSRR_BS15)

//#define SCLK_LOW (GPIOA->BSRR = GPIO_BSRR_BR5)
//#define SCLK_HI  (GPIOA->BSRR = GPIO_BSRR_BS5)

//#define MOSI_LOW (GPIOA->BSRR = GPIO_BSRR_BR7)
//#define MOSI_HI  (GPIOA->BSRR = GPIO_BSRR_BS7)



#include "stm32f10x.h"
#include "spi.h"


void initSPI2(void) {
	//RCC->APB2ENR |= (RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN);
	//RCC->APB1ENR  |= RCC_APB1ENR_SPI2EN;                                                //РІРєР»СЋС‡РµРЅРёРµ С‚Р°РєС‚РёСЂРѕРІР°РЅРёСЏ SPI2 
	  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

//	// вывод управления NSS: выход двухтактный, общего назначения,50MHz
//	GPIOB->CRL   |=  GPIO_CRH_MODE12;
//	GPIOB->CRL   &= ~GPIO_CRH_CNF12;
//	GPIOB->BSRR   =  GPIO_BSRR_BS12;

	// вывод SCK: выход двухтактный, альтернативная функция, 50MHz
	GPIOA->CRL   |=  GPIO_CRL_MODE5;
	GPIOA->CRL   &= ~GPIO_CRL_CNF5_0;
	GPIOA->CRL   |=  GPIO_CRL_CNF5_1;

//	// вывод MISO: вход цифровой с подтягивающим резистором, подтяжка к плюсу
//	GPIOB->CRH   &= ~GPIO_CRH_MODE14;
//	GPIOB->CRH   &= ~GPIO_CRH_CNF14;
//	GPIOB->CRH   |=  GPIO_CRH_CNF14_1;
//	GPIOB->BSRR   =  GPIO_BSRR_BS14;

	// вывод MOSI: выход двухтактный, альтернативная функция, 50MHz
	GPIOA->CRL   |=  GPIO_CRL_MODE7;
	GPIOA->CRL   &= ~GPIO_CRL_CNF7_0;
	GPIOA->CRL   |=  GPIO_CRL_CNF7_1;

	// Настройка SPI1 (STM32F103)
	SPI1->CR2     = 0x0000;
    
	SPI1->CR1     = SPI_CR1_MSTR;	// Мастер
	SPI1->CR1    |= SPI_CR1_BR_0;	// Маленькуя скорость SPI Baud rate = Fpclk/256	(2,4,8,16,32,64,128,256)
	SPI1->CR1    |= SPI_CR1_SSM;	// Программный режим NSS
	SPI1->CR1    |= SPI_CR1_SSI;	// Аналогично состоянию, когда на входе NSS высокий уровень
	SPI1->CR1    |= SPI_CR1_SPE;	// Разрешить работу модуля SPI
	//SPI1->CR1 |= SPI_CR1_CPOL; 	    // Полярность тактового сигнала (CK to idle when 0)
	//SPI1->CR1 |= SPI_CR1_CPHA; 	    // Фаза тактового сигнала (|= SPI_CR1_CPHA - по второму фронту)
//	SPI1->CR1 |= SPI_CR1_DFF; 		// 16 бит данных
//	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;	// Младший бит (MSB) передается первым
//	SPI1->CR2 |= SPI_CR2_SSOE; 		// NSS - используется как выход управления slave select
}

uint8_t transferComm(uint8_t com) {
	while (!(SPI1->SR & SPI_SR_TXE));      				// убедиться, что предыдущая передача завершена (STM32F103)
	SPI1->DR = com;										// вывод в SPI1
	while (!(SPI1->SR & SPI_SR_RXNE));     				// ждем окончания обмена (STM32F103)
	return SPI1->DR;		         					// читаем принятые данные
}

void transerData(char data, uint8_t command) {
//	SPI2_NSS_ON();										// CS_Low
//	SPI2SendByte(address);
//	SPI2SendByte(value);
//	SPI2_NSS_OFF();										// CS_HIGH
	CS_LOW;
	if(command == 0){
	  A0_LOW;
	  transferComm(data);
	}
    else {
		A0_HI;
		transferComm(data);
	}
	CS_HI;
}

uint8_t SPI2_ReadReg(uint8_t address) {
	uint8_t	val;

	SPI2_NSS_ON();										// CS_Low
	//SPI2SendByte(address);
	//val = SPI2SendByte(0x00);
	SPI2_NSS_OFF();										// CS_HIGH
	return val;
}


//void transerData(char data, uint8_t command){
//	CS_LOW;
//	if(command == 0){
//	  A0_LOW;
//	  transferComm(data);
//	}
//    else {
//		A0_HI;
//		transferComm(data);
//	}
//	CS_HI;	
//}

//void transferComm(uint8_t com){	
//	SCLK_LOW;
//	for (uint8_t i = 0; i < 8; i++){
//		SCLK_LOW;
//		if (com & 0x80){
//			MOSI_HI;
//		} 
//		else {
//			MOSI_LOW;
//		}
//	    SCLK_HI;
//		com = (com << 1);
//	}
//}	

void lcdInit(void){
	CS_LOW;	
	A0_LOW;
	//SCLK_LOW;
	//MOSI_LOW;
	RST_LOW;
	Delay_mks(50);
	RST_HI;
	Delay_mks(50);
	
   transferComm(0xe2); /*(14)Reset*/
   Delay_mks(10);
   transferComm(0xe2); /*(14)Reset*/
   Delay_mks(10);
   transferComm(0x2c); /*(19)static indicator  on/off static indicator rehister set*/
   Delay_mks(10);
   transferComm(0x2e); /*(13)End*/
   Delay_mks(10);
   transferComm(0x2f); /*???*/
   Delay_mks(10);
   transferComm(0x23); 
   transferComm(0x81); /*Точная настойка контрасности*/
   transferComm(0x3f); /*Точная настройка контрастности значение может быть установлено в диапазоне 0x00 ~ 0x3f*/
   transferComm(0xa2); /*1/9 отношение сдвига (смещения)*/
   transferComm(0xc8); /*Линия сканирования последовательности: сверху вниз*/
   transferComm(0xa0); /*Колонка сканирования порядке: слева направо*/
   transferComm(0x60); /*Линия старта: начало первой строки*/
   transferComm(0xaf); /*Отображение дисплея*///(0x2c); /*(19)static indicator  on/off static indicator rehister set*/
   Delay_mks(10);
   transferComm(0x2e); /*(13)End*/
   Delay_mks(10);
   transferComm(0x2f); /*???*/
   Delay_mks(10);
   transferComm(0x23);

//	transerData(0xa2,LCD_COMMAND); //lcd bias select 1/9 BIAS
//	transerData(0xa1,LCD_COMMAND); //ADC select,REVERSE 127-->0(a0,a1)
//	transerData(0xc0,LCD_COMMAND); //com select,NORMAL 0-->63(c8,c0)
//	transerData(0x26,LCD_COMMAND); //RESISTOR RATIO
//	transerData(0x81,LCD_COMMAND); //ELECTRONIC VOLUME mode setting 100B ?????
//	transerData(0x10,LCD_COMMAND); //Set reference voltagel register ?????
//	transerData(0x2f,LCD_COMMAND); //power control(VB,VR,VF=1,1,1)
//	Delay_ms(50);
//	transerData(0xaf,LCD_COMMAND); //set display on
//	transerData(0xf8,LCD_COMMAND); //set booster ratio
//	transerData(0x00,LCD_COMMAND); 
}

void LCDSetXY(uint8_t x, uint8_t y)
{
transerData(0xB0|y,LCD_COMMAND);// Page(Row)
transerData(0x10|((x+4)>>4),LCD_COMMAND);// Column high
transerData((0x00|(x+4))&0x0f,LCD_COMMAND);// Column low
}

void LCDcls(void)
{
uint32_t i,n;

for(i=0;i<9;i++)
{
LCDSetXY(0,i);

for(n=0;n<128;n++)
{
transerData(0x00,LCD_DATA);
}
}

}

