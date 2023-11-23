#include "stm32f10x.h"
#include "MyUSART.h"
#include "MyGPIO.h"
#include "MyPlateau.h"

void handlerPlateau(uint8_t received_byte){
		if(received_byte<128)
		{
				MyPlateau_SetDirection(0);
				float speed = (127 - received_byte)*(100/127);
				MyPlateau_SetSpeed(speed);
		}
		else
		{
				MyPlateau_SetDirection(1);
				float speed = (received_byte - 128)*(100/127);
				MyPlateau_SetSpeed(speed);			
		}
}

int main() {

		uint8_t received_byte;
	
    MyUSART_Init(USART1, 9600); 
  
		MyUSART_SetRxHandler(USART1,1,*handlerPlateau); // handler = action sur le plateau/voilier ?

    while (1) {
        received_byte = MyUSART_ReceiveByte(USART1); 

        MyUSART_TransmitByte(USART1, received_byte);


    }
    return 0;
}
