#include "stm32f10x.h"                  // Device header
#include "funct.h"
//29_05


extern volatile uint64_t msTime;  

int main(void){	
    portInit(); 
	init_TFT();

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

