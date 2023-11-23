#include "stm32f10x.h"
#include "MyPlateau.h"

int main() {
    MyPlateau_Init(GPIOC, 8); 

    while (1) {
        
        MyPlateau_SetDirection(0); 
        MyPlateau_SetSpeed(50); 
    }

    return 0;
}