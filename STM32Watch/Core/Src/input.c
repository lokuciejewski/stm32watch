/*
 * input.c
 *
 *  Created on: Jul 21, 2022
 *      Author: Anemiq
 */
#include "input.h"

uint8_t wait_for_input(const uint16_t timeout_ms) {
	wait_for_buttons_released();
	for (uint16_t i = 0; i < timeout_ms; i += 100) {
		if (left_button_pressed) {
			bool long_press = true;
			bool both_pressed = false;
			for (uint16_t j = 0; j < LONG_PRESS_DURATION_MS; j += 100) {
				if (left_button_pressed && right_button_pressed) {
					both_pressed = true;
					HAL_Delay(100);
				} else if (left_button_pressed) {
					both_pressed = false;
					HAL_Delay(100);
				} else
					long_press = false;
			}
			if (both_pressed)
				return INPUT_BOTH_BUTTONS_LONG_PRESS;
			if (long_press)
				return INPUT_LEFT_BUTTON_LONG_PRESS;
			return INPUT_LEFT_BUTTON_SHORT_PRESS;
		}
		if (right_button_pressed) {
			bool long_press = true;
			bool both_pressed = false;
			for (uint16_t j = 0; j < LONG_PRESS_DURATION_MS; j += 100) {
				if (right_button_pressed && left_button_pressed) {
					both_pressed = true;
					HAL_Delay(100);
				} else if (right_button_pressed) {
					both_pressed = false;
					HAL_Delay(100);
				} else
					long_press = false;
			}
			if (both_pressed)
				return INPUT_BOTH_BUTTONS_LONG_PRESS;
			if (long_press)
				return INPUT_RIGHT_BUTTON_LONG_PRESS;
			return INPUT_RIGHT_BUTTON_SHORT_PRESS;
		}
		HAL_Delay(100);
	}
	return INPUT_NO_INPUT;
}

void wait_for_buttons_released(void) {
	while(left_button_pressed || right_button_pressed) {
	}
}


void buzz_motor(const uint16_t time_ms){
	VIB_MOT_GPIO_Port->ODR |= VIB_MOT_Pin;
	HAL_Delay(time_ms);
	VIB_MOT_GPIO_Port->ODR &= ~VIB_MOT_Pin;
}
