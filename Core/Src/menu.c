/*
 * menu.c
 *
 *  Created on: Jul 21, 2022
 *      Author: Anemiq
 */

#include "menu.h"

void func_set_time() {

	bool ovf_minutes = false;
	bool ovf_hours = false;

	MenuItem set_hours = { "SET HOUR", print_time_blink_hours, NULL, NULL };
	MenuItem set_minutes = { "SET MINS", print_time_blink_minutes, &set_hours,
			NULL };
	MenuItem set_seconds = { "SET SECS", print_time_blink_seconds, &set_minutes,
			&set_hours };
	set_hours.prev = &set_seconds;
	set_hours.next = &set_minutes;
	set_minutes.next = &set_seconds;

	MenuItem menu = set_hours;
	while (right_button_pressed || left_button_pressed) {
		HAL_Delay(100);
	};

	new_hours = hours;
	new_minutes = minutes;
	new_seconds = seconds;

	while (true) {
		new_time_blink = !new_time_blink;
		menu.func();
		switch (wait_for_input(250)) {
		case INPUT_NO_INPUT:
			// No input
			break;
		case INPUT_RIGHT_BUTTON_SHORT_PRESS:
			// Right button short press
			if (menu.name == "SET SECS") {
				if (++new_seconds == 60) {
					new_seconds = 0;
					ovf_minutes = true;
				}
			}
			if (menu.name == "SET MINS" || ovf_minutes) {
				if (++new_minutes == 60) {
					new_minutes = 0;
					ovf_hours = true;
				}
				ovf_minutes = false;
			}
			if (menu.name == "SET HOUR" || ovf_hours) {
				if (++new_hours == 24) {
					new_hours = 0;
				}
				ovf_hours = false;
			}
			break;
		case INPUT_RIGHT_BUTTON_LONG_PRESS:
			// Right button long press
			menu = *menu.next;
			break;
		case INPUT_LEFT_BUTTON_SHORT_PRESS:
			// Left button short press
			if (menu.name == "SET SECS") {
				if (--new_seconds > 59) {
					new_seconds = 59;
					ovf_minutes = true;
				}
			}
			if (menu.name == "SET MINS" || ovf_minutes) {
				if (--new_minutes > 59) {
					new_minutes = 59;
					ovf_hours = true;
				}
				ovf_minutes = false;
			}
			if (menu.name == "SET HOUR" || ovf_hours) {
				if (--new_hours > 23) {
					new_hours = 23;
				}
				ovf_hours = false;
			}
			break;
		case INPUT_LEFT_BUTTON_LONG_PRESS:
			// Left button long press
			menu = *menu.prev;
			break;
		case INPUT_BOTH_BUTTONS_LONG_PRESS:
			// Both buttons long press
			// Stop interrupt to swap values
			hours = new_hours;
			minutes = new_minutes;
			seconds = new_seconds;
			write_time();
			return;
		}
	}
}

void func_version(void) {
	char buffer[9];
	snprintf(buffer, 9, "VER %03d", FIRMWARE_VERSION);
	print_string(buffer);
	HAL_Delay(500);
	wait_for_buttons_released();
}

void enter_menu(void) {

	MenuItem set_time = { "SET TIME", func_set_time, NULL, NULL };
	MenuItem set_date = { "SET DATE", NULL, &set_time, NULL };
	MenuItem set_shortcut = { "SHORTCUT", NULL, &set_date, NULL };
	MenuItem version = {"VERSION ", func_version, &set_shortcut, NULL };
	MenuItem status_menu = { "STATUS ", NULL, &version, &set_time };

	set_time.prev = &status_menu;
	set_time.next = &set_date;
	set_date.next = &set_shortcut;
	version.next = &status_menu;
	set_shortcut.next = &version;

	MenuItem menu = status_menu;
	print_string("  MENU  ");
	buzz_motor(100);
	wait_for_buttons_released();
	while (true) {
		print_string(menu.name);
		HAL_Delay(300);
		switch (wait_for_input(5000)) {
		case INPUT_NO_INPUT:
			// No input
			return;
		case INPUT_RIGHT_BUTTON_SHORT_PRESS:
			// Right button short press
			menu = *menu.next;
			break;
		case INPUT_RIGHT_BUTTON_LONG_PRESS:
			// Right button long press
			menu.func();
			break;
		case INPUT_LEFT_BUTTON_SHORT_PRESS:
			// Left button short press
			menu = *menu.prev;
			break;
		case INPUT_LEFT_BUTTON_LONG_PRESS:
			// Left button long press
			buzz_motor(100);
			return;
		}
	}
}
