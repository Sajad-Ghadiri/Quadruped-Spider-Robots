/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int Motor_Current_Position[4][5] = {{0, 0, 0, 0, 0}, {0, 75, 79, 78, 77}, {0, 120, 125, 120, 118}, {0, 93, 93, 97, 90}}; //Home 
//int Motor_Current_Position[4][5] = {{0, 0, 0, 0, 0}, {0, 90, 95, 60, 60}, {0, 120, 125, 120, 120}, {0, 80, 80, 80, 80}}; //Home_2

int Find_max(int pwm_1, int pwm_2, int pwm_3, int pwm_4)
{
	int max = pwm_1;
	if(max < pwm_2)
		max = pwm_2;
	if(max < pwm_3)
		max = pwm_3;
	if(max < pwm_4)
		max = pwm_4;
	return max;
}
int Find_min(int pwm_1, int pwm_2, int pwm_3, int pwm_4)
{
	int min = pwm_1;
	if(min > pwm_2)
		min = pwm_2;
	if(min > pwm_3)
		min = pwm_3;
	if(min > pwm_4)
		min = pwm_4;
	return min;
}
////////////////////////////////////////////////////////////////////////////////////
void Move_All(int pwm_1, int pwm_2, int pwm_3, int pwm_4, int motor)
{
	int n, max, min;
	max = Find_max(pwm_1, pwm_2, pwm_3, pwm_4);
	min = Find_min(pwm_1, pwm_2, pwm_3, pwm_4);
	switch(motor)
	{
		case 1:
			n = 50;
			for(;n <= max;n++)
			{
				if(pwm_3 >= n)
					htim3.Instance->CCR1 = n;
				if(pwm_1 >= n)
					htim4.Instance->CCR4 = n;
				if(pwm_4 >= n)
					htim4.Instance->CCR1 = n;
				if(pwm_2 >= n)
					htim2.Instance->CCR4 = n;
				HAL_Delay(10);
			}
			break;
		case 2:
			n = 70;
			for(;n <= max;n++)
			{
				if(pwm_3 >= n)
					htim3.Instance->CCR2 = n;
				if(pwm_1 >= n)
					htim3.Instance->CCR4 = n;
				if(pwm_4 >= n)
					htim4.Instance->CCR2 = n;
				if(pwm_2 >= n)
					htim2.Instance->CCR3 = n;
				HAL_Delay(10);
			}
			break;
		case 3:
			/*n = 125;
			for(;n >= min;n--)
			{
				if(pwm_3 <= n)
					htim3.Instance->CCR3 = n;
				if(pwm_1 <= n)
					htim1.Instance->CCR1 = n;
				if(pwm_4 <= n)
					htim4.Instance->CCR3 = n;
				if(pwm_2 <= n)
					htim2.Instance->CCR2 = n;
				HAL_Delay(20);
			}
			break;*/
			n = 45;
			for(;n <= max;n++)
			{
				if(pwm_3 >= n)
					htim3.Instance->CCR3 = n;
				if(pwm_1 >= n)
					htim1.Instance->CCR1 = n;
				if(pwm_4 >= n)
					htim4.Instance->CCR3 = n;
				if(pwm_2 >= n)
					htim2.Instance->CCR2 = n;
				HAL_Delay(10);
			}
			break;
	}
}
////////////////////////////////////////////////////////////////////////////////////
void Move(TIM_HandleTypeDef htim, int timer, int CCR, int pwm, int motor)
{
	int n = Motor_Current_Position[motor][timer];
	if(n <= pwm)
	{
		switch(CCR)
		{
			case 1:
					for(;n <= pwm;n++)
					{
						htim.Instance->CCR1 = n;
						HAL_Delay(10);
					}
					break;
			case 2:
					for(;n <= pwm;n++)
					{
						htim.Instance->CCR2 = n;
						HAL_Delay(10);
					}
					break;
			case 3:
					for(;n <= pwm;n++)
					{
						htim.Instance->CCR3 = n;
						HAL_Delay(10);
					}
					break;
			case 4:
					for(;n <= pwm;n++)
					{
						htim.Instance->CCR4 = n;
						HAL_Delay(10);
					}
					break;
		}
	}
	else
	{
		switch(CCR)
		{
			case 1:
					for(;n >= pwm;n--)
					{
						htim.Instance->CCR1 = n;
						HAL_Delay(10);
					}
					break;
			case 2:
					for(;n >= pwm;n--)
					{
						htim.Instance->CCR2 = n;
						HAL_Delay(10);
					}
					break;
			case 3:
					for(;n >= pwm;n--)
					{
						htim.Instance->CCR3 = n;
						HAL_Delay(10);
					}
					break;
			case 4:
					for(;n >= pwm;n--)
					{
						htim.Instance->CCR4 = n;
						HAL_Delay(10);
					}
					break;
		}
	}
	Motor_Current_Position[motor][timer] = pwm;
}
////////////////////////////////////////////////////////////////////////////////////
void Home()
{
	HAL_Delay(2000);
	Move_All(79, 75, 77, 78, 1);
	Move_All(125, 120, 118, 120, 2);
	Move_All(93, 93, 90, 90, 3); 
	HAL_Delay(1000);
}
////////////////////////////////////////////////////////////////////////////////////
void Forward(int count)
{
	for(int i = 1;i <= count;i++)
	{
		///////////////////////////
		Move(htim4, 4, 2, 105, 2); 
		Move(htim4, 4, 3, 75, 3);  
		Move(htim3, 3, 2, 100, 2);
		Move(htim3, 3, 1, 100, 1);
		Move(htim3, 3, 2, 120, 2);
		Move(htim4, 4, 2, 118, 2); 
		Move(htim4, 4, 3, 90, 3); 
		Move(htim1, 1, 2, 115, 2); 
		Move(htim1, 1, 1, 85, 3);  
		Move(htim3, 3, 1, 75,1);
		Move(htim1, 1, 2, 120, 2); 
		Move(htim1, 1, 1, 93, 3); 
		HAL_Delay(300);
		///////////////////////////  
		Move(htim1, 1, 2, 110, 2);
		Move(htim1, 1, 1, 79, 3);
		Move(htim2, 2, 3, 105, 2);
		Move(htim2, 2, 4, 54, 1);
		Move(htim2, 2, 3, 125, 2);
		Move(htim1, 1, 2, 120, 2);
		Move(htim1, 1, 1, 93, 3);
		Move(htim4, 4, 2, 113, 2); 
		Move(htim4, 4, 3, 82, 3);
		Move(htim2, 2, 4, 79, 1);
		Move(htim4, 4, 2, 118, 2); 
		Move(htim4, 4, 3, 90, 3);
		HAL_Delay(300);
	}
}
void Backward(int count)
{
	for(int i = 1;i <= count;i++)
	{
		///////////////////////////
		Move(htim4, 4, 2, 105, 2); 
		Move(htim4, 4, 3, 75, 3);  
		Move(htim3, 3, 2, 100, 2);
		Move(htim3, 3, 1, 50, 1);
		Move(htim3, 3, 2, 120, 2);
		Move(htim4, 4, 2, 118, 2); 
		Move(htim4, 4, 3, 90, 3); 
		Move(htim1, 1, 2, 115, 2); 
		Move(htim1, 1, 1, 85, 3);  
		Move(htim3, 3, 1, 75,1);
		Move(htim1, 1, 2, 120, 2); 
		Move(htim1, 1, 1, 93, 3); 
		HAL_Delay(300);
		///////////////////////////  
		Move(htim1, 1, 2, 110, 2);
		Move(htim1, 1, 1, 79, 3);
		Move(htim2, 2, 3, 105, 2);
		Move(htim2, 2, 4, 104, 1);
		Move(htim2, 2, 3, 125, 2);
		Move(htim1, 1, 2, 120, 2);
		Move(htim1, 1, 1, 93, 3);
		Move(htim4, 4, 2, 110, 2); 
		Move(htim4, 4, 3, 74, 3);
		Move(htim2, 2, 4, 79, 1);
		Move(htim4, 4, 2, 118, 2); 
		Move(htim4, 4, 3, 90, 3);
		HAL_Delay(300);
	}
}
////////////////////////////////////////////////////////////////////////////////////
void Turn_Left(int count)
{
	for(int i = 1;i <= count;i++)
	{
		///////////////////////////
		Move(htim4, 4, 2, 105, 2); 
		Move(htim4, 4, 3, 75, 3);  
		Move(htim3, 3, 2, 100, 2);
		Move(htim3, 3, 1, 100, 1);
		Move(htim3, 3, 2, 120, 2);
		Move(htim4, 4, 2, 118, 2); 
		Move(htim4, 4, 3, 90, 3); 
		///////////////////////////
		Move(htim3, 3, 3, 75, 3);
		Move(htim4, 4, 2, 105, 2);
		Move(htim4, 4, 1, 102, 1);
		Move(htim4, 4, 2, 118, 2);
		Move(htim3, 3, 3, 97, 3);
		for(int p = 1;p <= 25;p++)
		{
			htim3.Instance->CCR1 = 100 - p;
			htim4.Instance->CCR1 = 102 - p;
			HAL_Delay(10);
		}
		Motor_Current_Position[1][3] = 75;
		Motor_Current_Position[1][4] = 77;
		HAL_Delay(300);
	}
}
////////////////////////////////////////////////////////////////////////////////////
void Turn_Right(int count)
{
	for(int i = 1;i <= count;i++)
	{
		///////////////////////////
		Move(htim4, 4, 2, 105, 2); 
		Move(htim4, 4, 3, 75, 3);  
		Move(htim3, 3, 2, 100, 2);
		Move(htim3, 3, 1, 50, 1);
		Move(htim3, 3, 2, 120, 2);
		Move(htim4, 4, 2, 118, 2); 
		Move(htim4, 4, 3, 90, 3); 
		///////////////////////////
		Move(htim3, 3, 3, 75, 3);
		Move(htim4, 4, 2, 105, 2);
		Move(htim4, 4, 1, 52, 1);
		Move(htim4, 4, 2, 118, 2);
		Move(htim3, 3, 3, 97, 3);
		for(int p = 1;p <= 25;p++)
		{
			htim3.Instance->CCR1 = 50 + p;
			htim4.Instance->CCR1 = 52 + p;
			HAL_Delay(10);
		}
		Motor_Current_Position[1][3] = 75;
		Motor_Current_Position[1][4] = 77;
		HAL_Delay(300);
	}
}
////////////////////////////////////////////////////////////////////////////////////
/*void Turn_Right()
{
	///////////////////////////
	Move(htim1, 1, 2, 110, 2);
	Move(htim1, 1, 1, 79, 3);
	Move(htim2, 2, 3, 105, 2);
	Move(htim2, 2, 4, 54, 1);
	Move(htim2, 2, 3, 125, 2);
	Move(htim1, 1, 2, 120, 2);
	Move(htim1, 1, 1, 93, 3); 
	HAL_Delay(1000);
	///////////////////////////
	Move(htim4, 4, 1, 70, 1);
	Move(htim2, 2, 2, 75, 3);
	Move(htim1, 1, 2, 110, 2);
	Move(htim1, 1, 3, 50, 1);
	Move(htim1, 1, 2, 120, 2);
	Move(htim2, 2, 2, 93, 3);	
	Move(htim4, 4, 1, 77, 1);
	Move(htim4, 4, 2, 113, 2); 
	Move(htim4, 4, 3, 82, 3);
	for(int p = 1;p <= 25;p++)
	{
		htim1.Instance->CCR3 = 50 + p;
		htim2.Instance->CCR4 = 54 + p;
		HAL_Delay(10);
	}
	Motor_Current_Position[1][1] = 75;
	Motor_Current_Position[1][2] = 79;
	Move(htim4, 4, 2, 118, 2); 
	Move(htim4, 4, 3, 90, 3);
}*/
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
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	////////////////////////////////////////////////////////////// Leg1
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); //A8	=> M3
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);	//B1	=> M2
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4); //B9  => M1
	////////////////////////////////////////////////////////////// Leg2
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);	//A1	=> M3
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3); //A2	=> M2
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);	//A3	=> M1
	////////////////////////////////////////////////////////////// Leg3
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); //A6	=> M1
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);	//A7	=> M2
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3); //B0	=> M3
	////////////////////////////////////////////////////////////// Leg4
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1); //B6	=> M1
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);	//B7	=> M2
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3); //B8	=> M3

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
		Home();
		//Turn_Right(6);
		//Forward(10);
		//Turn_Left(8);
		//Backward(10);
		
while (1)
  {
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
  htim1.Init.Prescaler = 159;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 999;
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
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
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
  htim2.Init.Prescaler = 159;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
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
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 159;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 159;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
