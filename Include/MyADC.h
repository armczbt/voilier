#ifndef MYADC_H
#define MYADC_H
#include "stm32f10x.h"
#include "stdbool.h"

// Channel-pin table is in table 5 

void MyADC_Init(ADC_TypeDef *ADC, uint8_t Channel);
uint16_t MyADC_Read(ADC_TypeDef *ADC); // Return a value from 0x000 to 0xfff

#endif // MYADC_H
