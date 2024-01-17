/*
 * display.c
 *
 *  Created on: Jul 21, 2022
 *      Author: Anemiq
 */

#include "display.h"

void init_display() {
	DISPLAY_IO_PORT->ODR &= ~DISPLAY_DATA_IN;
	DISPLAY_IO_PORT->ODR &= ~DISPLAY_CLK;
	DISPLAY_IO_PORT->ODR |= DISPLAY_CE;
	DISPLAY_IO_PORT->ODR &= ~DISPLAY_RS;

	DISPLAY_IO_PORT->ODR &= ~DISPLAY_RST;
	HAL_Delay(10);
	DISPLAY_IO_PORT->ODR |= DISPLAY_RST;

	write_dot_register();
	write_to_command_register(0b01001111); // command reg 0, no sleep, default led current, max brightness
	write_to_command_register(0b10000001); // command reg 1, serial data output (this enables second display)
}

void shift_out_data(const uint8_t data) {
//	delay_cycles(50);
	for (int8_t i = 7; i >= 0; i--) {
		if ((data >> i) & 0b1)
			DISPLAY_IO_PORT->ODR |= DISPLAY_DATA_IN;
		else
			DISPLAY_IO_PORT->ODR &= ~DISPLAY_DATA_IN;
		DISPLAY_IO_PORT->ODR |= DISPLAY_CLK;
		DISPLAY_IO_PORT->ODR &= ~DISPLAY_CLK;
	}
}

void write_to_command_register(const uint8_t command) {
	DISPLAY_IO_PORT->ODR |= DISPLAY_RS;
	DISPLAY_IO_PORT->ODR &= ~DISPLAY_CE;
	if (command >> 7)
		display.reg1 = command;
	else
		display.reg0 = command;
	shift_out_data(command);
	DISPLAY_IO_PORT->ODR |= DISPLAY_CE;
}

void write_dot_register(void) {
	DISPLAY_IO_PORT->ODR &= ~DISPLAY_RS;
	DISPLAY_IO_PORT->ODR &= ~DISPLAY_CE;
	for (uint8_t i = 0; i < DISPLAY_DOT_REG_SIZE; i++)
		shift_out_data(display.dot_register[i]);
	DISPLAY_IO_PORT->ODR |= DISPLAY_CE;
}

void display_sleep(const bool sleep) {
	uint8_t new_reg0 = display.reg0;
	if (sleep) {
		new_reg0 &= 0b10111111;
	} else {
		new_reg0 |= 0b01000000;
	}
	write_to_command_register(new_reg0);
}

void set_brightness(const uint8_t brightness) {
	uint8_t new_reg_value = (display.reg0 & 0b11110000)
			| (brightness & 0b00001111);
	if (new_reg_value != display.reg0)
		write_to_command_register(new_reg_value);
}


void set_peak_current_brightness(const uint8_t pcb) {
	uint8_t new_reg_value = (display.reg0 & 0b11001111)
				| (pcb & 0b00110000);
		if (new_reg_value != display.reg0)
			write_to_command_register(new_reg_value);
}


void move_cursor(const uint8_t position) {
	display.cursor_position = position;
}

void write_char(const char c, uint8_t position, const bool snap_to_grid) {
	if (snap_to_grid)
		position = position * 5;

	for (int i = 0; i < 5; i++) {
		display.dot_register[position + i] = FONT[((c - 0x20) * 5) + i];
	}
}

uint8_t write_string(const char *str, uint8_t position, const bool snap_to_grid) {
	if (snap_to_grid)
		position = position * 5;

	uint8_t str_len = 0;

	while (str[str_len] != '\0') {
		char c = str[str_len];
		for (int i = 0; i < 5; i++) {
			display.dot_register[position + i] = FONT[((c - 0x20) * 5) + i];
		}
		position += 5;
		str_len++;
	}

	return str_len;
}

void clear_display(void) {
	for (uint8_t i = 0; i < DISPLAY_DOT_REG_SIZE; i++)
		display.dot_register[i] = 0;
//	write_dot_register();
}

void home(void) {
	clear_display();
	display.cursor_position = 0;
}

void print_char(const char c) {
	write_char(c, display.cursor_position, true);
	write_dot_register();
	display.cursor_position += 1;
}

void print_string(const char *str) {
	home();
	uint8_t str_len = write_string(str, display.cursor_position,
	true);
	write_dot_register();
	display.cursor_position += str_len;
}

void scroll_text(const char *str, const uint8_t len, const uint16_t delay_ms) {
	HAL_Delay(delay_ms);
	for (uint8_t i = 0; i <= len - 8; i++) {
		print_string(str++);
		HAL_Delay(delay_ms);
	}
	for (uint8_t i = len - 8; i > 0; i--) {
		print_string(--str);
		HAL_Delay(delay_ms);
	}
	print_string(--str);
}

void print_time(const uint8_t mode) {
	char buffer[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	char sec_dot = ' ';
	switch (mode) {
	case DISPLAY_MODE_PARTIAL:
		if (seconds % 2) {
			sec_dot = ':';
		}
		snprintf(buffer, 9, "  %02d%c%02d ", hours, sec_dot, minutes);
		break;
	case DISPLAY_MODE_FULL:
		snprintf(buffer, 9, "%02d:%02d:%02d", hours, minutes, seconds);
		break;
	case DISPLAY_MODE_OFF:
		break;
	}
	print_string(buffer);
}

void print_new_time(void) {
	char buffer[9];
	snprintf(buffer, 9, "%02d:%02d:%02d", new_hours, new_minutes, new_seconds);
	print_string(buffer);
}

void print_time_partial(void) {
	print_time(DISPLAY_MODE_PARTIAL);
}

void print_time_full(void) {
	print_time(DISPLAY_MODE_FULL);
}

void print_time_off() {
	print_time(DISPLAY_MODE_OFF);
}

void print_time_blink_hours(void) {
	if (blink) {
		print_new_time();
	} else {
		char buffer[9];
		snprintf(buffer, 9, "  :%02d:%02d", new_minutes, new_seconds);
		print_string(buffer);
	}
}

void print_time_blink_minutes(void) {
	if (blink) {
		print_new_time();
	} else {
		char buffer[9];
		snprintf(buffer, 9, "%02d:  :%02d", new_hours, new_seconds);
		print_string(buffer);
	}
}

void print_time_blink_seconds(void) {
	if (blink) {
		print_new_time();
	} else {
		char buffer[9];
		snprintf(buffer, 9, "%02d:%02d:  ", new_hours, new_minutes);
		print_string(buffer);
	}
}

void print_date(void) {
	read_date();
	char buffer[9];
	snprintf(buffer, 9, "%02d/%02d/%02d", day, month, year);
	print_string(buffer);
}

void print_new_date(void) {
	char buffer[9];
	snprintf(buffer, 9, "%02d/%02d/%02d", new_day, new_month, new_year);
	print_string(buffer);
}

void print_date_blink_day(void) {
	if (blink) {
		print_new_date();
	} else {
		char buffer[9];
		snprintf(buffer, 9, "  /%02d/%02d", new_month, new_year);
		print_string(buffer);
	}
}

void print_date_blink_month(void) {
	if (blink) {
		print_new_date();
	} else {
		char buffer[9];
		snprintf(buffer, 9, "%02d/  /%02d", new_day, new_year);
		print_string(buffer);
	}
}

void print_date_blink_year(void) {
	if (blink) {
		print_new_date();
	} else {
		char buffer[9];
		snprintf(buffer, 9, "%02d/%02d/  ", new_day, new_month);
		print_string(buffer);
	}
}
