#include "main.h"
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include "DummyTask.h"
#include "at86rf215.hpp"
#include "at86rf215config.hpp"
#include "MCUTemperatureTask.hpp"
#include "MCUTemperatureTask.hpp"
#include "UARTGatekeeperTask.hpp"
#include "TemperatureSensorsTask.hpp"
#include "eMMCTask.hpp"
#include "CurrentSensorsTask.hpp"
#include "GNSSTask.hpp"
#include "CANGatekeeperTask.hpp"
#include "CANTestTask.hpp"
#include "WatchdogTask.hpp"
#include "CurrentSensorsTask.hpp"
#include "TransceiverTask.hpp"
#include "TimeKeepingTask.hpp"
#include "CurrentSensorsTask.hpp"

extern UART_HandleTypeDef huart5;

template<class T>
static void vClassTask(void *pvParameters) {
    (static_cast<T *>(pvParameters))->execute();
}



extern "C" void main_cpp(){
    uartGatekeeperTask.emplace();
    canGatekeeperTask.emplace();
    canTestTask.emplace();
    eMMCTask.emplace();
    watchdogTask.emplace();
    transceiverTask.emplace();
    mcuTemperatureTask.emplace();
    temperatureSensorsTask.emplace();
    gnssTask.emplace();
    timeKeepingTask.emplace();
    currentSensorsTask.emplace();

    watchdogTask->createTask();
    uartGatekeeperTask->createTask();
    canGatekeeperTask->createTask();
    canTestTask->createTask();
    transceiverTask->createTask();
    eMMCTask->createTask();
    temperatureSensorsTask->createTask();
    mcuTemperatureTask->createTask();
    gnssTask->createTask();
    timeKeepingTask->createTask();
//    currentSensorsTask->createTask();


    vTaskStartScheduler();

    for(;;);
    return;
}

extern "C" [[maybe_unused]] void EXTI1_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(RF_IRQ_Pin);
    transceiverTask->transceiver.handle_irq();
}


extern "C" void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET) {
        /* Retreive Rx messages from RX FIFO0 */

        if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &CAN::rxHeader0, CAN::rxFifo0.data()) != HAL_OK) {
            /* Reception Error */
            Error_Handler();
        }
//        canGatekeeperTask->switchActiveBus(CAN::Main);
        CAN::rxFifo0.repair();
        CAN::Frame newFrame = CAN::getFrame(&CAN::rxFifo0, CAN::rxHeader0.Identifier);
        if(CAN::rxFifo0[0] >> 6 == CAN::TPProtocol::Frame::Single){
            canGatekeeperTask->addSFToIncoming(newFrame);
            xTaskNotifyFromISR(canGatekeeperTask->taskHandle, 0, eNoAction, &xHigherPriorityTaskWoken);

        }else{
            canGatekeeperTask->addMFToIncoming(newFrame);
            if(CAN::rxFifo0[0] >> 6 == CAN::TPProtocol::Frame::Final){
                xTaskNotifyFromISR(canGatekeeperTask->taskHandle, 0, eNoAction, &xHigherPriorityTaskWoken);
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }

        if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK) {
            /* Notification Error */
            Error_Handler();
        }
    }
}

extern "C" void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if ((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != RESET) {
        /* Retreive Rx messages from RX FIFO1 */
        if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO1, &CAN::rxHeader1, CAN::rxFifo1.data()) != HAL_OK) {
            /* Reception Error */
            Error_Handler();
        }
//        canGatekeeperTask->switchActiveBus(CAN::Redundant);
        CAN::rxFifo1.repair();
        CAN::Frame newFrame = CAN::getFrame(&CAN::rxFifo1, CAN::rxHeader1.Identifier);
        if(CAN::rxFifo0[0] >> 6 == CAN::TPProtocol::Frame::Single){
            canGatekeeperTask->addSFToIncoming(newFrame);
            xTaskNotifyFromISR(canGatekeeperTask->taskHandle, 0, eNoAction, &xHigherPriorityTaskWoken);

        }else{
            canGatekeeperTask->addMFToIncoming(newFrame);
            if(CAN::rxFifo0[0] >> 6 == CAN::TPProtocol::Frame::Final){
                xTaskNotifyFromISR(canGatekeeperTask->taskHandle, 0, eNoAction, &xHigherPriorityTaskWoken);
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }
        }

        if (HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO1_NEW_MESSAGE, 0) != HAL_OK) {
            /* Notification Error */
            Error_Handler();
        }
    }
}



extern "C" void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    // Size is used for copying the correct size of data to the TcCommand buffer,
    // of the TC Handling Task
    BaseType_t xHigherPriorityTaskWoken;

    xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(gnssTask->taskHandle, 0, eNoAction,  &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

    // Reset the DMA to receive the next chunk of data
    HAL_UARTEx_ReceiveToIdle_DMA(&huart5, gnssTask->incomingMessage, 512);

}

extern "C" [[maybe_unused]] void UART5_IRQHandler(void) {
    HAL_UART_IRQHandler(&huart5);
}
