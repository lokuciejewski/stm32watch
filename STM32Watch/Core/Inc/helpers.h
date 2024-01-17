/*
 * helpers.h
 *
 *  Created on: Jul 21, 2022
 *      Author: Anemiq
 */

#ifndef INC_HELPERS_H_
#define INC_HELPERS_H_

#include <stdint.h>
#include "definitions.h"
#include "main.h"

uint8_t byte_to_bcd(uint8_t data);
uint8_t bcd_to_byte(uint8_t data);

float get_battery_voltage(void);
void print_battery_voltage(void);

#endif /* INC_HELPERS_H_ */
