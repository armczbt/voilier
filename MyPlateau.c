#include "MyPlateau.h"
#include "MyTimer.h"
#include "MyGPIO.h"

#define PLATEAU_PWM_TIMER TIM3   
#define PLATEAU_PWM_CHANNEL 1 
#define PSC_VALUE 3599
#define ARR_VALUE 1999

static GPIO_TypeDef *Plateau_GPIO;
static uint16_t Plateau_Direction_Pin;

void MyPlateau_Init(GPIO_TypeDef *GPIO, uint16_t directionPin) {
    Plateau_GPIO = GPIO;
    Plateau_Direction_Pin = directionPin;

    MyGPIO_Init(Plateau_GPIO, Plateau_Direction_Pin, AltOut_PushPull); 

    MyTimer_Init(PLATEAU_PWM_TIMER, ARR_VALUE, PSC_VALUE);
    MyTimer_StartPWM(PLATEAU_PWM_TIMER, PLATEAU_PWM_CHANNEL);
}

void MyPlateau_SetDirection(int direction) {
    if (direction == PLATEAU_LEFT) {
        MyGPIO_Set(Plateau_GPIO, Plateau_Direction_Pin);
    } else {
        MyGPIO_Reset(Plateau_GPIO, Plateau_Direction_Pin);
    }
}

void MyPlateau_SetSpeed(float speed) {
    uint16_t dutyCycle = (uint16_t)(ARR_VALUE * speed);
    MyTimer_SetDutyCycle(PLATEAU_PWM_TIMER, PLATEAU_PWM_CHANNEL, dutyCycle);
}
