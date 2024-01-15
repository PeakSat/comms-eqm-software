#include "main.h"
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
//#include "DummyTask.h"
//#include "at86rf215.hpp"
//#include "at86rf215config.hpp"
#include "MCUTemperatureTask.hpp"
#include "UARTGatekeeperTask.hpp"
#include "TemperatureSensorsTask.hpp"
#include "eMMCTask.hpp"

extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart3;
extern I2C_HandleTypeDef hi2c2;


template<class T>
static void vClassTask(void *pvParameters) {
    (static_cast<T *>(pvParameters))->execute();
}

void blinkyTask1(void * pvParameters){
    for(;;){
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
        HAL_Delay(50);
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
        HAL_Delay(50);
    }
}

void blinkyTask2(void * pvParameters){
    for(;;){
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
        HAL_Delay(300);
    }
}

//namespace AT86RF215 {
//    AT86RF215 transceiver = AT86RF215(&hspi1, AT86RF215Configuration());
//}

extern "C" void main_cpp(){
    uartGatekeeperTask.emplace();
    mcuTemperatureTask.emplace();
    temperatureSensorsTask.emplace();
    eMMCTask.emplace();


    uartGatekeeperTask->createTask();
    temperatureSensorsTask->createTask();
    mcuTemperatureTask->createTask();
    eMMCTask->createTask();

    vTaskStartScheduler();

    /**
     * Uncomment below and comment above for Led task visualization (for STM32H743)
     */
//    xTaskCreate(blinkyTask1, "blinkyTask 2", 1000, nullptr, tskIDLE_PRIORITY + 1, nullptr);
//    xTaskCreate(blinkyTask2, "blinkyTask 2", 1000, nullptr, tskIDLE_PRIORITY + 1, nullptr);
    for(;;);
    return;
}

/**
 * @brief This function handles EXTI line[15:10] interrupts.
 */
//extern "C" void EXTI15_10_IRQHandler(void) {
//    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_14);
//
//    AT86RF215::transceiver.handle_irq();
//}
