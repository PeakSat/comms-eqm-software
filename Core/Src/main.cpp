#include "main.h"
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
//#include "DummyTask.h"
#include "TransceiverTask.hpp"
#include "at86rf215config.hpp"
#include "MCUTemperatureTask.hpp"
#include "txUHFTask.hpp"
#include "UARTGatekeeperTask.hpp"
#include "TemperatureSensorsTask.hpp"

extern SPI_HandleTypeDef hspi4;
extern UART_HandleTypeDef huart4;
extern I2C_HandleTypeDef hi2c2;




extern "C" void main_cpp(){
    //uartGatekeeperTask.emplace();
    //mcuTemperatureTask.emplace();
//    temperatureSensorsTask.emplace();
    transceiverTask.emplace();

    //uartGatekeeperTask->createTask();
    //temperatureSensorsTask->createTask();
    //mcuTemperatureTask->createTask();
    transceiverTask->createTask();

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
extern "C" void EXTI1_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(RF_IRQ_Pin);

    TransceiverTask::transceiver.handle_irq();
}
