#include "GNSSTask.hpp"
#include "GNSS.hpp"


void GNSSTask::execute() {
//    taskHandle = xTaskGetCurrentTaskHandle();
    HAL_GPIO_WritePin(P5V_RF_EN_GPIO_Port, P5V_RF_EN_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GNSS_RSTN_GPIO_Port, GNSS_RSTN_Pin, GPIO_PIN_SET);

    auto message = GNSSReceiver::QueryDOPMask();
//    HAL_UART_Transmit(&huart5, message.messageBody.data(), message.messageBody.size(), 500);
    while(true){
        xTaskNotifyWait(0, 0, nullptr, portMAX_DELAY);

        etl::string<512> GNSSMessage = {};
        for (uint8_t  byte : incomingMessage) {
            GNSSMessage.push_back(byte);
        }
        LOG_DEBUG << GNSSMessage.c_str() << "\n\n\n\n";
        new(&(incomingMessage)) uint8_t[256];
//        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

