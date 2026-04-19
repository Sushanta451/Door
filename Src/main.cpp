#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_gpio.h"
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

     PIO_Init();

    for(;;){
        
        GPIO_PinState buttonstate = HAL_GPIO_ReadPin(GPIOC, GPIOC_PIN_13);

        if(buttonstate == GPIO_PIN_RESET){
            HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_SET);   ;;
        }
        else{
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
        }
        

    }



}
