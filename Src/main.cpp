#include "stm32f446xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"
void SystemClock_Config(void);
void Error_Handler(void);
void GPIO_Init(void);



/* Entry point ---------------------------------------------------------------*/
int main(void)
{

    if(HAL_Init() != HAL_OK){
        Error_Handler();
    }

     SystemClock_Config();

     GPIO_Init();

    for(;;){
        
        GPIO_PinState buttonstate = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);

        //pressed - 0 , not pressed is- 1
        if(buttonstate == GPIO_PIN_RESET){ 
            HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_SET); // pressed- high->led is on
        }
        else{
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); //not pressed- low ->led is off
        }
        
    }

}

void GPIO_Init(void){
    GPIO_InitTypeDef gpio {}; //create a empty struct
     __HAL_RCC_GPIOA_CLK_ENABLE(); //turn on the clock for port A

        gpio.Pin = GPIO_PIN_5; 
        gpio.Mode = GPIO_MODE_OUTPUT_PP;
        gpio.Pull = GPIO_NOPULL;
        gpio.Speed = GPIO_SPEED_FREQ_LOW;

        HAL_GPIO_Init(GPIOA, &gpio);
   
     __HAL_RCC_GPIOC_CLK_ENABLE();

        gpio = {};
        gpio.Pin = GPIO_PIN_13;
        gpio.Mode = GPIO_MODE_INPUT;
        gpio.Pull = GPIO_NOPULL;
        gpio.Speed = GPIO_SPEED_FREQ_LOW;

        HAL_GPIO_Init(GPIOC, &gpio);

}

void SystemClock_Config(void) //comeback to it, not imporant for now.
{
    RCC_OscInitTypeDef RCC_OscInitStruct{};
    RCC_ClkInitTypeDef RCC_ClkInitStruct{};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_NONE;

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

void Error_Handler(){
    __disable_irq();
    for(;;){
        //whatever should show up when there is a error
    }
}