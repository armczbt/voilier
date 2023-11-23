#ifndef MYPLATEAU_H
#define MYPLATEAU_H

#include "stm32f10x.h"

#define PLATEAU_LEFT 0
#define PLATEAU_RIGHT 1


void MyPlateau_Init(GPIO_TypeDef *GPIO, uint16_t directionPin);
void MyPlateau_SetDirection(int direction);
void MyPlateau_SetSpeed(float speed);

#endif // MYPLATEAU_H
