#ifndef MYGPIO_H
#define MYGPIO_H
#include "stm32f10x.h"
#include "stdbool.h"


// Create an enum type for all GPIO configurations

#define In_Floating (0x04) // 0b0100
#define In_PullDown (0x08) // 0b01000
#define In_PullUp (0x18) // 0b11000
#define In_Analog (0x00) // 0b0000
#define Out_PushPull (0x02) // 0b0010
#define Out_OpenDrain (0x06) // 0b0110
#define AltOut_PushPull (0x0A) // 0b1010
#define AltOut_OpenDrain (0xE) // 0b1110

// Clock branches
#define Clock_A (2)
#define Clock_B (3)
#define Clock_C (4)
#define Clock_D (5)
#define Clock_ADC1 (9)
#define Clock_ADC2 (10)
#define Clock_USART1



void MyGPIO_Init(GPIO_TypeDef * GPIO, char GPIO_Pin, char GPIO_Conf);
bool MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin);
void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_Pin);

void MyGPIO_Enable_Clock(char Clock);
void MyGPIO_Disable_Clock(char Clock);



// Useless struct :

//typedef struct {
//	GPIO_TypeDef * GPIO ;
//	char GPIO_Pin ; // numero de 0 a 15
//	char GPIO_Conf ; // voir ci dessous
//} MyGPIO_Struct_TypeDef ;


#endif // MYGPIO_H
