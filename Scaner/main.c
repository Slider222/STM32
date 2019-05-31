#include "stm32f10x.h"                  // Device header
#include "funct.h"

#define CS GPIO_Pin_1


extern volatile uint64_t msTime;  

int main(void){	
<<<<<<< HEAD
    portInit(); 
		init_TFT();		
=======
    //portInit(); 
	//init_TFT();
    volatile uint8_t data1 = 0xF3;
    volatile uint16_t port1 = 0;
    port1 = ((data1 << 7) & 0x7f80)| 0x8000;

>>>>>>> a795ee346a81b17659b96aecfb4912bb7b397f3c
    while(1){
    ;
    }
}







void TIM2_IRQHandler(){
    if (TIM2->SR & TIM_SR_UIF){
      msTime++;
      TIM2->SR &= ~TIM_SR_UIF;
   }          
}

