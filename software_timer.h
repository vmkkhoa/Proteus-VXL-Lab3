/*
 * software_timer.h
 *
 *  Created on: Oct 26, 2021
 *      Author: ADMIN
 */

#ifndef __SOFTWARE_TIMER_H_
#define __SOFTWARE_TIMER_H_


void setTimer0(int duration);		//every second on the clock
void setTimer1(int duration);		//every 250ms to display LEDs
void setTimer2(int duration);		//1 second to delay for init system
void setTimer3(int duration);		//every 500ms each auto increasing
void setTimer4(int duration);		//LEDs blinking every 0.5s in setting mode
int get_timer_flag(int index);
void timer_run();

#endif /* INC_SOFTWARE_TIMER_H_ */
