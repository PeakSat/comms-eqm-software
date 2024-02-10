#include "GNSSTask.hpp"
#include "GNSS.hpp"


void GNSSTask::execute() {
//    taskHandle = xTaskGetCurrentTaskHandle();
    HAL_GPIO_WritePin(P5V_RF_EN_GPIO_Port, P5V_RF_EN_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GNSS_RSTN_GPIO_Port, GNSS_RSTN_Pin, GPIO_PIN_SET);
    GNSSDefinitions::BaudRate baud = GNSSDefinitions::BaudRate::Option115200;
//    auto message = GNSSReceiver::configureNMEAStringInterval()
//    HAL_UART_Transmit(&huart5, message.messageBody.)
//    uint8_t messageTralala[] = { 0xA0, 0xA1, 0x00, 0x07, 0x64, 0x3B, 0x47, 0x47, 0x41, 0x0A, 0x01, 0x1E, 0x0D, 0x0A };

//    HAL_UART_Transmit(&huart5, messageTralala, 11, HAL_MAX_DELAY);
    HAL_UARTEx_ReceiveToIdle_DMA(&huart5, incomingMessage, 512);
    while(true){
        xTaskNotifyWait(0, 0, nullptr, portMAX_DELAY);

        uint8_t found_dollar = 0;
        etl::string<512> GNSSMessage = {};
        for (uint8_t  byte : incomingMessage) {
            GNSSMessage.push_back(byte);
        }
        LOG_DEBUG << GNSSMessage.c_str() << "\n";
        new(&(incomingMessage)) uint8_t[512];
    }
}

