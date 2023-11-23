#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"
#include "stdbool.h"


void MyTimer_Init(TIM_TypeDef * Timer, uint16_t ARR, uint16_t PSC);
void MyTimer_Start(TIM_TypeDef * Timer);
void MyTimer_Stop(TIM_TypeDef * Timer);
void MyTimer_EnableInterrupt(TIM_TypeDef * Timer, char priority, void (*handler)(void));
void MyTimer_SetDutyCycle(TIM_TypeDef * Timer, char Channel, float DutyCycle);
void MyTimer_StartPWM(TIM_TypeDef * Timer, char Channel);

#endif // MYTIMER_H
