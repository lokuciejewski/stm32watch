/*
 * bh1750.c
 *
 *  Created on: Jan 18, 2024
 *      Author: anemiq
 */
#include "bh1750.h"

bool bh1750_configure_mode(BH1750_Mode mode) {
	uint8_t data[1] = { mode };
	HAL_StatusTypeDef result = HAL_I2C_Master_Transmit(&hi2c1,
			(BH1750_I2C_ADDRESS << 1), &data, 1, 1000);
	switch (result) {
	case HAL_OK:
		HAL_Delay(10);
		return true;
	default:
		return false;
	}
}

void read_current_light_intensity(void) {
	uint8_t data[2] = { 0 };
	HAL_StatusTypeDef result = HAL_I2C_Master_Receive(&hi2c1,
			(BH1750_I2C_ADDRESS << 1), &data, 2, 1000);
	if (result == HAL_OK) {
		light_intensity = ((((uint16_t)data[0]) << 8) | (uint16_t)data[1]);
	}
}
