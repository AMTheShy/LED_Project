/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define Button_Input_Pin GPIO_PIN_0
#define Button_Input_GPIO_Port GPIOA
#define Led_Output_Pin GPIO_PIN_1
#define Led_Output_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

#define GPIO_ACTIVE_PIN GPIO_PIN_SET
#define DEBOUNCE_MS 20u
#define LONG_CLICK_DURATION 1500u
#define DOUBLE_CLICK_WINDOW_DURATION 350u


typedef enum {

	BUTTON_STATUS_EVENT_NONE = 0,

	BUTTON_STATUS_EVENT_STABLE_PRESSED,

	BUTTON_STATUS_EVENT_STABLE_RELEASED

}Button_Status_Event_t;

typedef enum {

	BUTTON_SHORT_CLICK = 0,

	BUTTON_LONG_CLICK,

	BUTTON_DOUBLE_CLICK

}Button_Event_t;

typedef enum {

	LED_ON = 0,

	LED_OFF,

	LED_SLOW_FLASH,

	LED_FAST_FLASH

}Led_Task_t;

typedef struct {

	uint8_t rawState;

	uint8_t stableState;
	uint8_t lastStableState;

	uint32_t lastDebounceChangeTick;
	uint32_t lastPressEventTick;

	uint8_t longClickFired;
	uint8_t clickCount;
	uint8_t waitingForRelease;
	uint8_t waitingForDoubleClick;

	Button_Status_Event_t stableStatus;

}Button_t;

typedef struct {

	Led_Task_t ledTask;

}Led_t;

typedef struct {

	led_t led

}app_t;



/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
