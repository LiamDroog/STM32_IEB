/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

//██████╗░██████╗░██╗███╗░░██╗████████╗███████╗
//██╔�?�?██╗██╔�?�?██╗██║████╗░██║╚�?�?██╔�?�?�?██╔�?�?�?�?�?
//██████╔�?██████╔�?██║██╔██╗██║░░░██║░░░█████╗░░
//██╔�?�?�?�?░██╔�?�?██╗██║██║╚████║░░░██║░░░██╔�?�?�?░░
//██║░░░░░██║░░██║██║██║░╚███║░░░██║░░░██║░░░░░
//╚�?�?░░░░░╚�?�?░░╚�?�?╚�?�?╚�?�?░░╚�?�?�?░░░╚�?�?░░░╚�?�?░░░░░

// Enable printf sending over USART for ez debug
#include <printf.h>
//#include <nand_m79a.h>
// Currently set to transmit over USART1 (PA9 == TX; connect to USB-UART converter's RX.
//										  PA10 == RX; connect to USB-UART converter's TX)
// Change UART output by modifying lines 118 and 124 in printf.c to the desired HandleTypeDef


// TODO:
//		- look into warning: Printf.c:124:29: passing argument 2 of 'HAL_UART_Transmit' from incompatible pointer type [-Wincompatible-pointer-types]


//
//░█████╗░██╗░░░██╗████████╗██████╗░██╗░░░██╗████████╗  ████████╗███████╗██████╗░███╗░░░███╗██╗███╗░░██╗░█████╗░██╗░░░░░
//██╔�?�?██╗██║░░░██║╚�?�?██╔�?�?�?██╔�?�?██╗██║░░░██║╚�?�?██╔�?�?�?  ╚�?�?██╔�?�?�?██╔�?�?�?�?�?██╔�?�?██╗████╗░████║██║████╗░██║██╔�?�?██╗██║░░░░░
//██║░░██║██║░░░██║░░░██║░░░██████╔�?██║░░░██║░░░██║░░░  ░░░██║░░░█████╗░░██████╔�?██╔████╔██║██║██╔██╗██║███████║██║░░░░░
//██║░░██║██║░░░██║░░░██║░░░██╔�?�?�?�?░██║░░░██║░░░██║░░░  ░░░██║░░░██╔�?�?�?░░██╔�?�?██╗██║╚██╔�?██║██║██║╚████║██╔�?�?██║██║░░░░░
//╚█████╔�?╚██████╔�?░░░██║░░░██║░░░░░╚██████╔�?░░░██║░░░  ░░░██║░░░███████╗██║░░██║██║░╚�?�?░██║██║██║░╚███║██║░░██║███████╗
//░╚�?�?�?�?�?░░╚�?�?�?�?�?�?░░░░╚�?�?░░░╚�?�?░░░░░░╚�?�?�?�?�?�?░░░░╚�?�?░░░  ░░░╚�?�?░░░╚�?�?�?�?�?�?�?╚�?�?░░╚�?�?╚�?�?░░░░░╚�?�?╚�?�?╚�?�?░░╚�?�?�?╚�?�?░░╚�?�?╚�?�?�?�?�?�?�?

/**Can use whatever terminal you like to open a com port to see the uart output. I perfer RealTerm (free, and lightweight)
 * Steps to setting it up:
 * 		- Plug in USB-UART converter
 * 		- Launch Realterm (duh)
 * 		- Under Display tab:
 * 			- Display as Ansi (not ascii)
 * 			- adjust rows to suit your preference
 * 		- Under Port tab:
 * 			-  Change Baud rate to rate specified in ioc file (currently 115200)
 * 				- IMPORTANT: If you're getting weird errors n shit, with gobbledegook coming over the terminal, try halving the baud rate to 57600.
 * 							 Not sure why it works, but it does... You can also change uart to asynchronus and just use the tx pin. That sometimes
 * 							 fixes it as well
 * 			- Parity: None
 * 			- Data Bits: 8 bit
 * 			- Stop bits: 1 bit
 * 			- Port: Dependant on where you plug in the usb-uart converter.
 * 				- Make sure your usb-uart converter is plugged in BEFORE launching Realterm. Otherwise it won't detect it when you do plug it in.
 * 				- Select port which has your converter in it. for FTDI chips, it's usually port #/VPC0 (virtual com port 0). You do need FTDI drivers
 * 				  to run it properly.
 * 			- Click Open. It should open the com port, and you'll be able to see everything coming through as ansi text!
//
//██████╗░██╗░░░██╗███╗░░██╗███╗░░██╗██╗███╗░░██╗░██████╗░
//██╔�?�?██╗██║░░░██║████╗░██║████╗░██║██║████╗░██║██╔�?�?�?�?�?░
//██████╔�?██║░░░██║██╔██╗██║██╔██╗██║██║██╔██╗██║██║░░██╗░
//██╔�?�?██╗██║░░░██║██║╚████║██║╚████║██║██║╚████║██║░░╚██╗
//██║░░██║╚██████╔�?██║░╚███║██║░╚███║██║██║░╚███║╚██████╔�?
//╚�?�?░░╚�?�?░╚�?�?�?�?�?�?░╚�?�?░░╚�?�?�?╚�?�?░░╚�?�?�?╚�?�?╚�?�?░░╚�?�?�?░╚�?�?�?�?�?�?░
 *
 * within the main function, comment / uncomment tests that you want to run within the while loop (~line 440 ish)
 */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define dot_delay_ms 10
#define dash_delay_ms 30
#define word_delay_ms 70
#define letter_delay_ms 30
#define s_delay_ms 10


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
USART_HandleTypeDef husart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/**
  * @brief USART_1 Test Function
  * @param None
  * @retval None
  */
void usart1_test(void){
	printf("Don't Panic! [from IEB :) ]\r\n");
	HAL_Delay(1000);
	return;
}

/**
  * @brief LED_1 Test Function
  * @param None
  * @retval None
  */
void LED_1_test(void){

    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(word_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT1_GPIO_Port, TEST_OUT1_Pin, GPIO_PIN_RESET);
    HAL_Delay(word_delay_ms);
	return;
}

/**
  * @brief LED_2 Test Function
  * @param None
  * @retval None
  */
void LED_2_test(void){

    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(word_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);

    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(s_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dash_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(letter_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_SET);
    HAL_Delay(dot_delay_ms);
    HAL_GPIO_WritePin(TEST_OUT2_GPIO_Port, TEST_OUT2_Pin, GPIO_PIN_RESET);
    HAL_Delay(word_delay_ms);
	return;
}

/**
  * @brief I2C Bus Scan
  * @param None
  * @retval None
  */
void scan_i2c2(){
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
	HAL_Delay(1000);
}

/**
  * @brief SPI Flash Test Function
  * @param None
  * @retval None
  */
void spi_flash_test(void){
//	NANDReturnType result;
//	result = NAND_Init(&hspi2);
//	if (result == Ret_Success){
//		printf("NAND Initialized successfully");
//		return;
//	}
//	printf("NAND is borked :(");
	return;
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
//  HAL_Delay(300);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  MX_USART2_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  Uncomment whichever tests you want to do. These will loop forever until reset, so a HAL_DELAY in each function is reccommended to keep things at a reasonable pace.
//	  Use Ctrl + / to quickly comment/uncomment lines
//	  usart1_test();	// Send a message over UART1 every second
//	  LED_1_test();		// Blink Test LED 1
//	  LED_2_test();		// Blink Test LED 2
//	  scan_i2c2();		// Scan I2C2 (arducam sensors i2c bus) - Needs USART printf output to see results!
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
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
  hi2c1.Init.Timing = 0x00303D5B;
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
  hspi1.Init.Mode = SPI_MODE_SLAVE;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_INPUT;
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
  hspi2.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
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
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  husart2.Instance = USART2;
  husart2.Init.BaudRate = 115200;
  husart2.Init.WordLength = USART_WORDLENGTH_8B;
  husart2.Init.StopBits = USART_STOPBITS_1;
  husart2.Init.Parity = USART_PARITY_NONE;
  husart2.Init.Mode = USART_MODE_TX_RX;
  husart2.Init.CLKPolarity = USART_POLARITY_LOW;
  husart2.Init.CLKPhase = USART_PHASE_1EDGE;
  husart2.Init.CLKLastBit = USART_LASTBIT_DISABLE;
  if (HAL_USART_Init(&husart2) != HAL_OK)
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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, USART2_CS1_Pin|USART2_CS2_Pin|WP__Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, TEST_OUT1_Pin|CAM_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : TEST_IN2_Pin */
  GPIO_InitStruct.Pin = TEST_IN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TEST_IN2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : USART2_CS1_Pin USART2_CS2_Pin WP__Pin */
  GPIO_InitStruct.Pin = USART2_CS1_Pin|USART2_CS2_Pin|WP__Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : TEST_OUT1_Pin CAM_EN_Pin */
  GPIO_InitStruct.Pin = TEST_OUT1_Pin|CAM_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : TEST_OUT2_Pin */
  GPIO_InitStruct.Pin = TEST_OUT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TEST_OUT2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TEST_IN1_Pin */
  GPIO_InitStruct.Pin = TEST_IN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TEST_IN1_GPIO_Port, &GPIO_InitStruct);

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

