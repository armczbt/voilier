#include "MyUSART.h"
#include "MyGPIO.h"

// Global handlers
static void (*handlerUSART1)(uint8_t);
static void (*handlerUSART2)(uint8_t);
static void (*handlerUSART3)(uint8_t);

uint16_t floatToUSARTDIV(float x) {
	
	uint16_t integerPart = (uint16_t)x;
	float floatPart = x - integerPart;
	
	uint16_t fraction = 16 * floatPart + 0.5; // + 0.5 for nearest integer
	uint16_t mantissa = integerPart;
	
	return (mantissa << 4) | fraction;
}

void MyUSART_Init(USART_TypeDef *USART, float BaudRate) {
	
	// Clock frequency -> 72MHz
	float floatUSARTDIV = 72e6 / 16 / BaudRate;
	
	// Set Baud rate register
	USART->BRR &= ~(USART_BRR_DIV_Fraction | USART_BRR_DIV_Mantissa);
	USART->BRR |= floatToUSARTDIV(floatUSARTDIV);
	
	USART->CR1 &= ~USART_CR1_M; // Word length is 8 bits
	USART->CR1 &= ~USART_CR1_PCE; // Disable parity control
	
	USART->CR1 |= USART_CR1_RXNEIE; // Enable Rx interrupt
	
	// Enable USART clock
	switch((uint32_t)USART) {
		case (uint32_t)USART1: 
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN; 
		  MyGPIO_Enable_Clock(Clock_A);
			MyGPIO_Init(GPIOA, 9, AltOut_PushPull);
			break;
		
		case (uint32_t)USART2: 
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN; 
			// Missing stuff
			break;
		
		case (uint32_t)USART3: 
			RCC->APB1ENR |= RCC_APB1ENR_USART3EN; 
			// Missing stuff
			break;
	}
	
	USART->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE; // Enable Tx, Rx and USART
}


void MyUSART_TransmitByte(USART_TypeDef *USART, uint8_t byte) {
	
	// Put the byte into the data register
	USART->DR = byte;
	
	while (!(USART->SR & USART_SR_TC)); // Wait for transmission complete
}


void MyUSART_SetRxHandler(USART_TypeDef *USART, uint8_t priority, void (*handler)(uint8_t)) {
	
	IRQn_Type IRQn; 
	
	// Get IRQn from USART pointer
	switch ((uint32_t)USART) {
		case (uint32_t)USART1: 
			IRQn = TIM1_UP_IRQn; 
			handlerUSART1 = handler;
			break;
		case (uint32_t)USART2: 
			IRQn = TIM2_IRQn; 
			handlerUSART2 = handler;
			break;
		case (uint32_t)USART3: 
			IRQn = TIM3_IRQn; 
			handlerUSART3 = handler;
			break;
	}
	
	NVIC_EnableIRQ(IRQn); // Enable interrupt for NVIC
	NVIC_SetPriority(IRQn, (uint32_t)priority); // Set priority for NVIC
}

// A COMPLETER !!!!!!!!!!
void USART1_UP_IRQHandler(void) {
	TIM1->SR &= ~TIM_SR_UIF; // Clear interrupt flag
	handlerUSART1();
}
