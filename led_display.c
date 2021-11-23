/*
 * led_display.c
 *
 *  Created on: Nov 10, 2021
 *      Author: ADMIN
 */


#include "main.h"
#include "led_display.h"
#include "software_timer.h"

int index_7SEG=0;
int state_7SEG=0;
int led_enable=1;

void toggle_traffic_led(int num){
	switch (num) {
		case 0:
			HAL_GPIO_TogglePin(GRN1_GPIO_Port, GRN1_Pin);
			break;
		case 1:
			HAL_GPIO_TogglePin(YLW1_GPIO_Port, YLW1_Pin);
			break;
		case 2:
			HAL_GPIO_TogglePin(GRN2_GPIO_Port, GRN2_Pin);
			break;
		case 3:
			HAL_GPIO_TogglePin(YLW2_GPIO_Port, YLW2_Pin);
			break;
		default:
			break;
	}
}

void display_traffic_led(int num){
	switch (num) {
		case 0:						//CLEAR ALL LEDs
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, SET);
			HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, SET);
			HAL_GPIO_WritePin(YLW1_GPIO_Port, YLW1_Pin, SET);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, SET);
			HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, SET);
			HAL_GPIO_WritePin(YLW2_GPIO_Port, YLW2_Pin, SET);
			break;
		case 1:						//GREEN 1 AND RED 2 ARE ON
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, SET);
			HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, RESET);
			HAL_GPIO_WritePin(YLW1_GPIO_Port, YLW1_Pin, SET);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, RESET);
			HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, SET);
			HAL_GPIO_WritePin(YLW2_GPIO_Port, YLW2_Pin, SET);
			break;
		case 2:						//YELLOW 1 AND RED 2 ARE ON
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, SET);
			HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, SET);
			HAL_GPIO_WritePin(YLW1_GPIO_Port, YLW1_Pin, RESET);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, RESET);
			HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, SET);
			HAL_GPIO_WritePin(YLW2_GPIO_Port, YLW2_Pin, SET);
			break;
		case 3:						//GREEN 2 AND RED 1 ARE ON
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, RESET);
			HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, SET);
			HAL_GPIO_WritePin(YLW1_GPIO_Port, YLW1_Pin, SET);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, SET);
			HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, RESET);
			HAL_GPIO_WritePin(YLW2_GPIO_Port, YLW2_Pin, SET);
			break;
		case 4:						// YELLOW 2 AND RED 1 ARE ON
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, RESET);
			HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, SET);
			HAL_GPIO_WritePin(YLW1_GPIO_Port, YLW1_Pin, SET);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, SET);
			HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, SET);
			HAL_GPIO_WritePin(YLW2_GPIO_Port, YLW2_Pin, RESET);
			 break;
		case 5:						//ONLY GREEN 1 IS ON
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, SET);
			HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, RESET);
			HAL_GPIO_WritePin(YLW1_GPIO_Port, YLW1_Pin, SET);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, SET);
			HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, SET);
			HAL_GPIO_WritePin(YLW2_GPIO_Port, YLW2_Pin, SET);
			break;
		case 6:						//ONLY YELLOW 1 IS ON
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, SET);
			HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, SET);
			HAL_GPIO_WritePin(YLW1_GPIO_Port, YLW1_Pin, RESET);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, SET);
			HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, SET);
			HAL_GPIO_WritePin(YLW2_GPIO_Port, YLW2_Pin, SET);
			break;
		case 7:						//ONLY GREEN 2 IS ON
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, SET);
			HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, SET);
			HAL_GPIO_WritePin(YLW1_GPIO_Port, YLW1_Pin, SET);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, SET);
			HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, RESET);
			HAL_GPIO_WritePin(YLW2_GPIO_Port, YLW2_Pin, SET);
			 break;
		case 8: 					//ONLY YELLOW 2 IS ON
			HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, SET);
			HAL_GPIO_WritePin(GRN1_GPIO_Port, GRN1_Pin, SET);
			HAL_GPIO_WritePin(YLW1_GPIO_Port, YLW1_Pin, SET);
			HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, SET);
			HAL_GPIO_WritePin(GRN2_GPIO_Port, GRN2_Pin, SET);
			HAL_GPIO_WritePin(YLW2_GPIO_Port, YLW2_Pin, RESET);
			break;
		default:
			break;
	}
}

void display7SEG(int num){
	  switch(num){
	  case 0: //NUMBER 0
		  HAL_GPIO_WritePin(SEG1_A_GPIO_Port, SEG1_A_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_B_GPIO_Port, SEG1_B_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_C_GPIO_Port, SEG1_C_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_D_GPIO_Port, SEG1_D_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_E_GPIO_Port, SEG1_E_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_F_GPIO_Port, SEG1_F_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_G_GPIO_Port, SEG1_G_Pin, SET);
		  break;
	  case 1:	//NUMBER 1
		  HAL_GPIO_WritePin(SEG1_A_GPIO_Port, SEG1_A_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_B_GPIO_Port, SEG1_B_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_C_GPIO_Port, SEG1_C_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_D_GPIO_Port, SEG1_D_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_E_GPIO_Port, SEG1_E_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_F_GPIO_Port, SEG1_F_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_G_GPIO_Port, SEG1_G_Pin, SET);
		  break;
	  case 2:	//NUMBER 2
		  HAL_GPIO_WritePin(SEG1_A_GPIO_Port, SEG1_A_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_B_GPIO_Port, SEG1_B_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_C_GPIO_Port, SEG1_C_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_D_GPIO_Port, SEG1_D_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_E_GPIO_Port, SEG1_E_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_F_GPIO_Port, SEG1_F_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_G_GPIO_Port, SEG1_G_Pin, RESET);
		  break;
	  case 3:
		  HAL_GPIO_WritePin(SEG1_A_GPIO_Port, SEG1_A_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_B_GPIO_Port, SEG1_B_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_C_GPIO_Port, SEG1_C_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_D_GPIO_Port, SEG1_D_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_E_GPIO_Port, SEG1_E_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_F_GPIO_Port, SEG1_F_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_G_GPIO_Port, SEG1_G_Pin, RESET);
		  break;
	  case 4:
		  HAL_GPIO_WritePin(SEG1_A_GPIO_Port, SEG1_A_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_B_GPIO_Port, SEG1_B_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_C_GPIO_Port, SEG1_C_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_D_GPIO_Port, SEG1_D_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_E_GPIO_Port, SEG1_E_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_F_GPIO_Port, SEG1_F_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_G_GPIO_Port, SEG1_G_Pin, RESET);
		  break;
	  case 5:
		  HAL_GPIO_WritePin(SEG1_A_GPIO_Port, SEG1_A_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_B_GPIO_Port, SEG1_B_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_C_GPIO_Port, SEG1_C_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_D_GPIO_Port, SEG1_D_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_E_GPIO_Port, SEG1_E_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_F_GPIO_Port, SEG1_F_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_G_GPIO_Port, SEG1_G_Pin, RESET);
		  break;
	  case 6:
		  HAL_GPIO_WritePin(SEG1_A_GPIO_Port, SEG1_A_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_B_GPIO_Port, SEG1_B_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_C_GPIO_Port, SEG1_C_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_D_GPIO_Port, SEG1_D_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_E_GPIO_Port, SEG1_E_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_F_GPIO_Port, SEG1_F_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_G_GPIO_Port, SEG1_G_Pin, RESET);
		  break;
	  case 7:
		  HAL_GPIO_WritePin(SEG1_A_GPIO_Port, SEG1_A_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_B_GPIO_Port, SEG1_B_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_C_GPIO_Port, SEG1_C_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_D_GPIO_Port, SEG1_D_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_E_GPIO_Port, SEG1_E_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_F_GPIO_Port, SEG1_F_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_G_GPIO_Port, SEG1_G_Pin, SET);
		  break;
	  case 8:
		  HAL_GPIO_WritePin(SEG1_A_GPIO_Port, SEG1_A_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_B_GPIO_Port, SEG1_B_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_C_GPIO_Port, SEG1_C_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_D_GPIO_Port, SEG1_D_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_E_GPIO_Port, SEG1_E_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_F_GPIO_Port, SEG1_F_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_G_GPIO_Port, SEG1_G_Pin, RESET);
		  break;
	  case 9:
		  HAL_GPIO_WritePin(SEG1_A_GPIO_Port, SEG1_A_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_B_GPIO_Port, SEG1_B_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_C_GPIO_Port, SEG1_C_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_D_GPIO_Port, SEG1_D_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_E_GPIO_Port, SEG1_E_Pin, SET);
		  HAL_GPIO_WritePin(SEG1_F_GPIO_Port, SEG1_F_Pin, RESET);
		  HAL_GPIO_WritePin(SEG1_G_GPIO_Port, SEG1_G_Pin, RESET);
		  break;
	  default:
		  break;
	  }
 }
void update7SEG ( int index ) {
	 switch ( index ) {
	 	 case 0:
	 		 // Display the first 7 SEG with led_buffer [0]
	 		 display7SEG(led_buffer[0]);
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);

	 		 break ;
	 	 case 1:
	 		 // Display the second 7 SEG with led_buffer [1]
 	 		 display7SEG(led_buffer[1]);
 			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
 			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
 			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
 			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);

	 		 break ;
	 	 case 2:
	 		 // Display the third 7 SEG with led_buffer [2]
	 		 display7SEG(led_buffer[2]);
 			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
 			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
 			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
 			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);

	 		 break ;
	 	 case 3:
	 		 // Display the forth 7 SEG with led_buffer [3]
	 		 display7SEG(led_buffer[3]);
 			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
 			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
 			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
 			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);

	 		 break ;
	 	 default :
	 		 break ;
	 }
}

void display_fsm(void){
	switch(state_7SEG){
		case 0: //LED 0
			update7SEG(index_7SEG);
			if(led_enable <=0){
				led_enable = 1;
				index_7SEG= index_7SEG+1;
				state_7SEG = 1;
			}
			break;
		case 1:		//LED 1
			update7SEG(index_7SEG);
			if(led_enable <=0){
				led_enable = 1;
				index_7SEG= index_7SEG+1;
				state_7SEG = 2;
			}
			break;
		case 2:	 	//LED 2

			update7SEG(index_7SEG);
			if(led_enable <=0){
				led_enable = 1;
				index_7SEG= index_7SEG+1;
				state_7SEG = 3;
			}
			break;
		case 3:		//LED 3
			update7SEG(index_7SEG);
			if(led_enable <=0){
				led_enable= 1;
				index_7SEG = 0; //last index -> reset
				state_7SEG = 0;
			}
			break;
		default:
			break;
	}

	  if(get_timer_flag(1)==1){
		  led_enable =0;
		  setTimer1(250);
	  }
}
