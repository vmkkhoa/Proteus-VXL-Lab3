/*
 * Traffic_Light.c
 *
 *  Created on: Oct 26, 2021
 *      Author: ADMIN
 */

#include "main.h"
#include "input_reading.h"
#include "software_timer.h"
#include "Traffic_Light.h"
#include "input_processing.h"
#include "led_display.h"

#define INIT_SYSTEM		30
#define	PHASE1_GREEN	31
#define PHASE1_YELLOW 	32
#define PHASE2_GREEN	33
#define PHASE2_YELLOW	34
#define SET_PHASE1_GREEN 35
#define SET_PHASE1_YELLOW 36
#define SET_PHASE2_GREEN 37
#define SET_PHASE2_YELLOW 38


unsigned char statusOfLight = INIT_SYSTEM;
unsigned char timeOfGreenPhase1 = 15;
unsigned char timeOfYellowPhase1 =4;
unsigned char timeOfGreenPhase2 = 15;
unsigned char timeOfYellowPhase2 = 4;


int timeOfLight = 0;
int temp_time = 0;

int led_buffer[] = {0 , 0, 0 , 0 }; // A - B - C - D
void init_timeOfLight(int value){
	timeOfLight = value;
}
void traffic_Light(){
	fsm_for_input_processing();
	if(get_timer_flag(0)==1){
		timeOfLight--;
		setTimer0(1000);
	}
	switch(statusOfLight){
	case INIT_SYSTEM:
			display_traffic_led(0);
			timeOfLight = timeOfGreenPhase1;
			if(get_timer_flag(2)==1){
				statusOfLight = PHASE1_GREEN;
			}

		break;
	case PHASE1_GREEN:
		display_traffic_led(1);
		led_buffer[0] = timeOfLight/10;
		led_buffer[1] = timeOfLight - ((timeOfLight/10)*10);
		led_buffer[2] = (timeOfYellowPhase1+timeOfLight)/10;
		led_buffer[3] = (timeOfYellowPhase1+timeOfLight) - (((timeOfYellowPhase1 + timeOfLight)/10)*10);

		if(timeOfLight==0){
			statusOfLight = PHASE1_YELLOW;
			timeOfLight =timeOfYellowPhase1;
		}
		if(get_btn_value(0) == 1){
			display_traffic_led(5);
			statusOfLight = SET_PHASE1_GREEN;
			clear_btn_value(0);
		}
		break;
	case PHASE1_YELLOW:
		display_traffic_led(2);
		led_buffer[0] = timeOfLight/10;
		led_buffer[1] = timeOfLight - ((timeOfLight/10)*10);
		led_buffer[2] = (timeOfLight)/10;
		led_buffer[3] = (timeOfLight) - (((timeOfLight)/10)*10);

		if(timeOfLight==0){
			statusOfLight = PHASE2_GREEN;
			timeOfLight = timeOfGreenPhase2;
		}
		if(get_btn_value(0) == 1){
			display_traffic_led(5);
			statusOfLight = SET_PHASE1_GREEN;
			clear_btn_value(0);
		}
		break;
	case PHASE2_GREEN:
		display_traffic_led(3);
		led_buffer[0] = (timeOfYellowPhase2+timeOfLight)/10;
		led_buffer[1] = (timeOfYellowPhase2+timeOfLight) - (((timeOfYellowPhase1 + timeOfLight)/10)*10);
		led_buffer[2] = timeOfLight/10;
		led_buffer[3] = timeOfLight - ((timeOfLight/10)*10);

		if(timeOfLight==0){
			statusOfLight = PHASE2_YELLOW;
			timeOfLight = timeOfYellowPhase2;
		}
		if(get_btn_value(0) == 1){
			display_traffic_led(5);
			statusOfLight = SET_PHASE1_GREEN;
			clear_btn_value(0);
		}
		break;
	case PHASE2_YELLOW:
		display_traffic_led(4);
		led_buffer[0] = (timeOfLight)/10;
		led_buffer[1] = (timeOfLight) - (((timeOfLight)/10)*10);
		led_buffer[2] = timeOfLight/10;
		led_buffer[3] = timeOfLight - ((timeOfLight/10)*10);

		if(timeOfLight==0){
			statusOfLight = PHASE1_GREEN;
			timeOfLight = timeOfGreenPhase1;
		}
		if(get_btn_value(0) == 1){
			display_traffic_led(5);
			statusOfLight = SET_PHASE1_GREEN;
			clear_btn_value(0);
		}
		break;
	case SET_PHASE1_GREEN:
		if(get_btn_value(1) == 1){
			temp_time++;
			if(temp_time==100){
				temp_time=1;
			}
			clear_btn_value(1);
		}
		if(get_timer_flag(4) == 1){
			toggle_traffic_led(0);		//TOGGLE VERTICAL GREEN LEDs
			setTimer4(500);
		}

		led_buffer[0] = 0;
		led_buffer[1] = 2;
		led_buffer[2] = temp_time/10;
		led_buffer[3] = temp_time - ((temp_time/10)*10);

		if(get_btn_value(2) == 1){
			timeOfGreenPhase1 = temp_time;
			clear_btn_value(2);
			//temp_time=0;
		}

		if(get_btn_value(0) == 1){
			display_traffic_led(6);
			statusOfLight = SET_PHASE1_YELLOW;
			temp_time =0;
			clear_btn_value(0);
		}
		break;
	case SET_PHASE1_YELLOW:

		if(get_btn_value(1) == 1){
			temp_time++;
			if(temp_time==100){
				temp_time=1;
			}
			clear_btn_value(1);
		}
		if(get_timer_flag(4) == 1){
			toggle_traffic_led(1);		//TOGGLE VERTICAL YELLOW LEDs
			setTimer4(500);
		}
		led_buffer[0] = 0;
		led_buffer[1] = 3;
		led_buffer[2] = temp_time/10;
		led_buffer[3] = temp_time - ((temp_time/10)*10);

		if(get_btn_value(2) == 1){
			timeOfYellowPhase1 = temp_time;
			//temp_time=0;
			clear_btn_value(2);
		}
		if(get_btn_value(0) == 1){
			display_traffic_led(7);
			statusOfLight = SET_PHASE2_GREEN;
			temp_time =0;
			clear_btn_value(0);
		}
		break;
	case SET_PHASE2_GREEN:

		if(get_btn_value(1) == 1){
			temp_time++;
			if(temp_time==100){
				temp_time=1;
			}
			clear_btn_value(1);
		}
		if(get_timer_flag(4) == 1){
			toggle_traffic_led(2);		//TOGGLE HORIZONTAL GREEN LEDs
			setTimer4(500);
		}
		led_buffer[0] = 0;
		led_buffer[1] = 4;
		led_buffer[2] = temp_time/10;
		led_buffer[3] = temp_time - ((temp_time/10)*10);

		if(get_btn_value(2) == 1){
			timeOfGreenPhase2 = temp_time;
			//temp_time=0;
			clear_btn_value(2);
		}

		if(get_btn_value(0) == 1){
			display_traffic_led(8);
			statusOfLight = SET_PHASE2_YELLOW;
			temp_time =0;
			clear_btn_value(0);
		}
		break;
	case SET_PHASE2_YELLOW:
		if(get_btn_value(1) == 1){
			temp_time++;
			if(temp_time==100){
				temp_time=1;
			}
			clear_btn_value(1);
		}
		if(get_timer_flag(4) == 1){
			toggle_traffic_led(3);		//TOGGLE HORIZONTAL YELLOW LEDs
			setTimer4(500);
		}
		led_buffer[0] = 0;
		led_buffer[1] = 5;
		led_buffer[2] = temp_time/10;
		led_buffer[3] = temp_time - ((temp_time/10)*10);

		if(get_btn_value(2) == 1){
			timeOfYellowPhase2 = temp_time;
			temp_time=0;
			clear_btn_value(2);
		}
		if(get_btn_value(0) == 1){
			statusOfLight = INIT_SYSTEM;
			setTimer2(1000);
			temp_time =0;
			clear_btn_value(0);
		}
		break;
	default: break;
	}
}
