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




extern "C" void main_cpp() {
    uartGatekeeperTask.emplace();
//    mcuTemperatureTask.emplace();
//    temperatureSensorsTask.emplace();
    transceiverTask.emplace();

    uartGatekeeperTask->createTask();
    //temperatureSensorsTask->createTask();
    //mcuTemperatureTask->createTask();
    transceiverTask->createTask();

    vTaskStartScheduler();
}
/**
 * @brief This function handles EXTI1 interrupts.
 */
extern "C" [[maybe_unused]] void EXTI1_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(TransceiverIT_Pin);
    transceiverTask->transceiver.handle_irq();
}
