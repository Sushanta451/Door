#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"



void SystemClock_Config(void);
void Error_Handler(void);
void GPIO_Init(void);


struct stoplight{
    uint16_t pin;
    uint32_t duration;
};

stoplight seq[]{
    {GPIO_PIN_0,3000},
    {GPIO_PIN_1,1000},
    {GPIO_PIN_4,2000},
};

int size = sizeof(seq)/sizeof(seq[0]);


int main(void)
{
    if (HAL_Init() != HAL_OK)
    {
        Error_Handler();
    }
 
    SystemClock_Config();
    GPIO_Init();

    

    for (;;)
    {   
        for(int i = 0; i < size; i++){
            HAL_GPIO_WritePin(GPIOA , seq[i].pin, GPIO_PIN_SET);
            HAL_Delay(seq[i].duration);
            HAL_GPIO_WritePin(GPIOA , seq[i].pin, GPIO_PIN_RESET);
        }
        
    }
}

void GPIO_Init(void)
{

    GPIO_InitTypeDef gpio{};
    __HAL_RCC_GPIOA_CLK_ENABLE();


    for(int i = 0; i < size; i++){
    gpio.Pin = seq[i].pin;
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA,&gpio);
    }



}

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct{};
    RCC_ClkInitTypeDef RCC_ClkInitStruct{};

    RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_NONE;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType      = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK |
                                       RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}

void Error_Handler(void)
{
    __disable_irq();
    for (;;)
    {
    }
}