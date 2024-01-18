#include "main.h"
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"

#include "UARTGatekeeperTask.hpp"
#include "TemperatureSensorsTask.hpp"
#include "eMMCTask.hpp"
#include "TransceiverTask.hpp"
#include "WatchdogTask.hpp"


extern "C" void main_cpp(){
    uartGatekeeperTask.emplace();
    watchdogTask.emplace();
    transceiverTask.emplace();

    uartGatekeeperTask->createTask();
    watchdogTask->createTask();
    transceiverTask->createTask();

    vTaskStartScheduler();

    for(;;);
    return;
}

/**
 * @brief This function handles EXTI line[15:10] interrupts.
 */
extern "C" void EXTI15_10_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(RF_IRQ_Pin);
    TransceiverTask::transceiver.handle_irq();
}
