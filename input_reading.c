/*
 * input_reading.c
 *
 *  Created on: Oct 13, 2021
 *      Author: ADMIN
 */
 #include "main.h"
 #include "input_reading.h"
 // we aim to work with more than one buttons
 #define NO_OF_BUTTONS 3
 // timer interrupt duration is 10ms , so to pass 1 second ,
 // we need to jump to the interrupt service routine 100 time
 #define DURATION_FOR_AUTO_INCREASING 100	// 100*10ms = 1s
 #define BUTTON_IS_PRESSED 0
 #define BUTTON_IS_RELEASED 1
 // the buffer that the final result is stored after
 // debouncing
 GPIO_PinState buttonBuffer[NO_OF_BUTTONS] = {GPIO_PIN_SET,GPIO_PIN_SET,GPIO_PIN_SET};
 // we define two buffers for debouncing
 GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
 GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
 // we define a flag for a button pressed more than 1 second .
 uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
 // we define counter for automatically increasing the value
 // after the button is pressed more than 1 second .
 uint16_t counterForButtonPress1s[NO_OF_BUTTONS];
void button_reading ( void ){
	 for ( int i = 0; i < NO_OF_BUTTONS ; i++){
		 debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		 switch(i){
		 	 case 0:
		 		 debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BTN0_GPIO_Port , BTN0_Pin );
		 		 break;
		 	 case 1:
		 		 debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BTN1_GPIO_Port , BTN1_Pin );
		 		 break;
		 	 case 2:
		 		 debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(BTN2_GPIO_Port , BTN2_Pin );
		 		 break;
		 	 default: break;
		 }
		 if( debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
			 buttonBuffer[i] = debounceButtonBuffer1[i];
		 //KIEM TRA NEU NUT DUOC NHAN 1S
		 if( buttonBuffer[i] == BUTTON_IS_PRESSED){
			 //todo
			 if(counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING){
				 counterForButtonPress1s[i]++;
			 }
			 else{
				 flagForButtonPress1s[i] = 1;
			 }
		 }
		 else{
			 flagForButtonPress1s[i] = 0;
			 counterForButtonPress1s[i] = 0;
		 }

	}
 }
 int is_button_pressed( uint8_t index ){
	  if( index >= NO_OF_BUTTONS) return 0;
	  if(buttonBuffer[index] == BUTTON_IS_PRESSED)
		  return 1;
	  else return 0;
}
 int is_button_pressed_1s( uint8_t index){
	 if(index >= NO_OF_BUTTONS){
		 return 0xff;
	 }
	 return (flagForButtonPress1s[index] == 1);
 }


