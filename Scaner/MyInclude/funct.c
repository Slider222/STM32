#include "funct.h"



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
     
    RCC->AHBENR |= RCC_AHBENR_CRCEN;
//    GPIOA->CRH &= ~GPIO_CRH_CNF8_0;        //Порт A8 на выход
//    GPIOA->CRH |= GPIO_CRH_MODE8;

    GPIOA->CRL &= ~((GPIO_CRL_CNF7_0)|(GPIO_CRL_CNF6_0)|(GPIO_CRL_CNF5_0)|(GPIO_CRL_CNF4_0)|(GPIO_CRL_CNF3_0)|(GPIO_CRL_CNF2_0)|(GPIO_CRL_CNF1_0)|(GPIO_CRL_CNF0_0));
    GPIOA->CRL |= (GPIO_CRL_MODE7)|(GPIO_CRL_MODE6)|(GPIO_CRL_MODE5)|(GPIO_CRL_MODE4)|(GPIO_CRL_MODE3)|(GPIO_CRL_MODE2)|(GPIO_CRL_MODE1)|(GPIO_CRL_MODE0);

    GPIOB->CRH &= ~((GPIO_CRH_CNF8_0)|(GPIO_CRH_CNF9_0)|(GPIO_CRH_CNF10_0)|(GPIO_CRH_CNF11_0)|(GPIO_CRH_CNF12_0)|(GPIO_CRH_CNF13_0)|(GPIO_CRH_CNF14_0));
    GPIOB->CRH |= (GPIO_CRH_MODE8)|(GPIO_CRH_MODE9)|(GPIO_CRH_MODE10)|(GPIO_CRH_MODE11)|(GPIO_CRH_MODE12)|(GPIO_CRH_MODE13)|(GPIO_CRH_MODE14);
    
	GPIOB->CRL &= ~(GPIO_CRL_CNF7_0);
    GPIOB->CRL |= (GPIO_CRL_MODE7);
    

//    GPIOC->CRH &= ~GPIO_CRH_CNF13_0;      //Порт C13 на выход  
    GPIOC->CRH |= GPIO_CRH_MODE13;

    //GPIOA->CRL |= GPIO_CRL_CNF0_0;        //Порт A0 на вход
	
	  set_CS;
	  set_RS;
	  set_WR;
	  reset_RES;
	  set_RD;
}                                    

void timerInit(){
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;          //включаем тактирование
    TIM2->PSC = 24-1;                            //предделитель таймера 2 (72000000/65534 = 1098Гц)
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

void uartInit(void){
     
     RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
     USART1->BRR = 0x9c4;                            //BaudRate 9600    USART_BRR = (fck + baudrate /2 ) / baudrate
     USART1->CR1 |= USART_CR1_UE;
     USART1->CR1 |= USART_CR1_TE;                   //Включаем передатчик
}

void send_to_uart(uint8_t data) {

     while(!(USART1->SR & USART_SR_TC));  //Ждем пока бит TC в регистре SR станет 1

     USART1->DR = data;                     //Отсылаем байт через UART

}












