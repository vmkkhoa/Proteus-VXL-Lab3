/*
 * input_processing.c
 *
 *  Created on: Oct 13, 2021
 *      Author: ADMIN
 */
 # include "main.h"
 # include "input_reading.h"
#include "Traffic_Light.h"
#include "software_timer.h"


 enum ButtonState { BUTTON_RELEASED , BUTTON_PRESSED ,BUTTON_PRESSED_MORE_THAN_1_SECOND } ;
 enum ButtonState buttonState = BUTTON_RELEASED ;
 int btn0_value = 0;
 int btn1_value = 0;
 int btn2_value = 0;



 void fsm_for_input_processing(void){
 switch ( buttonState ){
 	 case BUTTON_RELEASED :
 		 if( is_button_pressed(0) && !is_button_pressed_1s(0)){
 			 buttonState = BUTTON_PRESSED ;
 			 HAL_GPIO_TogglePin(LED_TEST_GPIO_Port, LED_TEST_Pin);
 			 btn0_value = 1;
 		 }
 		 if( is_button_pressed(1) && !is_button_pressed_1s(1)){
 			 buttonState = BUTTON_PRESSED ;
 			 HAL_GPIO_TogglePin(LED_TEST_GPIO_Port, LED_TEST_Pin);
			 btn1_value = 1;
 		 }
 		 if( is_button_pressed(2) && !is_button_pressed_1s(2) ){
 			 buttonState = BUTTON_PRESSED ;
 			 HAL_GPIO_TogglePin(LED_TEST_GPIO_Port, LED_TEST_Pin);
			 btn2_value = 1;
 		 }
 		 break ;
 	 case BUTTON_PRESSED :
 		 if (!is_button_pressed(0) && !is_button_pressed(1) && !is_button_pressed(2)){
 			 buttonState = BUTTON_RELEASED ;
 		 }
 		 else {
			 btn0_value = 0;
			 btn1_value = 0;
			 btn2_value = 0;

 			 if(is_button_pressed_1s(0) ){
 				 buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND ;
 			 }
 			 if(is_button_pressed_1s(1) ){
 				 buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND ;
 			 }
 			 if(is_button_pressed_1s(2) ){
 				 buttonState = BUTTON_PRESSED_MORE_THAN_1_SECOND ;
 			 }

 		 }
 		 break ;
 	 case BUTTON_PRESSED_MORE_THAN_1_SECOND :
 		 if (!is_button_pressed(0) && !is_button_pressed(1) && !is_button_pressed(2)){
 			 buttonState = BUTTON_RELEASED ;
 		 }

 		 //AUTO INCREASE EVERY O.5s
 		 if(is_button_pressed_1s(1)){
 		 	 if(get_timer_flag(3)==1){
 		 		 temp_time++;
 		 		 setTimer3(500);
 		 	 }
 		 }
 		 break ;
 	 }
 }
 int get_btn_value(int index){
	 switch (index) {
		case 0:
			return btn0_value;
			break;
		case 1:
			return btn1_value;
			break;
		case 2:
			return btn2_value;
			break;
		default:
			break;
	}
	 return 0;
 }
 void clear_btn_value(int index){
	 switch (index) {
		case 0:
			btn0_value = 0;
			break;
		case 1:
			btn1_value = 0;
			break;
		case 2:
			btn2_value = 0;
			break;
		default:
			break;
	}
 }
