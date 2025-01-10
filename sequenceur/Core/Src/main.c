/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include <stdbool.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */


/* SWITCH PINS */

////////////////////////////////////////////////
//////////////////////////////
	//LES COMMANDES//
#define Q1L GPIO_PIN_1
#define Q1L_PORT GPIOC
#define Q2L GPIO_PIN_2
#define Q2L_PORT GPIOC
#define Q3L GPIO_PIN_3
#define Q3L_PORT GPIOC
#define Q1H GPIO_PIN_8
#define Q1H_PORT GPIOA
#define Q2H GPIO_PIN_9
#define Q2H_PORT GPIOA
#define Q3H GPIO_PIN_10
#define Q3H_PORT GPIOA

#define Q1L2 GPIO_PIN_4
#define Q1L2_PORT GPIOB
#define Q2L2 GPIO_PIN_5
#define Q2L2_PORT GPIOB
#define Q3L2 GPIO_PIN_6
#define Q3L2_PORT GPIOB
#define Q1H2 GPIO_PIN_0
#define Q1H2_PORT GPIOA
#define Q2H2 GPIO_PIN_1
#define Q2H2_PORT GPIOA
#define Q3H2 GPIO_PIN_10
#define Q3H2_PORT GPIOB
/////////////////////////////
/* HALL SENSORS PINS */
/////////////////////////////
////ENTREE HALL CARTE --> STM32/////
#define H1 GPIO_PIN_11
#define H1_PORT GPIOA
#define H2 GPIO_PIN_12
#define H2_PORT GPIOA
#define H3 GPIO_PIN_15
#define H3_PORT GPIOA

#define H12 GPIO_PIN_6
#define H12_PORT GPIOC
#define H22 GPIO_PIN_7
#define H22_PORT GPIOC
#define H32 GPIO_PIN_8
#define H32_PORT GPIOC
/////////////////////////////

#define SFD_EXPECTED 0xA000
#define SFD_MASK 0xF000
#define CMD_MASK 0x0F00
#define VALUE_MASK 0x00FE
#define FCS_MASK 0x0001

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t data_received = 0x00;
uint8_t data_to_send = 0x00;
 int a =0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

void All_GPIO_to_0_left();
void Sequence_moteur_horaire_left(uint32_t pwm);
void Sequence_moteur_antihoraire_left(uint32_t pwm);

void All_GPIO_to_0_right();
void Sequence_moteur_horaire_right(uint32_t pwm);
void Sequence_moteur_antihoraire_right(uint32_t pwm);

void process_message(uint16_t message);
bool calculate_fcs(uint8_t cmd, uint8_t value);

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
  MX_TIM1_Init();
  MX_SPI3_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  //Sequence_moteur_antihoraire(2000);



	  //for(uint32_t i = 0; i < 500; i++)
	  {}

     // Ajoutez un délai pour éviter de saturer le bus
 }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_SLAVE;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 3999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 3999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

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
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC1 PC2 PC3 PC4
                           PC5 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC6 PC7 PC8 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA11 PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB4 PB5 PB6 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void Sequence_moteur_horaire_left(uint32_t pwm){


	GPIO_PinState H1_State = HAL_GPIO_ReadPin(H1_PORT, H1);
	GPIO_PinState H2_State = HAL_GPIO_ReadPin(H2_PORT, H2);
	GPIO_PinState H3_State = HAL_GPIO_ReadPin(H3_PORT, H3);


	All_GPIO_to_0_left();

    if(H1_State == GPIO_PIN_SET && H2_State == GPIO_PIN_RESET && H3_State == GPIO_PIN_SET ){ // 1
    	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
        HAL_GPIO_WritePin(Q2L_PORT, Q2L, GPIO_PIN_SET);
    }
    else if( H1_State == GPIO_PIN_SET && H2_State == GPIO_PIN_RESET && H3_State == GPIO_PIN_RESET ){ // 2
    	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
        HAL_GPIO_WritePin(Q3L_PORT, Q3L, GPIO_PIN_SET);
    }
    else if(H1_State == GPIO_PIN_SET && H2_State == GPIO_PIN_SET && H3_State == GPIO_PIN_RESET ){ // 3
    	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm);
        HAL_GPIO_WritePin(Q3L_PORT, Q3L, GPIO_PIN_SET);
    }
    else if(H1_State == GPIO_PIN_RESET && H2_State == GPIO_PIN_SET && H3_State == GPIO_PIN_RESET){ // 4
        HAL_GPIO_WritePin(Q1L_PORT, Q1L, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm);																																																																																																																																																																																																																																																																																																																																																														__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm);
    }
    else if(H1_State == GPIO_PIN_RESET && H2_State == GPIO_PIN_SET && H3_State == GPIO_PIN_SET){ // 5
        HAL_GPIO_WritePin(Q1L_PORT, Q1L, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwm);
    }
    else if(H1_State == GPIO_PIN_RESET && H2_State == GPIO_PIN_RESET && H3_State == GPIO_PIN_SET){ // 6
        HAL_GPIO_WritePin(Q2L_PORT, Q2L, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwm);
    }
}

void Sequence_moteur_horaire_right(uint32_t pwm){


	GPIO_PinState H12_State = HAL_GPIO_ReadPin(H12_PORT, H12);
	GPIO_PinState H22_State = HAL_GPIO_ReadPin(H22_PORT, H22);
	GPIO_PinState H32_State = HAL_GPIO_ReadPin(H32_PORT, H32);


	All_GPIO_to_0_right();

    if(H12_State == GPIO_PIN_SET && H22_State == GPIO_PIN_RESET && H32_State == GPIO_PIN_SET ){ // 1
    	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwm);
        HAL_GPIO_WritePin(Q2L2_PORT, Q2L2, GPIO_PIN_SET);
    }
    else if( H12_State == GPIO_PIN_SET && H22_State == GPIO_PIN_RESET && H32_State == GPIO_PIN_RESET ){ // 2
    	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwm);
        HAL_GPIO_WritePin(Q3L2_PORT, Q3L2, GPIO_PIN_SET);
    }
    else if(H12_State == GPIO_PIN_SET && H22_State == GPIO_PIN_SET && H32_State == GPIO_PIN_RESET ){ // 3
    	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pwm);
        HAL_GPIO_WritePin(Q3L2_PORT, Q3L2, GPIO_PIN_SET);
    }
    else if(H12_State == GPIO_PIN_RESET && H22_State == GPIO_PIN_SET && H32_State == GPIO_PIN_RESET){ // 4
        HAL_GPIO_WritePin(Q1L2_PORT, Q1L2, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pwm);
    }
    else if(H12_State == GPIO_PIN_RESET && H22_State == GPIO_PIN_SET && H32_State == GPIO_PIN_SET){ // 5
        HAL_GPIO_WritePin(Q1L_PORT, Q1L, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwm);
    }
    else if(H12_State == GPIO_PIN_RESET && H22_State == GPIO_PIN_RESET && H32_State == GPIO_PIN_SET){ // 6
        HAL_GPIO_WritePin(Q2L2_PORT, Q2L2, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, pwm);
    }
}

void Sequence_moteur_antihoraire_left(uint32_t pwm){

	GPIO_PinState H1_State = HAL_GPIO_ReadPin(H1_PORT, H1);
	GPIO_PinState H2_State = HAL_GPIO_ReadPin(H2_PORT, H2);
	GPIO_PinState H3_State = HAL_GPIO_ReadPin(H3_PORT, H3);

	All_GPIO_to_0_left();

        if(H3_State == GPIO_PIN_RESET && H1_State == GPIO_PIN_SET && H2_State == GPIO_PIN_SET){
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwm);
            HAL_GPIO_WritePin(Q2L_PORT, Q2L, GPIO_PIN_SET);
        }
        else if(H1_State == GPIO_PIN_RESET && H2_State == GPIO_PIN_RESET && H3_State == GPIO_PIN_SET){
            HAL_GPIO_WritePin(Q3L_PORT, Q3L, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm);
        }

        else if(H3_State == GPIO_PIN_SET && H1_State == GPIO_PIN_RESET && H2_State == GPIO_PIN_SET){
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
            HAL_GPIO_WritePin(Q3L_PORT, Q3L, GPIO_PIN_SET);
        }
        else if(H1_State == GPIO_PIN_SET && H2_State == GPIO_PIN_RESET && H3_State == GPIO_PIN_RESET){
            HAL_GPIO_WritePin(Q1L_PORT, Q1L, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwm);
        }

        else if(H3_State == GPIO_PIN_SET && H1_State == GPIO_PIN_SET && H2_State == GPIO_PIN_RESET){
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm);
            HAL_GPIO_WritePin(Q1L_PORT, Q1L, GPIO_PIN_SET);
        }
        else if(H1_State == GPIO_PIN_RESET && H2_State == GPIO_PIN_SET && H3_State == GPIO_PIN_RESET){
            HAL_GPIO_WritePin(Q2L_PORT, Q2L, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm);
        }
}
void Sequence_moteur_antihoraire_right(uint32_t pwm){

	GPIO_PinState H12_State = HAL_GPIO_ReadPin(H12_PORT, H12);
	GPIO_PinState H22_State = HAL_GPIO_ReadPin(H22_PORT, H22);
	GPIO_PinState H32_State = HAL_GPIO_ReadPin(H32_PORT, H32);

	All_GPIO_to_0_right();

        if(H32_State == GPIO_PIN_RESET && H12_State == GPIO_PIN_SET && H22_State == GPIO_PIN_SET){
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, pwm);
            HAL_GPIO_WritePin(Q2L2_PORT, Q2L2, GPIO_PIN_SET);
        }
        else if(H12_State == GPIO_PIN_RESET && H22_State == GPIO_PIN_RESET && H32_State == GPIO_PIN_SET){
            HAL_GPIO_WritePin(Q3L2_PORT, Q3L2, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pwm);
        }

        else if(H32_State == GPIO_PIN_SET && H12_State == GPIO_PIN_RESET && H22_State == GPIO_PIN_SET){
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwm);
            HAL_GPIO_WritePin(Q3L2_PORT, Q3L2, GPIO_PIN_SET);
        }
        else if(H12_State == GPIO_PIN_SET && H22_State == GPIO_PIN_RESET && H32_State == GPIO_PIN_RESET){
            HAL_GPIO_WritePin(Q1L2_PORT, Q1L2, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, pwm);
        }

        else if(H32_State == GPIO_PIN_SET && H12_State == GPIO_PIN_SET && H22_State == GPIO_PIN_RESET){
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, pwm);
            HAL_GPIO_WritePin(Q1L2_PORT, Q1L2, GPIO_PIN_SET);
        }
        else if(H12_State == GPIO_PIN_RESET && H22_State == GPIO_PIN_SET && H32_State == GPIO_PIN_RESET){
            HAL_GPIO_WritePin(Q2L2_PORT, Q2L2, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwm);
        }
}




void All_GPIO_to_0_left(){
	//permet de reset l'état des GPIO destinés à la ocmmande des ponts H
	HAL_GPIO_WritePin(Q1L_PORT, Q1L, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Q2L_PORT, Q2L, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Q3L_PORT, Q3L, GPIO_PIN_RESET);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
}

void All_GPIO_to_0_right(){
	//permet de reset l'état des GPIO destinés à la ocmmande des ponts H
	HAL_GPIO_WritePin(Q1L2_PORT, Q1L2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Q2L2_PORT, Q2L2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Q3L2_PORT, Q3L2, GPIO_PIN_RESET);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 0);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	Sequence_moteur_horaire_left(2500);
  	for(uint32_t i = 0; i < 50
	; i++)
		  {}
    //Sequence_moteur_antihoraire());
}

bool calculate_fcs(uint8_t cmd, uint8_t value) {
    uint8_t combined = (cmd << 7) | value;
    uint8_t parity = 0;
    while (combined) {
        parity ^= (combined & 1);
        combined >>= 1;
    }
    return (parity & 1);
}

void process_message(uint16_t message) {
    uint16_t sfd = (message & SFD_MASK) >> 12;
    uint8_t cmd = (message & CMD_MASK) >> 8;
    uint8_t value = (message & VALUE_MASK) >> 1;
    bool fcs = (message & FCS_MASK);

    // Vérification du SFD
    if (sfd != (SFD_EXPECTED >> 12)) {
        printf("Erreur : SFD invalide\n");
        return;
    }

    // Vérification du FCS
    if (fcs != calculate_fcs(cmd, value)) {
        printf("Erreur : FCS invalide\n");
        return;
    }

    // Traitement du champ CMD
    switch (cmd) {
        case 0x1: // Marche/Arrêt moteur 1
            printf("Commande : Marche/Arrêt moteur 1, valeur : %d\n", value);
            break;
        case 0x2: // Sens de rotation moteur 1
            printf("Commande : Sens de rotation moteur 1, valeur : %d\n", value);
            break;
        case 0x4: // Configuration fréquence PWM moteur 1
            printf("Commande : Configuration fréquence PWM moteur 1, valeur : %d\n", value);
            break;
        case 0x7: // Configuration vitesse/rapport cyclique moteur 1
            printf("Commande : Configuration vitesse moteur 1, valeur : %d\n", value);
            break;
        case 0x9: // Marche/Arrêt moteur 2
            printf("Commande : Marche/Arrêt moteur 2, valeur : %d\n", value);
            break;
        case 0xA: // Sens de rotation moteur 2
            printf("Commande : Sens de rotation moteur 2, valeur : %d\n", value);
            break;
        case 0xC: // Configuration fréquence PWM moteur 2
            printf("Commande : Configuration fréquence PWM moteur 2, valeur : %d\n", value);
            break;
        case 0xF: // Configuration vitesse/rapport cyclique moteur 2
            printf("Commande : Configuration vitesse moteur 2, valeur : %d\n", value);
            break;
        default:
            printf("Commande inconnue : %d\n", cmd);
            break;
    }
}

int __io_putchar(int ch){
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch,1,0xFFFF);
	return ch;
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi->Instance == SPI3) {
        uint16_t received_data;
        HAL_SPI_Receive(&hspi3, (uint8_t *)&received_data, 1, HAL_MAX_DELAY);
        process_message(received_data);
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
