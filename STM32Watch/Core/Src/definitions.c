/*
 * definitions.c
 *
 *  Created on: Jul 21, 2022
 *      Author: Anemiq
 */

#include "definitions.h"

uint32_t battery_voltage = 0;

volatile bool battery_critical_mode = false;

volatile bool left_button_pressed = false;
volatile bool right_button_pressed = false;

volatile uint8_t sleep_timeout_counter = 0;
volatile uint8_t dim_timeout_s = 5;
volatile uint8_t sleep_timeout_s = 10;

uint8_t hours = 12;
uint8_t minutes = 0;
uint8_t seconds = 0;

uint8_t new_hours = 0;
uint8_t new_minutes = 0;
uint8_t new_seconds = 0;

uint8_t day = 1;
uint8_t month = 1;
uint8_t century = 20;
uint8_t year = 22;

uint8_t new_day = 0;
uint8_t new_century = 0;
uint8_t new_month = 0;
uint8_t new_year = 0;

uint16_t light_intensity = 4097;
bool auto_brightness = true;

bool alarm_1 = false;
bool alarm_2 = false;

volatile Display display = { { 0 }, 0 };
volatile bool blink = false;
