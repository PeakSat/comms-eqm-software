#include "FreeRTOSTasks/DummyTask.h"
#include "Task.hpp"
#include "etl/string.h"

extern UART_HandleTypeDef huart4;


void DummyTask::execute() {
    etl::string<7> str("what\n");
    for(;;){
        HAL_GPIO_TogglePin(LED_PE14_GPIO_Port, LED_PE14_Pin);
        HAL_Delay(300);
//        HAL_UART_Transmit(&huart4, reinterpret_cast<const uint8_t *>(str.c_str()), str.length(), HAL_MAX_DELAY);
        LOG_DEBUG << "Hello comms\r\n";
    }
}