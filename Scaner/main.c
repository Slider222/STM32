#include "stm32f10x.h"                  // Device header
#include "funct.h"
#include "GUI.h"
#include "WindowDLG.h"
#include "LCDConf.h"

//#define CS GPIO_Pin_1


//http://www.cyberforum.ru/arm/thread2089985-page21.html
//http://forum.easyelectronics.ru/viewtopic.php?f=35&t=17386&start=475http://forum.easyelectronics.ru/viewtopic.php?f=35&t=17386&p=414039&hilit=Кастомный+драйвер+элементарно+прикручивается#p414039




extern volatile uint64_t msTime;  


int main(void){
		portInit();
		timerInit();    
        __enable_irq ();
        initDelay();				
	    GUI_Init();       
        CreateWindow();
	    //display_rgb(RED);
         


    while(1){

		GUI_Delay(100);

    }
}







void TIM2_IRQHandler(){
    if (TIM2->SR & TIM_SR_UIF){
      OS_TimeMS_Inc();
      TIM2->SR &= ~TIM_SR_UIF;
   }          
}

