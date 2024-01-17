/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include "definitions.h"
#include "display.h"
#include "input.h"
#include "menu.h"
#include "helpers.h"
#include "ds3231mz.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define VIB_MOT_Pin GPIO_PIN_14
#define VIB_MOT_GPIO_Port GPIOC
#define DISPLAY_DATA_IN_Pin GPIO_PIN_1
#define DISPLAY_DATA_IN_GPIO_Port GPIOA
#define DISPLAY_CLK_Pin GPIO_PIN_3
#define DISPLAY_CLK_GPIO_Port GPIOA
#define DISPLAY_RS_Pin GPIO_PIN_4
#define DISPLAY_RS_GPIO_Port GPIOA
#define DISPLAY_CE_Pin GPIO_PIN_5
#define DISPLAY_CE_GPIO_Port GPIOA
#define DISPLAY_RST_Pin GPIO_PIN_6
#define DISPLAY_RST_GPIO_Port GPIOA
#define V_BAT_IN_Pin GPIO_PIN_7
#define V_BAT_IN_GPIO_Port GPIOA
#define DS3231_EN_Pin GPIO_PIN_8
#define DS3231_EN_GPIO_Port GPIOA
#define DS3231_INT_Pin GPIO_PIN_12
#define DS3231_INT_GPIO_Port GPIOA
#define DS3231_INT_EXTI_IRQn EXTI4_15_IRQn
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define BTN_L_Pin GPIO_PIN_4
#define BTN_L_GPIO_Port GPIOB
#define BTN_L_EXTI_IRQn EXTI4_15_IRQn
#define BTN_R_Pin GPIO_PIN_5
#define BTN_R_GPIO_Port GPIOB
#define BTN_R_EXTI_IRQn EXTI4_15_IRQn

/* USER CODE BEGIN Private defines */
extern I2C_HandleTypeDef hi2c1;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
