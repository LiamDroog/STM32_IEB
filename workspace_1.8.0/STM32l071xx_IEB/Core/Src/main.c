/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "printf.h"
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
I2C_HandleTypeDef hi2c2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/**
  * @brief I2C Bus Scan
  * @param None
  * @retval None
  */
void scan_i2c2(){
	HAL_StatusTypeDef result;
	uint8_t i =0;

	printf("--------------------\r\n");
	printf("Scanning IEB I2C2...\r\n");

	for (i=0; i<128; i++){
		result = HAL_I2C_IsDeviceReady(&hi2c2, (uint16_t)(i<<1), 2, 2);

		if (result == HAL_OK){
			printf("I2C address found: 0x%X\r\n", (uint16_t)(i<<1));
		}
	}
	printf("I2C Scan Complete\r\n--------------------\r\n");
	HAL_Delay(1000);
}

uint8_t hi2c2_read_register(uint8_t addr, uint16_t register_pointer)
{
    HAL_StatusTypeDef status = HAL_OK;
    uint16_t return_value = 0;

    status = HAL_I2C_Mem_Read(&hi2c2, addr, (uint16_t)register_pointer, I2C_MEMADD_SIZE_8BIT, &return_value, 2, 100);

    /* Check the communication status */
    if(status != HAL_OK)
    {
        // Error handling, for example re-initialization of the I2C peripheral
    	printf("I2C read from 0x%x failed...\r\n", register_pointer );
    }
    else{
    	printf("I2C read from 0x%x was successful!\r\n", register_pointer );
    }
    return return_value;
}

void hi2c2_write_register(uint8_t addr, uint16_t register_pointer, uint8_t register_value)
{
    HAL_StatusTypeDef status;

    status = HAL_I2C_Mem_Write(&hi2c2, addr, (uint16_t)register_pointer, I2C_MEMADD_SIZE_8BIT, register_value, 2, 100);

    /* Check the communication status */
    if(status != HAL_OK)
    {
        // Error handling, for example re-initialization of the I2C peripheral
    	printf("I2C write to 0x%x failed...\r\n", register_pointer );
    }
    else{
    	printf("I2C write was successful\r\n");
    }
}
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
  MX_USART1_UART_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint8_t rtn;
  scan_i2c2();
//  printf("Reading 0x3801 from 0x79; expecting 0xB4\r\n");
//  rtn = hi2c2_read_register(0x79, 0X3801);
//  printf("Read 0x%X from 0x3801 at 0x79\r\n", rtn);
//  printf("Reading 0x3801 from 0x7D; expecting 0xB4\r\n");
//  rtn = hi2c2_read_register(0x7D, 0X3801);
//  printf("Read 0x%X from 0x3801\r\n", rtn);
//
//  printf("\r\nWriting 0xa8 to 0x3801 on 0x78\r\n");
//  hi2c2_write_register(0x79, 0x3801, 0x0A8);
//  printf("Writing 0xa8 to 0x3801 on 0x7C\r\n");
//  hi2c2_write_register(0x7D, 0x3801, 0x0A8);
//
//  printf("Reading 0x3801 from 0x79; expecting 0xA8\r\n");
//  rtn = hi2c2_read_register(0x79, 0X3801);
//  printf("Read 0x%X from 0x3801 at 0x79\r\n", rtn);
//  printf("Reading 0x3801 from 0x7D; expecting 0xa8\r\n");
//  rtn = hi2c2_read_register(0x7D, 0X3801);
//  printf("Read 0x%X from 0x3801\r\n", rtn);


  printf("Reading 0x3004 from 0x79; expecting 0xDF\r\n");
  rtn = hi2c2_read_register(0x79, 0X3004);
  printf("Read 0x%X from 0x3004 at 0x79\r\n", rtn);
  printf("Reading 0x3004 from 0x7D; expecting 0xDF\r\n");
  rtn = hi2c2_read_register(0x7D, 0X3004);
  printf("Read 0x%X from 0x3004\r\n", rtn);


  printf("Reading 0x300B from 0x79; expecting 0x42\r\n");
  rtn = hi2c2_read_register(0x79, 0X300B);
  printf("Read 0x%X from 0x3005 at 0x79\r\n", rtn);
  printf("Reading 0x300B from 0x7D; expecting 0x42\r\n");
  rtn = hi2c2_read_register(0x7D, 0X300B);
  printf("Read 0x%X from 0x300B\r\n", rtn);


  printf("Reading 0x300A from 0x79; expecting 0x56\r\n");
  rtn = hi2c2_read_register(0x79, 0X300A);
  printf("Read 0x%X from 0x300A at 0x79\r\n", rtn);
  printf("Reading 0x300A from 0x7D; expecting 0x56\r\n");
  rtn = hi2c2_read_register(0x7D, 0X300A);
  printf("Read 0x%X from 0x300A\r\n", rtn);
  while (1)
  {
	  HAL_GPIO_TogglePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin);
	  HAL_Delay(100);
//	  HAL_GPIO_TogglePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin);
////	  HAL_Delay(250);
////	  HAL_GPIO_TogglePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin);
//	  printf("Don't Panic!\r\n");
    /* USER CODE END WHILE */

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x00303D5B;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, TEST_OUT1_Pin|TEST_OUT2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : TEST_OUT1_Pin TEST_OUT2_Pin */
  GPIO_InitStruct.Pin = TEST_OUT1_Pin|TEST_OUT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
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
  }
  /* USER CODE END Error_Handler_Debug */
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

