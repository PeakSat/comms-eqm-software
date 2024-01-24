#include "main.h"
#include "FreeRTOS.h"
#include "list.h"
#include "task.h"
#include "at86rf215.hpp"
#include "at86rf215config.hpp"
#include "MCUTemperatureTask.hpp"
#include "UARTGatekeeperTask.hpp"
#include "TemperatureSensorsTask.hpp"
#include "eMMCTask.hpp"
#include "CANGatekeeperTask.hpp"
#include "CANTestTask.hpp"


extern SPI_HandleTypeDef hspi1;
extern UART_HandleTypeDef huart3;
extern I2C_HandleTypeDef hi2c1;


template<class T>
static void vClassTask(void *pvParameters) {
    (static_cast<T *>(pvParameters))->execute();
}



extern "C" void main_cpp(){
    uartGatekeeperTask.emplace();
    canGatekeeperTask.emplace();
    canTestTask.emplace();
//    mcuTemperatureTask.emplace();
//    temperatureSensorsTask.emplace();
//    eMMCTask.emplace();


    uartGatekeeperTask->createTask();
    canGatekeeperTask->createTask();
    canTestTask->createTask();
//    temperatureSensorsTask->createTask();
//    mcuTemperatureTask->createTask();
//    eMMCTask->createTask();

    vTaskStartScheduler();

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

extern "C" void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET) {
        /* Retreive Rx messages from RX FIFO0 */

        if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &CAN::rxHeader0, CAN::rxFifo0.data()) != HAL_OK) {
            /* Reception Error */
            Error_Handler();
        }
        canGatekeeperTask->switchActiveBus(CAN::Redundant);
        CAN::rxFifo0.repair();
        CAN::Frame newFrame = CAN::getFrame(&CAN::rxFifo0, CAN::rxHeader0.Identifier);
        if(CAN::rxFifo0[0] >> 6 == CAN::TPProtocol::Frame::Single){
            canGatekeeperTask->addSFToIncoming(newFrame);
            xTaskNotifyFromISR(canGatekeeperTask->taskHandle, 0, eNoAction, &xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
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