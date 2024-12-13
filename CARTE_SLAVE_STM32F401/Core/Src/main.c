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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */


/* SWITCH PINS */
#define Q1L GPIO_PIN_1
#define Q1L_PORT GPIOC

#define Q2L GPIO_PIN_2
#define Q2L_PORT GPIOC

#define Q3L GPIO_PIN_3
#define Q3L_PORT GPIOC


/* HALL SENSORS PINS */
#define H1 GPIO_PIN_11
#define H1_PORT GPIOA

#define H2 GPIO_PIN_12
#define H2_PORT GPIOA

#define H3 GPIO_PIN_15
#define H3_PORT GPIOA

#define H1sim GPIO_PIN_12
#define H1sim_PORT GPIOB

#define H2sim GPIO_PIN_13
#define H2sim_PORT GPIOB

#define H3sim GPIO_PIN_14
#define H3sim_PORT GPIOB

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */
 int a =0;
 int sense_rotation_horaire = 0 ;
 int sense_rotation_anti_horaire = 0 ;
 int sense_rotation ;
 volatile uint16_t pulseValueA = 0;
 volatile uint16_t pulseValueB = 0;
 volatile uint16_t pulseValueC = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

void All_GPIO_to_0();
void Sequence_moteur_horaire(uint16_t GPIO_Pin);
void Sequence_moteur_antihoraire(uint16_t GPIO_Pin);
void Simulation_capteurs_Hall();
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
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 Simulation_capteurs_Hall();
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
  htim1.Init.Prescaler = 20;
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
  sConfigOC.Pulse = 1000;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.Pulse = 32768;
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
                          |GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC1 PC2 PC3 PC4
                           PC5 PC7 PC8 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : USART_TX_Pin USART_RX_Pin */
  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PC6 */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA11 PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
  HAL_GPIO_WritePin(H1sim_PORT, H1, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(H2sim_PORT, H2, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(H3sim_PORT, H3, GPIO_PIN_SET);
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void Sequence_moteur_horaire(uint16_t GPIO_Pin){
    GPIO_PinState H1_State = HAL_GPIO_ReadPin(H1_PORT, H1);
    GPIO_PinState H2_State = HAL_GPIO_ReadPin(H2_PORT, H2);
    GPIO_PinState H3_State = HAL_GPIO_ReadPin(H3_PORT, H3);
if (GPIO_Pin == H1) {
    if(H3_State == GPIO_PIN_SET && H1_State == GPIO_PIN_SET && H2_State == GPIO_PIN_RESET){
    	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500);
    	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        HAL_GPIO_WritePin(Q2L_PORT, Q2L, GPIO_PIN_SET);
    }
    else if(H1_State == GPIO_PIN_RESET && H2_State == GPIO_PIN_SET && H3_State == GPIO_PIN_RESET){
        HAL_GPIO_WritePin(Q1L_PORT, Q1L, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 500);
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    }
}
if (GPIO_Pin == H2) {
    if(H3_State == GPIO_PIN_RESET && H1_State == GPIO_PIN_SET && H2_State == GPIO_PIN_SET){
    	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 500);
    	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
        HAL_GPIO_WritePin(Q3L_PORT, Q3L, GPIO_PIN_SET);
    }
    else if(H1_State == GPIO_PIN_RESET && H2_State == GPIO_PIN_RESET && H3_State == GPIO_PIN_SET){
        HAL_GPIO_WritePin(Q2L_PORT, Q2L, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 500);
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    }
}
if (GPIO_Pin == H3){
    if(H3_State == GPIO_PIN_RESET && H1_State == GPIO_PIN_SET && H2_State == GPIO_PIN_RESET){
    	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500);
    	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        HAL_GPIO_WritePin(Q3L_PORT, Q3L, GPIO_PIN_SET);
    }
    else if(H1_State == GPIO_PIN_RESET && H2_State == GPIO_PIN_SET && H3_State == GPIO_PIN_SET){
        HAL_GPIO_WritePin(Q1L_PORT, Q1L, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 500);
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    }
}
}

void Sequence_moteur_antihoraire(uint16_t GPIO_Pin){
    GPIO_PinState H1_State = HAL_GPIO_ReadPin(H1_PORT, H1);
    GPIO_PinState H2_State = HAL_GPIO_ReadPin(H2_PORT, H2);
    GPIO_PinState H3_State = HAL_GPIO_ReadPin(H3_PORT, H3);

    if (GPIO_Pin == H1) {
        if(H3_State == GPIO_PIN_RESET && H1_State == GPIO_PIN_SET && H2_State == GPIO_PIN_SET){
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 500);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
            HAL_GPIO_WritePin(Q2L_PORT, Q2L, GPIO_PIN_SET);
        }
        else if(H1_State == GPIO_PIN_RESET && H2_State == GPIO_PIN_RESET && H3_State == GPIO_PIN_SET){
            HAL_GPIO_WritePin(Q3L_PORT, Q3L, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 500);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
        }
    }
    if (GPIO_Pin == H2) {
        if(H3_State == GPIO_PIN_SET && H1_State == GPIO_PIN_RESET && H2_State == GPIO_PIN_SET){
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
            HAL_GPIO_WritePin(Q3L_PORT, Q3L, GPIO_PIN_SET);
        }
        else if(H1_State == GPIO_PIN_SET && H2_State == GPIO_PIN_RESET && H3_State == GPIO_PIN_RESET){
            HAL_GPIO_WritePin(Q1L_PORT, Q1L, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 500);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
        }
    }
    if (GPIO_Pin == H3) {
        if(H3_State == GPIO_PIN_SET && H1_State == GPIO_PIN_SET && H2_State == GPIO_PIN_RESET){
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
            HAL_GPIO_WritePin(Q1L_PORT, Q1L, GPIO_PIN_SET);
        }
        else if(H1_State == GPIO_PIN_RESET && H2_State == GPIO_PIN_SET && H3_State == GPIO_PIN_RESET){
            HAL_GPIO_WritePin(Q2L_PORT, Q2L, GPIO_PIN_SET);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 500);
            HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
        }
    }
}


void Simulation_capteurs_Hall()
{
	HAL_GPIO_WritePin(H1sim_PORT, H1sim, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(H3sim_PORT, H3sim, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(H2sim_PORT, H2sim, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(H1sim_PORT, H1sim, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(H3sim_PORT, H3sim, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(H2sim_PORT, H2sim, GPIO_PIN_RESET);
	HAL_Delay(10);

}

void All_GPIO_to_0(){
	//permet de reset l'état des GPIO destinés à la ocmmande des ponts H
	HAL_GPIO_WritePin(Q1L_PORT, Q1L, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Q2L_PORT, Q2L, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Q3L_PORT, Q3L, GPIO_PIN_RESET);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
}



void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
    All_GPIO_to_0();
    Sequence_moteur_horaire(GPIO_Pin);
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
