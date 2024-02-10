#include "FreeRTOSTasks/DummyTask.h"
#include "Task.hpp"
#include <iostream>

void DummyTask::execute() {
    HAL_GPIO_WritePin(P5V_RF_EN_GPIO_Port, P5V_RF_EN_Pin, GPIO_PIN_SET);
    for(;;){
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}