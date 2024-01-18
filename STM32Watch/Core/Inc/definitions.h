/*
 * definitions.h
 *
 *  Created on: Jul 21, 2022
 *      Author: Anemiq
 */

#ifndef INC_DEFINITIONS_H_
#define INC_DEFINITIONS_H_
#include "stm32l0xx_hal.h"
#include <stdbool.h>

#define FIRMWARE_VERSION 59

#define BTN_L_PORT GPIOB
#define BTN_L GPIO_PIN_4

#define BTN_R_PORT GPIOB
#define BTN_R GPIO_PIN_5

#define SEG_DATA GPIOA->ODR
#define SEG_PORT GPIOA
#define ADD_REG GPIOB->ODR
#define ADD_PORT GPIOB

#define BH1750_I2C_ADDRESS 0x23

#define DS3231_I2C_ADDRESS 0x68
#define DS3231_EN GPIO_PIN_8
#define DS3231_EN_PORT GPIOA
#define DS3231_INT_PORT GPIOA
#define DS3231_INT GPIO_PIN_12

#define SHORT_PRESS_DURATION_MS 500
#define LONG_PRESS_DURATION_MS 1000

#define INPUT_NO_INPUT 0
#define INPUT_RIGHT_BUTTON_SHORT_PRESS 1
#define INPUT_RIGHT_BUTTON_LONG_PRESS 2
#define INPUT_LEFT_BUTTON_SHORT_PRESS 3
#define INPUT_LEFT_BUTTON_LONG_PRESS 4
#define INPUT_BOTH_BUTTONS_SHORT_PRESS 5
#define INPUT_BOTH_BUTTONS_LONG_PRESS 6

#define DISPLAY_MODE_OFF 0
#define DISPLAY_MODE_PARTIAL 1
#define DISPLAY_MODE_FULL 2

#define DISPLAY_DOT_REG_SIZE 40 // 320 / 8
#define DISPLAY_IO_PORT GPIOA
#define DISPLAY_DATA_IN GPIO_PIN_1
#define DISPLAY_RS GPIO_PIN_4
#define DISPLAY_CLK GPIO_PIN_3
#define DISPLAY_CE GPIO_PIN_5
#define DISPLAY_RST GPIO_PIN_6

#define BATTERY_CRITICAL_VOLTAGE 3.2
#define BATTERY_CRITICAL_VOLTAGE_OFF 3.3
#define BATTERY_LOW_VOLTAGE 3.4
#define BATTERY_LOW_VOLTAGE_OFF 3.5

struct Display {
	uint8_t dot_register[DISPLAY_DOT_REG_SIZE];
	uint8_t cursor_position;
	uint8_t reg0;
	uint8_t reg1;
}typedef Display;

extern uint32_t battery_voltage;
extern volatile bool battery_critical_mode;

extern volatile bool left_button_pressed;
extern volatile bool right_button_pressed;

extern volatile uint8_t sleep_timeout_counter;
extern volatile uint8_t sleep_timeout_s;
extern volatile uint8_t dim_timeout_s;
extern volatile uint8_t timer_compensation;

extern uint8_t hours;
extern uint8_t minutes;
extern uint8_t seconds;

extern uint8_t new_hours;
extern uint8_t new_minutes;
extern uint8_t new_seconds;

extern uint8_t day;
extern uint8_t month;
extern uint8_t century;
extern uint8_t year;

extern uint8_t new_day;
extern uint8_t new_month;
extern uint8_t new_century;
extern uint8_t new_year;

extern uint16_t light_intensity;
extern bool auto_brightness;

extern bool alarm_1;
extern bool alarm_2;

extern volatile bool blink;
extern volatile Display display;

#endif /* INC_DEFINITIONS_H_ */
