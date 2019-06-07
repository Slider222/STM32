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
	int posCursorX = 0, posCursorY = 5, value = 0;
    char* string;
	portInit();
	timerInit();    
    __enable_irq ();
    initDelay();				
	GUI_Init();       
    CreateWindow();
  	GUI_CURSOR_SetPosition(posCursorX,posCursorY);
	GUI_CURSOR_Show();    
    
    
    while(1){

    GUI_Delay(1);
    for (int i = 0; i < 239; i++){
				posCursorX += 1;
		GUI_CURSOR_SetPosition(posCursorX,posCursorX);
        if (posCursorX > 238){
						posCursorX = 0;
				}
//		value = read_data(0x22);
//    string = adc2str(value, string, 16);
//    write_String(100, 100, 0x0000, 0xFFFF, string, 4);    
		}
		
		
			
    }
}







void TIM2_IRQHandler(){
    if (TIM2->SR & TIM_SR_UIF){
      OS_TimeMS_Inc();
      TIM2->SR &= ~TIM_SR_UIF;
   }          
}

