#include "stm32f10x.h"                  // Device header
#include "funct.h"
//#include "GUI.h"
//#include "WindowDLG.h"
//#include "LCDConf.h"


//#define CS GPIO_Pin_1


//http://www.cyberforum.ru/arm/thread2089985-page21.html
//http://forum.easyelectronics.ru/viewtopic.php?f=35&t=17386&start=475http://forum.easyelectronics.ru/viewtopic.php?f=35&t=17386&p=414039&hilit=Кастомный+драйвер+элементарно+прикручивается#p414039




extern volatile uint64_t msTime;  


int main(void){
	portInit();
	//timerInit();    
    __enable_irq ();
    initDelay();
    init_TFT();
    //Display_Home();   
    display_rgb(0xFFFF);
    write_String(50, 50, 0x0000, 0xffff, "FFF", 3);
    uint16_t x0 = 50, y0 = 50;
    uint16_t x1 = 60, y1 = 60;


    while(1){
        
        getArea(x0,y0,x1,y1);                       //считать область    
        drawRect(x0, y0, x1, y1, RED, 1, 0x0000);   //нарисовать
        Delay_ms(20);
        setArea(x0,y0,x1,y1);                      //закрасить область
        
//        x0++;
//        x1++;

        getArea(x0,y0,x1,y1);                       //считать область
        drawRect(x0, y0, x1, y1, RED, 1, 0x0000);   //нарисовать
        Delay_ms(20);
        setArea(x0, y0, x1, y1);
        
        x0++;
        x1++;
        
        if (x0 >= 229){
           x0 = 50;
           x1 = 60;
           y0 = 50;
           y1 = 60;
        }

	
    }
}







void TIM2_IRQHandler(){
    if (TIM2->SR & TIM_SR_UIF){
      //OS_TimeMS_Inc();
      TIM2->SR &= ~TIM_SR_UIF;
   }          
}

