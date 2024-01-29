#include "GNSSTask.hpp"
#include "GNSS.hpp"


void GNSSTask::execute() {
    taskHandle = xTaskGetCurrentTaskHandle();
    HAL_GPIO_WritePin(P5V_RF_EN_GPIO_Port, P5V_RF_EN_Pin, GPIO_PIN_SET);
    while(true){
        xTaskNotifyWait(0, 0, nullptr, portMAX_DELAY);

        etl::string<512> GNSSMessage = {};
        for (uint8_t  byte : incomingMessage) {
            GNSSMessage.push_back(byte);
        }
        LOG_DEBUG << GNSSMessage.c_str();

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

