#include "stm32f10x.h"                  // Device header
#include "funct.h"
//29_05


extern volatile uint64_t msTime;  

int main(void){	
    //portInit(); 
	//init_TFT();
    volatile uint8_t data1 = 0xF3;
    volatile uint16_t port1 = 0;
    port1 = ((data1 << 7) & 0x7f80)| 0x8000;

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

