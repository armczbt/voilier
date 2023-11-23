#include "MyGPIO.h"


void MyGPIO_Init(GPIO_TypeDef * GPIO, char GPIO_Pin, char GPIO_Conf) {
	char shift = (GPIO_Pin & 0x7) << 2; // Last 3 bits times 4
		
	// If Pin > 7 -> use CRH
	// 0xF8 = 0b11111000
	if (GPIO_Pin & 0xF8) {
		GPIO->CRH &= ~(0xF << shift); // Reset 4 config bits
		GPIO->CRH |= (GPIO_Conf & 0xF) << shift; // Set some bits to 1
		// Masks the 5th config bit which is only for pull up/down
	}
	// Else -> use CRL
	else {
		GPIO->CRL &= ~(0xF << shift); // Reset 4 config bits
		GPIO->CRL |= (GPIO_Conf & 0xF) << shift; // Set some bits to 1
		// Masks the 5th config bit which is only for pull up/down
	}
	
	// If pull-up/down -> write ODR bit
	if ((GPIO_Conf & 0xF) == 0x8) {
		GPIO->ODR &= ~(1 << GPIO_Pin); // Reset ODR bit
		GPIO->ODR |= (GPIO_Conf >> 4) << GPIO_Pin; // Set ODR bit if needed
	}
}



bool MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	return GPIO->IDR & (1 << GPIO_Pin);
}



void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	GPIO->ODR |= 1 << GPIO_Pin;
}



void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	GPIO->ODR &= ~(1 << GPIO_Pin);
}



void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	GPIO->ODR ^= 1 << GPIO_Pin; // Invert the bit using a XOR
}

void MyGPIO_Enable_Clock(char Clock) {
	RCC->APB2ENR |= 1 << Clock;
}

void MyGPIO_Disable_Clock(char Clock) {
	RCC->APB2ENR &= ~(1 << Clock);
}

