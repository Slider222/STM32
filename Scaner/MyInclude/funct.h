#ifndef FUNCT_H_
#define FUNCT_H_





#include "stm32f10x.h"
#include "delay.h" 
#include <stdio.h>
#include "AnMotors.h"

void portInit(void);
void timerInit(void);
uint64_t millis(void);
uint64_t micros(void);


#endif
