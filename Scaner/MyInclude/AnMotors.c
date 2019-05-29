#include "AnMotors.h"

volatile unsigned long prevtime;
volatile unsigned int lolen, hilen, state;
volatile static char bcounter = 0;    						// количество прин¤тых битов
volatile static long code1 = 0;       						// зашифрованна¤ часть
volatile static long code2 = 0;       						// фиксированна¤ часть 

void SendANMotors(long c1, long c2){
    __disable_irq ();
     for (int j = 0; j < 4; j++){
    // отправл¤ем 12 начальных импульсов 0-1
        for (int i = 0; i < 12; i++) {
            Delay_mks(Pe);
            GPIOA->BSRR |= GPIO_BSRR_BS1;
            Delay_mks(Pe);
            GPIOA->BSRR |= GPIO_BSRR_BR1;            
        }
        Delay_mks(Pe * 10);
        // отправл¤ем первую половину
        for (int i = 4 * 8; i > 0; i--) {
            int k = i - 1;
            SendBit((1 << k) & c1);
        }
        // вторую половину
        for (int i = 4 * 8; i > 0; i--) {
            int j = i - 1;
            SendBit((1 << j) & c2);
        }
         // и еще пару ненужных бит, которые означают батарейку и флаг повтора
        SendBit(1);
        SendBit(1);
        Delay_mks(Pe * 39);
    }
    __enable_irq ();
} 

void SendBit(char b) {
  if (b == 0) {
    GPIOA->BSRR |= GPIO_BSRR_BS1; // 0
    Delay_mks(Pe2);
    GPIOA->BSRR |= GPIO_BSRR_BR1;
    Delay_mks(Pe);
  }
  else {
    GPIOA->BSRR |= GPIO_BSRR_BS1; // 1
    Delay_mks(Pe);
    GPIOA->BSRR |= GPIO_BSRR_BR1;
    Delay_mks(Pe2);
  }
}

char CheckValue(unsigned int base, unsigned int value)
{
  return ((value == base) || ((value > base) && ((value - base) < MAX_DELTA)) || ((value < base) && ((base - value) < MAX_DELTA)));
} 

void grab() {
  state = GPIOA->IDR & GPIO_IDR_IDR0;
  if (state == HIGH)
    lolen = micros() - prevtime;
  else
    hilen = micros() - prevtime;
  prevtime = micros();
 
  if (state == HIGH)
  {
    // последовательность закончилась
    if (CheckValue(Pe, hilen) && CheckValue(Pe2, lolen)) // valid 1
    {
      if (bcounter < 32)
        code1 = (code1 << 1) | 1;
      else if (bcounter < 64)
        code2 = (code2 << 1) | 1;
      bcounter++;
    }
    else if (CheckValue(Pe2, hilen) && CheckValue(Pe, lolen)) // valid 0
    {
      if (bcounter < 32)
        code1 = (code1 << 1) | 0;
      else if (bcounter < 64)
        code2 = (code2 << 1) | 0; bcounter++;
    }
    else
      bcounter = 0;
  }
  if (bcounter >= 65)
  {
    printf("Перехвачено: ");
    //printf(code1);
    //printf(" ");
    //printf(code2);
 
    bcounter = 0;
    code1 = 0;
    code2 = 0;
  }
}
