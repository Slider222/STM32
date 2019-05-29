#include "funct.h"
#include "NewFont.h"


volatile uint64_t msTime = 0;




#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))
#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}

void portInit(void){
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPCEN;     //включение тактирования портов 
        
    GPIOA->CRL &= ~GPIO_CRL_CNF1_0;        //Порт A1 на выход
    GPIOA->CRL |= GPIO_CRL_MODE1;    

    GPIOC->CRH &= ~GPIO_CRH_CNF13_0;      //Порт C13 на выход  
    GPIOC->CRH |= GPIO_CRH_MODE13;

    GPIOA->CRL |= GPIO_CRL_CNF0_0;        //Порт A0 на выход
}                                    

void timerInit(){
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;          //включаем тактирование
    TIM2->PSC = 72-1;                            //предделитель таймера 2 (72000000/65534 = 1098Гц)
    TIM2->ARR = 1000;                            //
   
    //__enable_irq ();                                  //глобальное разрешение прерываний
    NVIC->ISER[0] = NVIC_ISER_SETENA_28;                //разрешаем прерывания NVIC
    //NVIC_EnableIRQ(TIM2_IRQn);
    TIM2->DIER |= TIM_DIER_UIE;                         //разрешаем прерывания в таймере 2
    TIM2->CR1 |= TIM_CR1_CEN;                           //включение таймера
}


uint64_t millis(){
    uint64_t millisec = 0;
    __disable_irq ();
    millisec = msTime;
    __enable_irq ();
    return millisec; 
}

uint64_t micros(){
    uint64_t millisec = 0;
    __disable_irq ();
    millisec = msTime;
    __enable_irq ();
    return millisec; 
}







