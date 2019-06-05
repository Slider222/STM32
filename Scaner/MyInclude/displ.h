#ifndef displ_H_
#define displ_H_



#include "funct.h"

#define RED     0xF864
#define GREEN   0x67E0
#define BLUE    0x48FF



#define set_CS (GPIOA->BSRR |= GPIO_BSRR_BS5)
#define set_RS (GPIOA->BSRR |= GPIO_BSRR_BS4)
#define set_WR (GPIOA->BSRR |= GPIO_BSRR_BS3)
#define set_RD (GPIOA->BSRR |= GPIO_BSRR_BS2)
#define set_LED (GPIOA->BSRR |= GPIO_BSRR_BS0)
#define set_RES (GPIOA->BSRR |= GPIO_BSRR_BS1)
#define set_PC13 (GPIOC->BSRR |= GPIO_BSRR_BS13)
#define set_PC12 (GPIOC->BSRR |= GPIO_BSRR_BS12)

#define reset_CS (GPIOA->BSRR |= GPIO_BSRR_BR5)
#define reset_RS (GPIOA->BSRR |= GPIO_BSRR_BR4)
#define reset_WR (GPIOA->BSRR |= GPIO_BSRR_BR3)
#define reset_RD (GPIOA->BSRR |= GPIO_BSRR_BR2)
#define reset_LED (GPIOA->BSRR |= GPIO_BSRR_BR0)
#define reset_RES (GPIOA->BSRR |= GPIO_BSRR_BR1)
#define reset_PC13 (GPIOC->BSRR |= GPIO_BSRR_BR13)
#define reset_PC12 (GPIOC->BSRR |= GPIO_BSRR_BR12)


#define dataPort (GPIOB->ODR)

#define setSPT    {lcdWriteCommand(0x07);write_data(0x0153);}    //0053  spt = 1 2screen
#define resetSPT  {lcdWriteCommand(0x07); write_data(0x0053);}  //0053  spt = 0 1screen




void lcdWriteCommand(uint8_t command);
void write_data (unsigned int data);
unsigned int read_data(uint8_t data);
void Display_Home(void);
void lcdSetPos(uint16_t poz_x_start, uint16_t poz_x_end, uint16_t poz_y_start, uint16_t poz_y_end);
void display_rgb (unsigned int data);
void init_TFT (void);
void set_cursor(unsigned int x, unsigned int y);
void write_symbol(int x, int y, int Size, unsigned int Color, unsigned int Backcolor, char charcode);
void write_String(unsigned int x, unsigned int y, unsigned int color, unsigned int phone, char *str, unsigned char size);
void drawRect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1,  unsigned int color, unsigned char size, unsigned int backolor);
void line (unsigned char size, int x1, int y1, int x2, int y2, unsigned int color);
void point (unsigned char size, unsigned int x, unsigned int y, unsigned int color);

void displ_PutPixel (uint16_t x, uint16_t y, uint16_t color);
uint16_t displ_GetPixel (uint16_t x, uint16_t y);
void displ_FillRect_fast (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

#endif

