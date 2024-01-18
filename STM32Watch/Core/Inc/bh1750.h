/*
 * bh1750.h
 *
 *  Created on: Jan 18, 2024
 *      Author: anemiq
 */

#include "definitions.h"
#include "main.h"

#ifndef INC_BH1750_H_
#define INC_BH1750_H_

enum BH1750_Mode {
	// same as Power Down
	UNCONFIGURED = 0,
	// Measurement at 1 lux resolution. Measurement time is approx 120ms.
	CONTINUOUS_HIGH_RES_MODE = 0x10,
	// Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
	CONTINUOUS_HIGH_RES_MODE_2 = 0x11,
	// Measurement at 4 lux resolution. Measurement time is approx 16ms.
	CONTINUOUS_LOW_RES_MODE = 0x13,
	// Measurement at 1 lux resolution. Measurement time is approx 120ms.
	ONE_TIME_HIGH_RES_MODE = 0x20,
	// Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
	ONE_TIME_HIGH_RES_MODE_2 = 0x21,
	// Measurement at 4 lux resolution. Measurement time is approx 16ms.
	ONE_TIME_LOW_RES_MODE = 0x23
}typedef BH1750_Mode;


bool bh1750_configure_mode(BH1750_Mode mode);

void read_current_light_intensity(void);

#endif /* INC_BH1750_H_ */
