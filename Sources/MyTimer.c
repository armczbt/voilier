#include "MyTimer.h"

// Global handlers
static void (*handlerTIM1)(void);
static void (*handlerTIM2)(void);
static void (*handlerTIM3)(void);
static void (*handlerTIM4)(void);

// Initialize the given timer (TIM1, TIM2, TIM3 or TIM4)
// ARR is the autoreload value
// PSC is the prescale value
void MyTimer_Init(TIM_TypeDef * Timer, uint16_t ARR, uint16_t PSC) {
	switch ((uint32_t)Timer) {
		case (uint32_t)TIM1: RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; break;
		case (uint32_t)TIM2: RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; break;
		case (uint32_t)TIM3: RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; break;
		case (uint32_t)TIM4: RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; break;
	}
	Timer->ARR = ARR;
	Timer->PSC = PSC;
}

// Only accept TIM1, TIM2, TIM3 and TIM4
void MyTimer_EnableInterrupt(TIM_TypeDef * Timer, char priority, void (*handler)(void)) {
	
	IRQn_Type IRQn; // Get IRQn from Timer pointer
	
	Timer->DIER |= TIM_DIER_UIE; // Set update interrupt enabled bit
	
	switch ((uint32_t)Timer) {
		case (uint32_t)TIM1: 
			IRQn = TIM1_UP_IRQn; 
			handlerTIM1 = handler;
			break;
		case (uint32_t)TIM2: 
			IRQn = TIM2_IRQn; 
			handlerTIM2 = handler;
			break;
		case (uint32_t)TIM3: 
			IRQn = TIM3_IRQn; 
			handlerTIM3 = handler;
			break;
		case (uint32_t)TIM4: 
			IRQn = TIM4_IRQn; 
			handlerTIM4 = handler;
			break;
	}
	
	NVIC_EnableIRQ(IRQn); // Enable interrupt for NVIC
	NVIC_SetPriority(IRQn, (uint32_t)priority); // Set priority for NVIC
}

// Set duty cycle (from 0.0 to 1.0)
// Only accept Chanel 1, 2, 3 and 4
void MyTimer_SetDutyCycle(TIM_TypeDef * Timer, char Channel, float DutyCycle) {
	switch (Channel) {
		case 1:	Timer->CCR1 = (uint16_t) (Timer->ARR * DutyCycle); break;
		case 2:	Timer->CCR2 = (uint16_t) (Timer->ARR * DutyCycle); break;
		case 3:	Timer->CCR3 = (uint16_t) (Timer->ARR * DutyCycle); break;
		case 4:	Timer->CCR4 = (uint16_t) (Timer->ARR * DutyCycle); break;
	}
}


// Only accept Chanel 1, 2, 3 and 4
void MyTimer_StartPWM(TIM_TypeDef * Timer, char Channel) {
	
	// For TIM1 set MOE bit to 1
	if (Timer == TIM1) {
		TIM1->BDTR |= TIM_BDTR_MOE; // Set MOE bit to 1
	}
	
	Timer->EGR |= TIM_EGR_UG; // Set UG bit to 1 (update generation)
	
	switch (Channel) {
		case 1:
			Timer->CCMR1 &= ~(TIM_CCMR1_OC1M); // Reset OC1M bits
		  Timer->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2; // Set OC1M bits to 0b110 (mode 1)
		  Timer->CCMR1 |= TIM_CCMR1_OC1PE; // Set OC1PE bit to 1 (preload enable)
			Timer->CCER |= TIM_CCER_CC1E; // Set output enable bit to 1
			break;
		
		case 2:
			Timer->CCMR1 &= ~(TIM_CCMR1_OC2M); // Reset OC2M bits
		  Timer->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2; // Set OC2M bits to 0b110 (mode 1)
		  Timer->CCMR1 |= TIM_CCMR1_OC2PE; // Set OC2PE bit to 1 (preload enable)
			Timer->CCER |= TIM_CCER_CC2E; // Set output enable bit to 1
			break;
		
		case 3:
			Timer->CCMR2 &= ~(TIM_CCMR2_OC3M); // Reset OC3M bits
		  Timer->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2; // Set OC3M bits to 0b110 (mode 1)
		  Timer->CCMR2 |= TIM_CCMR2_OC3PE; // Set OC3PE bit to 1 (preload enable)
			Timer->CCER |= TIM_CCER_CC3E; // Set output enable bit to 1
			break;
		
		case 4:
			Timer->CCMR2 &= ~(TIM_CCMR2_OC4M); // Reset OC4M bits
		  Timer->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2; // Set OC4M bits to 0b110 (mode 1)
		  Timer->CCMR2 |= TIM_CCER_CC2P; // Set OC4PE bit to 1 (preload enable)
			Timer->CCER |= TIM_CCER_CC4E; // Set output enable bit to 1
			break;
	}
	
	
}



// Start the given timer
void MyTimer_Start(TIM_TypeDef * Timer) {
	Timer->CR1 |= TIM_CR1_CEN;
}

// Stop the given timer
void MyTimer_Stop(TIM_TypeDef * Timer) {
	Timer->CR1 &= ~TIM_CR1_CEN;
}


void TIM1_UP_IRQHandler(void) {
	TIM1->SR &= ~TIM_SR_UIF; // Clear interrupt flag
	handlerTIM1();
}

void TIM2_IRQHandler(void) {
	TIM2->SR &= ~TIM_SR_UIF; // Clear interrupt flag
	handlerTIM2();
}

void TIM3_IRQHandler(void) {
	TIM3->SR &= ~TIM_SR_UIF; // Clear interrupt flag
	handlerTIM3();
}

void TIM4_IRQHandler(void) {
	TIM4->SR &= ~TIM_SR_UIF; // Clear interrupt flag
	handlerTIM4();
}
