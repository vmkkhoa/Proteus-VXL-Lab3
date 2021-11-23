/*
 * led_display.h
 *
 *  Created on: Nov 10, 2021
 *      Author: ADMIN
 */

#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

void update7SEG(int num);
void display7SEG(int num);
void display_fsm(void);
void display_traffic_led(int num);
void toggle_traffic_led(int num);

#endif /* INC_LED_DISPLAY_H_ */
