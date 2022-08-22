/*
 * display.h
 *
 *  Created on: Jul 21, 2022
 *      Author: Anemiq
 */
#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_
#include <stdio.h>
#include <stdint.h>
#include "definitions.h"
#include "main.h"

void enable_displays(void);

void disable_displays(void);

void set_data(const uint8_t data);

void print_char(const uint8_t field, const char c);

void print_string(const char *str);

void scroll_text(const char *str, const uint8_t len, const uint16_t delay_ms);

void print_time(const uint8_t mode);

void print_new_time(void);

void print_time_partial(void);

void print_time_full(void);

void print_time_off(void);

void print_time_blink_hours(void);

void print_time_blink_minutes(void);

void print_time_blink_seconds(void);

#endif /* INC_DISPLAY_H_ */
