/*
 * definitions.c
 *
 *  Created on: Jul 21, 2022
 *      Author: Anemiq
 */

#include "definitions.h"


const uint32_t SEG_PINS[7] = { GPIO_PIN_6, GPIO_PIN_5, GPIO_PIN_4, GPIO_PIN_3, GPIO_PIN_2, GPIO_PIN_1, GPIO_PIN_0 };

uint32_t battery_voltage = 0;

volatile bool battery_critical_mode = false;

volatile bool left_button_pressed = false;
volatile bool right_button_pressed = false;

volatile uint8_t sleep_timeout_counter = 0;
volatile uint8_t sleep_timeout_s = 10;
volatile uint8_t timer_compensation = 5;

uint8_t hours = 12;
uint8_t minutes = 0;
uint8_t seconds = 0;

volatile bool new_time_blink = false;
volatile uint8_t new_hours;
volatile uint8_t new_minutes;
volatile uint8_t new_seconds;
