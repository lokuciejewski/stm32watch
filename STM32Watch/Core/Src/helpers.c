/*
 * helpers.c
 *
 *  Created on: Jul 21, 2022
 *      Author: Anemiq
 */

#include "helpers.h"

uint8_t byte_to_bcd(uint8_t data) {
	return ((data / 10) << 4) | (data % 10);
}

uint8_t bcd_to_byte(uint8_t data) {
	return ((data >> 4) * 10) + (data % 16);
}

void led_red_on(void) {
	LED_R_PORT->ODR |= LED_R;
}
void led_red_off(void) {
	LED_R_PORT->ODR &= ~LED_R;
}

void led_green_on(void) {
	LED_G_PORT->ODR |= LED_G;
}
void led_green_off(void) {
	LED_G_PORT->ODR &= ~LED_G;
}

float get_battery_voltage(void) {
//	return 2 * (3.3 * (uint16_t) battery_voltage) / 4095.0;
	return ((uint16_t) battery_voltage) * 0.0016117216117216;
}

void print_battery_voltage(void) {
	float vbat = get_battery_voltage();
	char buff[9] = { 'B', 'T', ' ', 48 + (uint8_t) vbat, '.', 48
			+ ((uint8_t) (vbat * 10) % 10), 48 + ((uint8_t) (vbat * 100) % 10),
			'V', '\0' };
	print_string(buff);
}
