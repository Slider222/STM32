#ifndef displ_H_
#define displ_H_



#include "Funct.h"


#define set_CS (GPIOB->BSRR |= GPIO_BSRR_BS0)
#define set_RS (GPIOB->BSRR |= GPIO_BSRR_BS1)
#define set_WR (GPIOA->BSRR |= GPIO_BSRR_BS8)
#define set_RD (GPIOB->BSRR |= GPIO_BSRR_BS7)
#define set_LED (GPIOB->BSRR |= GPIO_BSRR_BS6)
#define set_RES (GPIOB->BSRR |= GPIO_BSRR_BS5)
#define set_PC13 (GPIOC->BSRR |= GPIO_BSRR_BS13)
#define set_PC12 (GPIOC->BSRR |= GPIO_BSRR_BS12)

#define reset_CS (GPIOB->BSRR |= GPIO_BSRR_BR0)
#define reset_RS (GPIOB->BSRR |= GPIO_BSRR_BR1)
#define reset_WR (GPIOA->BSRR |= GPIO_BSRR_BR8)
#define reset_RD (GPIOB->BSRR |= GPIO_BSRR_BR7)
#define reset_LED (GPIOB->BSRR |= GPIO_BSRR_BR6)
#define reset_RES (GPIOB->BSRR |= GPIO_BSRR_BR5)
#define reset_PC13 (GPIOC->BSRR |= GPIO_BSRR_BR13)
#define reset_PC12 (GPIOC->BSRR |= GPIO_BSRR_BR12)


#define dataPort (GPIOA->ODR)

#define setSPT    {lcdWriteCommand(0x07);write_data(0x0153);}    //0053  spt = 1 2screen
#define resetSPT  {lcdWriteCommand(0x07); write_data(0x0053);}  //0053  spt = 0 1screen




void lcdWriteCommand(uint8_t command);
void write_data (unsigned int data);
void Display_Home(void);
void lcdSetPos(uint16_t poz_x_start, uint16_t poz_x_end, uint16_t poz_y_start, uint16_t poz_y_end);
void display_rgb (unsigned int data);
void init_TFT (void);
void set_cursor(unsigned int x, unsigned int y);
void write_symbol(int x, int y, int Size, unsigned int Color, unsigned int Backcolor, char charcode);
void write_String(unsigned int x, unsigned int y, unsigned int color, unsigned int phone, char *str, unsigned char size);



#endif

