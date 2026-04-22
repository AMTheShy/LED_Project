/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdint.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

static Button_t System_Button;
static Led_t System_Led;
static app_t System_App;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  
  /* USER CODE BEGIN 2 */

  Button_Init(&System_Button);
  Led_Init(&System_Led);
  app_Init(&System_App, System_Led);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

      uint32_t now = HAL_GetTick();

      Button_Debounce(&System_Button, now);

      Calculate_Button_Event(&System_Button, now);

      App_Handle_Button_Event(System_Button.currentButtonEvent, &System_App);

      Led_task(&System_Led, now);

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, Led_Output_Pin|LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Button_Input_Pin */
  GPIO_InitStruct.Pin = Button_Input_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Button_Input_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Led_Output_Pin LD2_Pin */
  GPIO_InitStruct.Pin = Led_Output_Pin|LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

static uint8_t Button_ReadRaw(void){

    uint8_t newRawState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

    if (newRawState == GPIO_PIN_SET) {
   
        return 1u;

    }
    else {
    
        return 0u;

    }

}

static void Button_Init(Button_t *btn) {

     btn->rawState = 0u;
     btn->lastDebounceChangeTick = 0u;
     

     btn->stableState = 0u;
     btn->lastStableState = 0u;

     btn->longCLickFired = 0u;
     btn->clickCount = 0u;
     btn->waitingForDoubleClick = 0u;

     btn->stableStatus = BUTTON_STATUS_EVENT_STABLE_RELEASED;
     btn->currentButtonEvent = BUTTON_NULL;

}

static void Led_Init(Led_t* led) {

    led->ledTask = LED_OFF;

    led->ledTaskledSlowFlashTick = 0u;

    led->ledTaskledFastFlashTick = 0u;

}

static void app_Init(app_t* app, Led_t led) {

    app->ledTask = led.ledTask;
 
}

static void Button_Debounce(Button_t* btn, uint32_t now) {

    uint8_t newRawState = Button_ReadRaw();

    if (newRawState != btn->rawState) {

        btn->lastDebounceChangeTick = now;

        btn->rawState = newRawState;

    }

    if (now - btn->lastDebounceChangeTick > DEBOUNCE_MS) {

        if (btn->rawState != btn->stableState) {

            btn->lastStableState = btn->stableState;

            btn->stableState = btn->rawState;

            if (btn->stableState == 1u && btn->lastStableState == 0u) {

                btn->stableStatus = BUTTON_STATUS_EVENT_STABLE_PRESSED;

            }
            else if (btn->stableState == 0u && btn->lastStableState == 1u) {

                btn->stableStatus = BUTTON_STATUS_EVENT_STABLE_RELEASED;

            }



        }



    }

}

static void Calculate_Button_Event(Button_t *btn, uint32_t now) {

    if (btn->stableStatus == BUTTON_STATUS_EVENT_STABLE_PRESSED) {

        if (btn->waitingForDoubleClick) {

            btn->waitingForDoubleClick = 0u;

            btn->currentButtonEvent = BUTTON_DOUBLE_CLICK;
            
        }else {     

                if (!btn->longClickFired) {
                
                    btn->newPressClickTick = now;

                }

            btn->longClickFired = 1u;
                    
        }
            
    }



    if (btn->stableStatus == BUTTON_STATUS_EVENT_STABLE_RELEASED) {

        if (btn->waitingForDoubleClick) {

            if (now - lastPressEventClick >= DOUBLE_CLICK_WINDOW_DURATION) {
            
                btn->waitingForDoubleClick = 0u;

                btn->currentButtonEvent = BUTTON_SHORT_CLICK;

            }

        }
    
        if (now - btn->newPressClickTick >= LONG_CLICK_DURATION) {
        
            btn->longCLickFired = 0u;

            btn->currentButtonEvent = BUTTON_LONG_CLICK;

        }else {

            btn->waitingForDoubleClick = 1u;

            btn->longCLickFired = 0u;

            btn->lastPressEventTick = now;

        }
        
     }
   
}

static void App_Handle_Button_Event(Button_Event_t event, app_t *app) {

    Led_Task_t currentLedTask = app->led.ledTask;

    switch (event) {
    
    case BUTTON_SHORT_CLICK: 

        switch (currentLedTask) {
        
        case LED_ON :

            app->led.ledTask = LED_SLOW_FLASH;
            break;

        case LED_SLOW_FLASH:

            app->led.ledTask = LED_FAST_FLASH;
            break;

        case LED_FAST_FLASH:

            app->led.ledTask = LED_OFF;
            break;

        case LED_OFF:

            app->led.ledTask = LED_ON;
            break;

        default :

            app->led.ledTask = LED_OFF;
            break;
        
        }

        break;

    case BUTTON_LONG_CLICK:

        app->led.ledTask = LED_OFF;

        break;

    case BUTTON_DOUBLE_CLICK:
        
        app->led.ledTask = LED_FAST_FLASH;

        break;

    case BUTTON_NULL:

        app->led.ledTask = LED_OFF;

        break;
    
    default:

        break;
    }


}

static void Led_task(Led_t *led, uint32_t now) {

    Led_Task_t ledTask = led->ledTask;

    switch (ledTask) {
    
    case LED_ON:

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
        break;

    case LED_OFF:

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
        break;

    case LED_SLOW_FLASH:

        if (now - led->ledSlowFlashTick >= LED_SLOW_FLASH_PERIOD) {

            led->ledSlowFlashTick = now;
        
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);

        }

        break;

    case LED_FAST_FLASH:

        if (now - led->ledFastFlashTick >= LED_FAST_FLASH_PERIOD) {

            led->ledFastFlashTick = now;

            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);

        }

        break;

    default:

        break;

    }
    
}



    


}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
