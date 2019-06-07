#ifndef FUNCT_H_
#define FUNCT_H_





#include "stm32f10x.h"
#include "delay.h" 
#include <stdio.h>
#include "AnMotors.h" 
#include "displ.h"



void portInit(void);
void timerInit(void);
uint64_t millis(void);
uint64_t micros(void);
void portToOut(void);
void portToInput(void);
char* adc2str(uint_fast16_t d, char* out, char base);

void uartInit(void);
void send_to_uart(uint8_t data);

#endif
