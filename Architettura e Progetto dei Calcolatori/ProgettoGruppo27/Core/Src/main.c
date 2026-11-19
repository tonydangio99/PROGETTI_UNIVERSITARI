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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "math.h"
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
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */
uint32_t valore_luce = 0;
uint32_t valore_temperatura = 0;
float temperatura_celsius = 0.0f;
float valore_celsius = 0.0f;

// La variabile "stato" deve essere 'volatile' perché viene modificata asincronamente dall'interrupt
volatile uint8_t stato = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
void ADC_Select_Channel(uint32_t channel);
char Scansiona_Tastierino(void);
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
  MX_ADC1_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

  uint32_t tick_precedente_sensori = 0;
  uint32_t tick_precedente_tastierino = 0;

  char tasto_rilevato = '\0';
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      uint32_t tick_attuale = HAL_GetTick();

      // ====================================================================
      // LETTURA SENSORI OGNI 500ms)
      // ====================================================================
      if (tick_attuale - tick_precedente_sensori >= 500)
      {
          tick_precedente_sensori = tick_attuale;

          //Lettura del fotoresistore (Canale 2 su PA1)
          ADC_Select_Channel(ADC_CHANNEL_2);
          HAL_ADC_Start(&hadc1);
          HAL_ADC_PollForConversion(&hadc1, 10);
          valore_luce = HAL_ADC_GetValue(&hadc1);
          HAL_ADC_Stop(&hadc1);

          //Lettura del sensore di temperatura (Canale 3 su PA2)
          ADC_Select_Channel(ADC_CHANNEL_3);
          HAL_ADC_Start(&hadc1);
          HAL_ADC_PollForConversion(&hadc1, 10);
          valore_temperatura = HAL_ADC_GetValue(&hadc1);
          HAL_ADC_Stop(&hadc1);

          //Conversione della temperatura
          if (valore_temperatura > 0 && valore_temperatura < 4095)
          {
              float resistenza = 47000.0f * ((float)valore_temperatura / (4095.0f - (float)valore_temperatura));
              float log_resistenza = logf(resistenza / 10000.0f);
              float kelvin = 1.0f / ((1.0f / 298.15f) + (log_resistenza / 3950.0f));
              temperatura_celsius = kelvin - 273.15f;
          }
          else if (valore_temperatura == 0)
          {
              temperatura_celsius = 999.0f; // Errore sensore
          }
          else
          {
              temperatura_celsius = -273.15f; // Cavo scollegato
          }
      }

      // ====================================================================
      // GESTIONE AUTOMATICA (MOD 0)
      // ====================================================================
      if (stato == 0)
      {
          // Controllo LED basato sulla luce
          if (valore_luce > 1500)
          {
              HAL_GPIO_WritePin(GPIOE, LED_mod_notte_Pin, GPIO_PIN_SET);        // LED Nord Acceso (Spia Buio)
              HAL_GPIO_WritePin(GPIOE, LED_mod_giorno_1_Pin, GPIO_PIN_RESET);  // LED Sud Spento
              HAL_GPIO_WritePin(GPIOE, LED_mod_giorno_2_Pin, GPIO_PIN_RESET);  // LED Sud-Est Spento
              HAL_GPIO_WritePin(GPIOE, LED_mod_giorno_3_Pin, GPIO_PIN_RESET);  // LED Sud-Ovest Spento
          }
          else
          {
              HAL_GPIO_WritePin(GPIOE, LED_mod_notte_Pin, GPIO_PIN_RESET);     // LED Nord Spento
              HAL_GPIO_WritePin(GPIOE, LED_mod_giorno_1_Pin, GPIO_PIN_SET);    // LED Sud Acceso
              HAL_GPIO_WritePin(GPIOE, LED_mod_giorno_2_Pin, GPIO_PIN_SET);    // LED Sud-Est Acceso
              HAL_GPIO_WritePin(GPIOE, LED_mod_giorno_3_Pin, GPIO_PIN_SET);    // LED Sud-Ovest Acceso
          }

          // Controllo Climatizzazione basato sulla temperatura
          if (temperatura_celsius > 0 && temperatura_celsius < 27)
          {
              __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 200);   // Riscaldamento ON (Servo a 180°)
          }
          else if (temperatura_celsius > 30)
          {
              __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 100);   // Raffrescamento ON (Servo a 0°)
          }
      }
      // ====================================================================
      // GESTIONE MANUALE (MOD 1)
      // ====================================================================
      else
      {
          // Scansiona il tastierino ogni 50ms
          if (tick_attuale - tick_precedente_tastierino >= 50)
          {
              tick_precedente_tastierino = tick_attuale;
              tasto_rilevato = Scansiona_Tastierino();

              if (tasto_rilevato != '\0')
              {
                  switch (tasto_rilevato)
                  {
                      case '1': // Accende/Spegne LED Nord
                          HAL_GPIO_TogglePin(GPIOE, LED_mod_notte_Pin);
                          break;
                      case '2': // Accende/Spegne LED Sud
                          HAL_GPIO_TogglePin(GPIOE, LED_mod_giorno_1_Pin);
                          break;
                      case '3': // Accende/Spegne LED Sud-Est
                          HAL_GPIO_TogglePin(GPIOE, LED_mod_giorno_2_Pin);
                          break;
                      case '4': // Accende/Spegne LED Sud-Ovest
                          HAL_GPIO_TogglePin(GPIOE, LED_mod_giorno_3_Pin);
                          break;
                      case '5': // Spegne tutto
                          HAL_GPIO_WritePin(GPIOE, LED_mod_notte_Pin | LED_mod_giorno_1_Pin |
                                                   LED_mod_giorno_2_Pin | LED_mod_giorno_3_Pin, GPIO_PIN_RESET);
                          break;
                      case '6': // Accende tutto
                          HAL_GPIO_WritePin(GPIOE, LED_mod_notte_Pin | LED_mod_giorno_1_Pin |
                                                   LED_mod_giorno_2_Pin | LED_mod_giorno_3_Pin, GPIO_PIN_SET);
                          break;
                      case '7': // accnedi climatizzatore CALDO
                          __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 100);
                          break;
                      case '9': // accendi climatizzatore FREDDO
                          __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 200);
                          break;
                      default:
                          break;
                  }
              }
          }
      }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC12;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_MultiModeTypeDef multimode = {0};
  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc1.Init.LowPowerAutoWait = DISABLE;
  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the ADC multi-mode
  */
  multimode.Mode = ADC_MODE_INDEPENDENT;
  if (HAL_ADCEx_MultiModeConfigChannel(&hadc1, &multimode) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  htim3.Init.Prescaler = 79;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1999;
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
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE(); // Abilita il clock per PORT D

  /*Configure GPIO pin Output Level per tutti i LED utilizzati su GPIOE */
  HAL_GPIO_WritePin(GPIOE, LED_mod_notte_Pin|LED_mod_giorno_1_Pin|LED_mod_giorno_2_Pin|LED_mod_giorno_3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level per le righe del tastierino (Inizializzate a HIGH) */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_SET);

  /*Configure GPIO pin : PA0 (PIN_user_button_Pin) come ingresso con Interrupt (EXTI) */
  GPIO_InitStruct.Pin = PIN_user_button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; // Configurato per scattare sul fronte di salita
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PIN_user_button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins LED su GPIOE : LED_mod_notte_Pin, LED_mod_giorno_1_Pin, LED_mod_giorno_2_Pin, LED_mod_giorno_3_Pin */
  GPIO_InitStruct.Pin = LED_mod_notte_Pin|LED_mod_giorno_1_Pin|LED_mod_giorno_2_Pin|LED_mod_giorno_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins Righe Tastierino su PORT D : PD0, PD1, PD2, PD3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins Colonne Tastierino su PORT D : PD4, PD5, PD6, PD7 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP; // Forza lo stato HIGH quando nessun tasto è premuto
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* Abilitazione dell'interrupt nel controller NVIC */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
/**
  * @brief  Modifica dinamicamente il canale attivo di ADC1.
  * @param  channel: Canale ADC da attivare (es. ADC_CHANNEL_2 o ADC_CHANNEL_3)
  * @retval None
  */
void ADC_Select_Channel(uint32_t channel)
{
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = channel;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief  Esegue la scansione a matrice del tastierino a 16 tasti (4x4).
  *         I pin PD0-PD3 sono righe (Output), PD4-PD7 sono colonne (Input Pull-Up).
  * @retval char: Carattere del tasto premuto, oppure '\0' se nessun tasto è premuto.
  */
char Scansiona_Tastierino(void)
{
    char mappa[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}
    };
    uint16_t righe_pins[4] = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3};
    uint16_t col_pins[4] = {GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7};

    static char ultimo_tasto = '\0';
    char tasto_corrente = '\0';

    // Ripristina tutte le righe a HIGH prima di scansionare
    for (int r = 0; r < 4; r++) {
        HAL_GPIO_WritePin(GPIOD, righe_pins[r], GPIO_PIN_SET);
    }

    for (int r = 0; r < 4; r++)
    {
        // Abbassa la riga corrente a LOW
        HAL_GPIO_WritePin(GPIOD, righe_pins[r], GPIO_PIN_RESET);

        // Breve ritardo software per stabilizzare le capacità parassite delle linee
        for (volatile int i = 0; i < 15; i++);

        for (int c = 0; c < 4; c++)
        {
            // Se la colonna associata scende a LOW, il tasto è premuto
            if (HAL_GPIO_ReadPin(GPIOD, col_pins[c]) == GPIO_PIN_RESET)
            {
                tasto_corrente = mappa[r][c];
            }
        }

        // Riporta la riga corrente a HIGH prima di passare alla prossima
        HAL_GPIO_WritePin(GPIOD, righe_pins[r], GPIO_PIN_SET);
    }

    // Logica Edge-Trigger: restituisce il tasto solo al cambio di stato (pressione singola)
    if (tasto_corrente != ultimo_tasto)
    {
        ultimo_tasto = tasto_corrente;
        return tasto_corrente;
    }

    return '\0';
}

/**
  * @brief  Funzione di Callback eseguita dall'hardware ad ogni interrupt GPIO.
  * @param  GPIO_Pin: Il pin che ha scatenato l'interrupt
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static uint32_t tempo_ultimo_interrupt = 0;
    uint32_t tempo_attuale = HAL_GetTick();

    // Controlla che l'evento sia generato dal pin del pulsante user
    if (GPIO_Pin == PIN_user_button_Pin)
    {
        // Antirimbalzo
        if (tempo_attuale - tempo_ultimo_interrupt > 250)
        {
            stato = !stato; // Inverte lo stato
        }
        tempo_ultimo_interrupt = tempo_attuale;
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
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif /* USER CODE END */
