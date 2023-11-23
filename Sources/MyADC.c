#include "MyADC.h"
#include "MyGPIO.h"


void MyADC_Init(ADC_TypeDef *ADC, uint8_t Channel) {
	
	// Enable the clock
	switch ((uint32_t)ADC) {
		case (uint32_t)ADC1: 
			MyGPIO_Enable_Clock(Clock_ADC1);
			break;
		case (uint32_t)ADC2: 
			MyGPIO_Enable_Clock(Clock_ADC2);
			break;
	}
	
	
	ADC->CR2 &= ~(ADC_CR2_CONT); // Disable continuous conversion
	
	ADC->SQR1 &= ~(ADC_SQR1_L); // Clear sequence length bits (1 conversion)
	ADC->SQR3 &= ~ADC_SQR3_SQ1; // Clear SQ1 bits
	ADC->SQR3 |= ADC_SQR3_SQ1 & Channel; // Set right channel for SQ1
	
	ADC->CR2 |= ADC_CR2_ADON; // Set ADON bit to turn on the ADC
	
	
}

uint16_t MyADC_Read(ADC_TypeDef *ADC) {
	
	ADC->CR2 |= ADC_CR2_SWSTART; // Start conversion by setting SWSTART bit
	
	// Block until conversion is finished
	while (ADC->SR & ADC_SR_EOC) ;
	
	// Return regular value 16 first bits of Data Register
	return ADC->DR & ADC_DR_DATA;
}

