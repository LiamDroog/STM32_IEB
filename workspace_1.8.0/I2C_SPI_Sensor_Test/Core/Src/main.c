/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body for I2C_SPI_Sensor_Test project
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
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
// IMPORTANT: printf prints out over UART - Pins PA10, PA9! NEED A USB-SERIAL CONVERTER
// AND TERMINAL TO SEE STATEMENTS!
#include "printf.h"
#include "NAND_m79a.h"
//#include "interface_methods.h"
//#include "arducam_methods.h"
//#include "ArduCAM.h"
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
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI1_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
#define testaddr 0x00
#define testwrite 0x55
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t hi2c2_read_reg_IT(uint8_t addr, uint16_t reg_addr){
	uint8_t RxBuf[2];
	HAL_I2C_Master_Transmit_IT(&hi2c2, (addr<<1)|0x01, reg_addr, sizeof(reg_addr));
}
uint16_t hi2c2_read_register(uint8_t address_pointer, uint16_t register_pointer)
{
    HAL_StatusTypeDef status = HAL_OK;
//    uint16_t return_value = 0;
    uint16_t buf[2];
    buf[0] = (uint16_t *)register_pointer;
    buf[1] = 0x00;
    status = HAL_I2C_Master_Transmit(&hi2c2, ((address_pointer<<1) | 0x01), buf, 1, HAL_MAX_DELAY);

    /* Check the communication status */
    if(status != HAL_OK)
    {
    	printf("I2C transmit failed");
    	return;
    }

    status = HAL_I2C_Master_Receive(&hi2c2, (address_pointer<<1) | 0x01, buf, 2, HAL_MAX_DELAY);

    /* Check the communication status */
//    if(status != HAL_OK)
//    {
//    	printf("I2C Recieve failed");
//    	return;
//    }
    return buf[1];
}

void hi2c2_write_register(uint8_t address_pointer,uint8_t register_pointer, uint16_t register_value)
{
    HAL_StatusTypeDef status = HAL_OK;

    status = HAL_I2C_Mem_Write(&hi2c2, address_pointer<<1, (uint16_t)register_pointer, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&register_value), 2, 100);

    /* Check the communication status */
    if(status != HAL_OK)
    {
        // Error handling, for example re-initialization of the I2C peripheral
    	printf("I2C write to 0x%x failed...\r\n", register_pointer );
    }
}

void scan_i2c(){
	HAL_StatusTypeDef result;
	uint8_t i =0;

	printf("--------------------\r\n");
	printf("Scanning I2C...\r\n");

	for (i=0; i<128; i++){
		result = HAL_I2C_IsDeviceReady(&hi2c2, (uint16_t)(i<<1), 2, 2);

		if (result == HAL_OK){
			printf("I2C address found: 0x%X\r\n", (uint16_t)(i<<1));
		}
	}
	printf("I2C Scan Complete\r\n--------------------\r\n");

}

void test_i2c(){
	    HAL_StatusTypeDef result;
	    uint8_t i;
	    for (i=1; i<128; i++)
	  	{
	  	  result = HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t)(i<<1), 2, 2);

	  	  if (result == HAL_OK)
	  	  {
	  		  printf("I2C address found: 0x%X\r\n", (uint16_t)(i<<1));
	  	  }
	  	}

	    uint8_t reg_ptr = 0x00;
	    uint16_t buffer;
	//    hi2c1_write_register(0x78, reg_ptr, 0x05);

	    // 0xEC is a BME280 I had laying around to test I2C
	    // Upon power up this should be 0x0
	    printf("Reading from 0xF5 on 0xEC\r\n");
	    buffer = hi2c2_read_register(0xEC, 0xF5);
	    printf("Obtained 0x%x\r\n\n", buffer);
	    // write binary 101 to reg
	    printf("\nWriting b101 to 0xF5 on 0xEC\r\n");
	    hi2c2_write_register(0xEC, 0xF5, 0b101);
	    printf("Obtained 0x%x\r\n\n", buffer);
	    // read back to assert it's written properly (redundant; hi2c1_write_register should throw an error if it fails)
	    printf("\nReading from 0xF5 on 0xEC\r\n");
	    buffer = hi2c2_read_register(0xEC, 0xF5);
	    printf("Obtained 0x%x\r\n\n", buffer);
	    // Read test reg for fun
	    printf("\nReading from 0xD0 on 0xEC\r\n");
	    buffer = hi2c2_read_register(0xEC, 0xD0);
	    printf("Obtained 0x%x\r\n\n", buffer);

	    // Try to scan ArduCam chip to no avail :?
	    for (int j=0x3000; j<0x3009; j++){
	    		printf("Reading from 0x%x on 0x79\r\n", j);
	    		buffer = hi2c2_read_register(0x79, j);
	    	    printf("Obtained 0x%x\r\n", buffer);

	    }
}

uint8_t SPI_Write(uint8_t addr, uint8_t data){
	uint8_t txBuf[2] = {(addr | 0x80), data};
	HAL_GPIO_WritePin(GPIO_PB6_GPIO_Port, GPIO_PB6_Pin, GPIO_PIN_RESET);
	uint8_t status = (HAL_SPI_Transmit(&hspi2, txBuf, 2, HAL_MAX_DELAY) == HAL_OK);
	HAL_GPIO_WritePin(GPIO_PB6_GPIO_Port, GPIO_PB6_Pin, GPIO_PIN_SET);

	return status;
}

uint8_t SPI_Read(uint8_t addr, uint8_t *data) {
	uint8_t txBuf[2] = {addr, 0x00};
	uint8_t rxBuf[2];
	HAL_GPIO_WritePin(GPIO_PB6_GPIO_Port, GPIO_PB6_Pin, GPIO_PIN_RESET);
	uint8_t status = (HAL_SPI_TransmitReceive(&hspi2, txBuf, rxBuf, 2, HAL_MAX_DELAY) == HAL_OK);
//	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIO_PB6_GPIO_Port, GPIO_PB6_Pin, GPIO_PIN_SET);
	*data = rxBuf[1];
	return status;
}

void CS_LOW(){
	HAL_GPIO_WritePin(GPIO_PB6_GPIO_Port, GPIO_PB6_Pin, GPIO_PIN_RESET);
}

void CS_HIGH(){
	HAL_GPIO_WritePin(GPIO_PB6_GPIO_Port, GPIO_PB6_Pin, GPIO_PIN_SET);

}
//
//void detect_ov5642(){
//	uint8_t temp=0;
//	CS_LOW();
//	HAL_Delay(100);
//	uint8_t data[2];
//	data[0] = 0x00 | 0x80;
//	data[1] = 0x55;
//	// send spi
//	HAL_SPI_Init(&hspi1);
//	HAL_StatusTypeDef status;
//    char spi_buf[2];
////    status = HAL_SPI_TransmitReceive(&hspi1, &data, (uint8_t *)spi_buf, 2, 100);
//	status = HAL_SPI_Transmit(&hspi1, data, 2, 100);
////    while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
//	if (status == HAL_OK){
//		printf("Transmitted successfully.\r\n");
//	}
//	else{
//		if (status == HAL_TIMEOUT){
//			printf("Connection timed out\r\n");
//		}
//		printf("Transmission failed.\r\n");
//	}
//	status = HAL_SPI_Receive(&hspi1, (uint8_t *)spi_buf, 2, 100);
////    while(HAL_SPI_GetState(&hspi1) != HAL_SPI_STATE_READY);
//	if (status == HAL_OK){
//		printf("Recieved successfully.\r\n");
//	}
//	else{
//		if (status == HAL_TIMEOUT){
//			printf("Connection timed out\r\n");
//		}
//		printf("Receive failed.\r\n");
//	}
//	HAL_Delay(100);
//	CS_HIGH();
//	printf("Received: 0x%x", spi_buf);
//	}


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	// this shouldn't be deleted!

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
  MX_SPI2_Init();
  MX_SPI1_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_Delay(1000);
	printf("\r\n--------\r\n\r\nProject: I2C__SPI_Sensor_Test; V0.1\r\nInitializing UART..\n\rConnected to UART.\r\n");

//	scan_i2c();
//	HAL_I2C_IsDeviceReady(&hi2c2, (uint16_t)(0x78<<1), 2, 2);

	CS_HIGH();
//	printf("Testing SPI Connection\r\n");
//	detect_ov5642();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//	uint8_t data[2];
//	data[0] = 0x00 | 0x80;
//	data[1] = 0x55;
//	// send spi
//	HAL_StatusTypeDef status;
//	uint8_t spi_buf[2];

	uint8_t data;
//    HAL_StatusTypeDef result;
    static const uint8_t addr = 0x3C;
    uint16_t reg = 0x300A;

	NANDReturnType result;
	char helloworld[] = "Hello World";

	while (1)
	{
//		######### SPI RW
//		SPI_Write(0x00, 0x11);
//		HAL_Delay(100);
//		SPI_Read(0x00, &data);6
//		if (data != 0){
//			printf("0x00: 0x%x\r\n", data);
//		}
//		reg = 0x300A;
//		data = hi2c2_read_register(addr, reg);
//		printf("Addr: 0x%x: Reg: 0x%x: Data: 0x%x\r\n", (addr <<1) |0x01, reg, data);
//		reg = 0x300B;
//		data = hi2c2_read_register(addr, reg);
//		printf("Addr: 0x%x: Reg: 0x%x: Data: 0x%x\r\n", (addr <<1) |0x01, reg, data);


		result = NAND_Init(&hspi2);
		if (result == Ret_Success){
			printf("NAND Initialized successfully");
			return;
		}
		printf("NAND is borked :(");

//		  HAL_SPI_DeInit(&hspi2);
//
//		  HAL_SPI_Init(&hspi2);
//		  HAL_SPI_Transmit(&hspi2, (uint8_t *)helloworld, sizeof(helloworld), HAL_MAX_DELAY);
//		  HAL_SPI_DeInit(&hspi2);
//
//		  NAND_Init(&hspi2);


		HAL_Delay(1000);

//		HAL_SPI_Init(&hspi2);
//		for (int i=0x00; i<0x45; i++){
//	        SPI_Read(i, &data);
//	        if (data != 0){
//		        printf("Reading from 0x%x: 0x%x\r\n", i, data);
//	        }
//			HAL_Delay(50);
//		}
		printf("--------\r\n");


//		HAL_SPI_DeInit(&hspi2);
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
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x0000020B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

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
  hi2c2.Init.Timing = 0x2000090E;
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
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

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
  if (HAL_HalfDuplex_Init(&huart1) != HAL_OK)
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD_R_GPIO_Port, LD_R_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ePD1_RESET_Pin|GPIO_PB6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : MFX_IRQ_OUT_Pin */
  GPIO_InitStruct.Pin = MFX_IRQ_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MFX_IRQ_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MFX_WAKEUP_Pin */
  GPIO_InitStruct.Pin = MFX_WAKEUP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MFX_WAKEUP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA2 PA4 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF3_TSC;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD_R_Pin */
  GPIO_InitStruct.Pin = LD_R_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD_R_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF3_TSC;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : ePD1_RESET_Pin GPIO_PB6_Pin */
  GPIO_InitStruct.Pin = ePD1_RESET_Pin|GPIO_PB6_Pin;
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

