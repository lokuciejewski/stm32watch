/*
 * display.h
 *
 *  Created on: Jul 21, 2022
 *      Author: Anemiq
 */
#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "definitions.h"
#include "font.h"
#include "ds3231mz.h"

void init_display(void);

void shift_out_data(const uint8_t data);

void write_to_command_register(const uint8_t command);

void write_dot_register(void);

void display_sleep(const bool sleep);

void set_brightness(const uint8_t brightness);

void set_peak_current_brightness(const uint8_t pcb);

void move_cursor(const uint8_t position);

void write_char(const char c, uint8_t position, const bool snap_to_grid);

uint8_t write_string(const char *str, uint8_t position, const bool snap_to_grid);

void clear_display(void);

void home(void);

void print_char(const char c);

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

void print_date(void);

void print_new_date(void);

void print_date_blink_day(void);

void print_date_blink_month(void);

void print_date_blink_year(void);

#endif /* INC_DISPLAY_H_ */
