#include "GNSSTask.hpp"
#include "GNSS.hpp"


void GNSSTask::execute() {
    taskHandle = xTaskGetCurrentTaskHandle();

    HAL_GPIO_WritePin(P5V_RF_EN_GPIO_Port, P5V_RF_EN_Pin, GPIO_PIN_SET);

//    auto message = GNSSReceiver::configureMessageType(static_cast<ConfigurationType>(1), static_cast<Attributes>(2));
//    message = GNSSReceiver::setFactoryDefaults();
//    HAL_UART_Transmit(&huart5, message.messageBody.data(), 10, 1000);


    while(true){
//        xTaskNotifyWait(0, 0, nullptr, portMAX_DELAY);

        uint8_t omg[]  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//        HAL_UART_Transmit(&huart5, message.messageBody.data(), 10, 1000);
        HAL_UART_Receive_DMA(&huart5, incomingMessage, 512, 1000);
        etl::string<1000> minima = {};
        for (uint8_t  byte : incomingMessage) {
            minima.push_back(byte);
        }
        LOG_DEBUG << minima.c_str();
//        MessageParser::execute(ecssTC);

//        incomingMessage.clear();

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

