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

void read_time(void) {
	HAL_I2C_Mem_Read(&hi2c1, (DS3231_I2C_ADDRESS << 1), 0x0, 1, &seconds, 1,
			1000);
	HAL_I2C_Mem_Read(&hi2c1, (DS3231_I2C_ADDRESS << 1), 0x1, 1, &minutes, 1,
			1000);
	HAL_I2C_Mem_Read(&hi2c1, (DS3231_I2C_ADDRESS << 1), 0x2, 1, &hours, 1,
			1000);
	seconds = bcd_to_byte(seconds);
	minutes = bcd_to_byte(minutes);
	hours = bcd_to_byte(hours);
}

void write_time(void) {
	uint8_t bcd_seconds = byte_to_bcd(seconds);
	uint8_t bcd_minutes = byte_to_bcd(minutes);
	uint8_t bcd_hours = byte_to_bcd(hours);
	HAL_I2C_Mem_Write(&hi2c1, (DS3231_I2C_ADDRESS << 1), 0x0, 1, &bcd_seconds,
			1, 1000);
	HAL_I2C_Mem_Write(&hi2c1, (DS3231_I2C_ADDRESS << 1), 0x1, 1, &bcd_minutes,
			1, 1000);
	HAL_I2C_Mem_Write(&hi2c1, (DS3231_I2C_ADDRESS << 1), 0x2, 1, &bcd_hours, 1,
			1000);
}


float get_battery_voltage(void) {
//	return 2 * (3.3 * (uint16_t) battery_voltage) / 4095.0;
	return ((uint16_t) battery_voltage) * 0.0016117216117216;
}

