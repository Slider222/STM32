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
	int posCursorX = 0, posCursorY = 0, value = 0;
    char* string;
	portInit();
	timerInit();    
    __enable_irq ();
    initDelay();				
	GUI_Init();       
    CreateWindow();
  	GUI_CURSOR_SetPosition(posCursorX,posCursorY);
	GUI_CURSOR_Show();    
    value = read_data(0x00);
    string = adc2str(value, string);
    
    while(1){

    GUI_Delay(100);
    for (int i = 0; i < 239; i++){
				posCursorX += 20;
        if (posCursorX > 200){
						posCursorX = 0;
				}
				GUI_CURSOR_SetPosition(posCursorX,posCursorY);				
				Delay_ms(300);
                write_String(100, 100, 0xFF, RED, string, 2);
		}
			
			
    }
}







void TIM2_IRQHandler(){
    if (TIM2->SR & TIM_SR_UIF){
      OS_TimeMS_Inc();
      TIM2->SR &= ~TIM_SR_UIF;
   }          
}

