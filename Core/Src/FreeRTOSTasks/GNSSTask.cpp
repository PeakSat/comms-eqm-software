#include "GNSSTask.hpp"
#include "GNSS.hpp"


void GNSSTask::execute() {
    taskHandle = xTaskGetCurrentTaskHandle();

    HAL_GPIO_WritePin(P5V_RF_EN_GPIO_Port, P5V_RF_EN_Pin, GPIO_PIN_SET);
    auto baudrate = GNSSDefinitions::BaudRate::Option115200;
    GNSSDefinitions::SoftwareType softwareType = GNSSDefinitions::SoftwareType::Reserved;
//    const uint8_t *message = GNSSReceiver::querySoftwareVersion(softwareType);
//    message = GNSSReceiver::setFactoryDefaults();
      uint8_t message[] = {0xA0, 0xA1, 0x00, 0x02, 0x02, 0x00, 0x02, 0x0D, 0x0A};


    while(true){
        auto volatile status = HAL_UART_Transmit(&huart5, message, 9, 1000);

//        xTaskNotifyWait(0, 0, nullptr, portMAX_DELAY);

        uint8_t omg[]  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//        HAL_UART_Transmit(&huart5, message.messageBody.data(), 10, 1000);
//        HAL_Delay(10000);
        status = HAL_UART_Receive(&huart5, incomingMessage, 512, 1000);
        status = HAL_UART_Receive(&huart5, incomingMessage, 512, 1000);
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

