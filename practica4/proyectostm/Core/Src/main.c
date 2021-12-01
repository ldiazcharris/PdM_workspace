/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal_uart.h"
#include "API_uart.h"
#include "API_delay.h"
#include "API_debounce.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BOTON GPIO_PIN_1		//Puerto A
#define LED1 GPIO_PIN_2			//Puerto A
#define LED2 GPIO_PIN_3			//Puerto A
#define LED3 GPIO_PIN_4			//Puerto A
#define OK_LED GPIO_PIN_1 		//Puerto B
#define ERROR_LED GPIO_PIN_0	//Puerto B

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */



/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/


/* USER CODE BEGIN PV */

static delay_t delay_led1;
static delay_t delay_led2;
static delay_t delay_led3;
static uint32_t duration_delay_led1 = 100;
static uint32_t duration_delay_led2 = 500;
static uint32_t duration_delay_led3 = 1000;
static uint8_t cont = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void secuencia();
void clearOutput();

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
  delayInit(&delay_led1, duration_delay_led1);
  delayInit(&delay_led2, duration_delay_led2);
  delayInit(&delay_led3, duration_delay_led3);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  if(uartInit())
  {
	  Ok_Handler();
	  uartSendString_direct("\n\r***UART inicialized successfuly***\n\r\n\r");
  }
  else{
	  Error_Handler();
  }


  /* USER CODE BEGIN 2 */



 /* uint8_t prueba[] = "\n\r UART Printf Example: retarget the C library printf function to the UART\n\r";
  uint8_t prueba2[] = "\n\r **Test finished successfully. **\n\r";
  uint8_t mistring[] = "\n\r Hola Mundo \n\r";
  HAL_UART_Transmit(&huart6, prueba, sizeof(prueba)/sizeof(uint8_t), 0xFFF);
  HAL_UART_Transmit(&huart6, prueba, sizeof(prueba2)/sizeof(uint8_t), 0xFFF);
  HAL_UART_Transmit(&huart6, mistring, sizeof(mistring)/sizeof(uint8_t), 0xFFF); */

  uartSendString_direct("LED1: 100 ms\n\r");
  uartSendString_direct("LED1: 500 ms\n\r");
  uartSendString_direct("LED1: 1000 ms\n\r\n\r");

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  secuencia();

	  	  	  if(debounceUpdate(HAL_GPIO_ReadPin(GPIOA, BOTON)) == BUTTON_DOWN && cont == 0){

	  	  		  	duration_delay_led1 = 500;
	  	  			delayWrite(&delay_led1, duration_delay_led1);
	  	  			delayWrite(&delay_led2, duration_delay_led1);
	  	  			delayWrite(&delay_led3, duration_delay_led1);
	  	  		    uartSendString_direct("LED1: 500 ms\n\r");
	  	  			uartSendString_direct("LED1: 500 ms\n\r");
	  	  			uartSendString_direct("LED1: 500 ms\n\r\n\r");
	       			cont = cont+1;
	       			clearOutput();
	  	  	  }

	  	  	  if(debounceUpdate(HAL_GPIO_ReadPin(GPIOA, BOTON)) == BUTTON_DOWN && cont == 1){


	  	  	  		duration_delay_led1 = 100;
	  	  	  		duration_delay_led2 = 500;
	  	  	  		duration_delay_led3 = 1000;
	  	  	  		delayWrite(&delay_led1, duration_delay_led1);
	  	  	  		delayWrite(&delay_led2, duration_delay_led2);
	  	  	  		delayWrite(&delay_led3, duration_delay_led3);
	  	  	  	    uartSendString_direct("LED1: 100 ms\n\r");
	  	  	  	    uartSendString_direct("LED1: 500 ms\n\r");
	  	  	  		uartSendString_direct("LED1: 1000 ms\n\r\n\r");
	  	  	  		cont = 0;
	  	  	  		clearOutput();
	  	  	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

void secuencia()
{

	if (delayRead(&delay_led1)){
		HAL_GPIO_TogglePin(GPIOA, LED1);
	}

	if (delayRead(&delay_led2)){
		HAL_GPIO_TogglePin(GPIOA, LED2);
	}
	if (delayRead(&delay_led3)){
		HAL_GPIO_TogglePin(GPIOA, LED3);
	}

}

void clearOutput()
{
	HAL_GPIO_WritePin(GPIOA, LED1, 0);
	HAL_GPIO_WritePin(GPIOA, LED2, 0);
	HAL_GPIO_WritePin(GPIOA, LED3, 0);

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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}



/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();


  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA3 PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = ERROR_LED | OK_LED;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
	  HAL_GPIO_TogglePin(GPIOB, ERROR_LED);
	  HAL_GPIO_WritePin(GPIOB, OK_LED, 0);
	  HAL_Delay(100);
  }
  /* USER CODE END Error_Handler_Debug */
}

void Ok_Handler(void){
	HAL_GPIO_WritePin(GPIOB, OK_LED, 1);
	HAL_Delay(100);
}

#ifdef  USE_FULL_ASSERT
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
