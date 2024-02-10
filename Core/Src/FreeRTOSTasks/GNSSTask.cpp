#include "GNSSTask.hpp"
#include "GNSS.hpp"


void GNSSTask::execute() {
//    taskHandle = xTaskGetCurrentTaskHandle();
    HAL_GPIO_WritePin(P5V_RF_EN_GPIO_Port, P5V_RF_EN_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GNSS_RSTN_GPIO_Port, GNSS_RSTN_Pin, GPIO_PIN_SET);
    GNSSDefinitions::BaudRate baud = GNSSDefinitions::BaudRate::Option115200;
//    auto message = GNSSReceiver::configureSerialPort(0, baud, static_cast<Attributes>(0));
//    HAL_UART_Transmit(&huart5, message.messageBody.)
    HAL_UARTEx_ReceiveToIdle_DMA(&huart5, incomingMessage, 256);
    while(true){
        xTaskNotifyWait(0, 0, nullptr, portMAX_DELAY);

        uint8_t found_dollar = 0;
        etl::string<512> GNSSMessage = {};
        for (uint8_t  byte : incomingMessage) {
            GNSSMessage.push_back(byte);
        }
        LOG_DEBUG << GNSSMessage.c_str() << "\n";
        new(&(incomingMessage)) uint8_t[256];
//        HAL_UARTEx_ReceiveToIdle_DMA(&huart5, gnssTask->incomingMessage, 256);
    }
}

