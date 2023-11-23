#ifndef MYUART_H
#define MYUART_H
#include "stm32f10x.h"





void MyUSART_Init(USART_TypeDef *USART, float BaudRate);
void MyUSART_TransmitByte(USART_TypeDef *USART, uint8_t byte);

#endif // MYUART_H
