/*
 * menu.c
 *
 *  Created on: Jul 21, 2022
 *      Author: Anemiq
 */

#include "menu.h"

void save_changes_notify(void) {
	buzz_motor(100);
}

void func_set_date(void) {

	MenuItem set_day = { "SET DAY ", print_date_blink_day, NULL, NULL };
	MenuItem set_month = { "SET MNTH", print_date_blink_month, &set_day,
	NULL };
	MenuItem set_year = { "SET YEAR", print_date_blink_year, &set_month,
			&set_day };

	set_day.next = &set_month;
	set_day.prev = &set_year;
	set_month.next = &set_year;

	MenuItem menu = set_day;
	wait_for_buttons_released();

	read_date();
	new_day = day;
	new_month = month;
	new_year = year;

	while (true) {
		blink = !blink;
		menu.func();
		switch (wait_for_input(250)) {
		case INPUT_NO_INPUT:
			// No input
			break;
		case INPUT_RIGHT_BUTTON_SHORT_PRESS:
			// Right button short press
			if (menu.name == "SET DAY ") {
				if (++new_day == 32) {
					new_day = 1;
				}
			}
			if (menu.name == "SET MNTH") {
				if (++new_month == 13) {
					new_month = 1;
				}
			}
			if (menu.name == "SET YEAR") {
				if (++new_year == 100) {
					new_year = 0;
				}
			}
			break;
		case INPUT_RIGHT_BUTTON_LONG_PRESS:
			// Right button long press
			menu = *menu.next;
			break;
		case INPUT_LEFT_BUTTON_SHORT_PRESS:
			// Left button short press
			if (menu.name == "SET DAY ") {
				if (--new_day == 0) {
					new_day = 31;
				}
			}
			if (menu.name == "SET MNTH") {
				if (--new_month == 0) {
					new_month = 12;
				}
			}
			if (menu.name == "SET YEAR") {
				if (--new_year > 100) {
					new_year = 99;
				}
			}
			break;
		case INPUT_LEFT_BUTTON_LONG_PRESS:
			// Left button long press
			menu = *menu.prev;
			break;
		case INPUT_BOTH_BUTTONS_LONG_PRESS:
			// Both buttons long press
			// Stop interrupt to swap values
			if (new_month == 4 || new_month == 6 || new_month == 9
					|| new_month == 11) {
				day = fmin(30, new_day);
			} else if (new_month == 2) {
				if (new_year % 4 == 0) {
					day = fmin(29, new_day);
				}
			} else {
				day = new_day;
			}

			month = new_month;
			year = new_year;
			write_date();
			save_changes_notify();
			return;
		}
	}
}

void func_set_time(void) {
	MenuItem set_hours = { "SET HOUR", print_time_blink_hours, NULL, NULL };
	MenuItem set_minutes = { "SET MINS", print_time_blink_minutes, &set_hours,
	NULL };
	MenuItem set_seconds = { "SET SECS", print_time_blink_seconds, &set_minutes,
			&set_hours };
	set_hours.prev = &set_seconds;
	set_hours.next = &set_minutes;
	set_minutes.next = &set_seconds;

	MenuItem menu = set_hours;
	wait_for_buttons_released();

	new_hours = hours;
	new_minutes = minutes;
	new_seconds = seconds;

	while (true) {
		blink = !blink;
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
				}
			}
			if (menu.name == "SET MINS") {
				if (++new_minutes == 60) {
					new_minutes = 0;
				}
			}
			if (menu.name == "SET HOUR") {
				if (++new_hours == 24) {
					new_hours = 0;
				}
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
				}
			}
			if (menu.name == "SET MINS") {
				if (--new_minutes > 59) {
					new_minutes = 59;
				}
			}
			if (menu.name == "SET HOUR") {
				if (--new_hours > 23) {
					new_hours = 23;
				}
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
			save_changes_notify();
			return;
		}
	}
}

void func_status(void) {
	print_string("Vib test");
	buzz_motor(500);
	print_battery_voltage();
	HAL_Delay(1000);
}

void func_version(void) {
	char buffer[9];
	snprintf(buffer, 9, "v.%03d", FIRMWARE_VERSION);
	print_string(buffer);
	HAL_Delay(500);
	wait_for_buttons_released();
}

void func_set_dim_timeout(void) {
	char buffer[9];
	while (true) {
		if (dim_timeout_s != 0) {
			snprintf(buffer, 9, "Dim %03ds", dim_timeout_s);
			print_string(buffer);
		} else {
			print_string("Dim  off");
		}
		switch (wait_for_input(500)) {
		case INPUT_RIGHT_BUTTON_SHORT_PRESS:
			dim_timeout_s++;
			break;
		case INPUT_LEFT_BUTTON_SHORT_PRESS:
			dim_timeout_s--;
			break;
		case INPUT_BOTH_BUTTONS_LONG_PRESS:
			save_changes_notify();
			return;
		}
	}
}

void func_set_timeout(void) {
	char buffer[9];
	while (true) {
		if (sleep_timeout_s != 0) {
			snprintf(buffer, 9, "T/O %03ds", sleep_timeout_s);
			print_string(buffer);
		} else {
			print_string("T/O  off");
		}
		switch (wait_for_input(500)) {
		case INPUT_RIGHT_BUTTON_SHORT_PRESS:
			sleep_timeout_s++;
			break;
		case INPUT_LEFT_BUTTON_SHORT_PRESS:
			sleep_timeout_s--;
			break;
		case INPUT_BOTH_BUTTONS_LONG_PRESS:
			save_changes_notify();
			return;
		}
	}
}

void enter_menu(void) {

	MenuItem set_time = { "Set time", func_set_time, NULL, NULL };
	MenuItem set_date = { "Set date", func_set_date, &set_time, NULL };
	MenuItem set_shortcut = { "Shortcut", NULL, &set_date, NULL };
	MenuItem set_timeout = { "Timeout ", func_set_timeout, &set_shortcut, NULL };
	MenuItem set_dim_timeout = { "Dim T/O ", func_set_dim_timeout, &set_timeout, NULL };
	MenuItem version = { "Version ", func_version, &set_dim_timeout, NULL };
	MenuItem status_menu = { "Status ", func_status, &version, NULL };
	MenuItem alarm_menu = {" Alarm  ", NULL, &status_menu, &set_time};

	status_menu.next = &alarm_menu;
	set_time.prev = &alarm_menu;
	set_time.next = &set_date;
	set_date.next = &set_timeout;
	set_timeout.next = &set_dim_timeout;
	set_dim_timeout.next = &set_shortcut;
	version.next = &status_menu;
	set_shortcut.next = &version;

	MenuItem menu = status_menu;
	print_string("  Menu  ");
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
			buzz_motor(100);
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
