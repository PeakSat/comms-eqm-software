#include "GNSSTask.hpp"
#include "GNSS.hpp"

uint8_t GNSSTask::checkTheConnection() {
    //GNSSMessage gnssMessage;
    //gnssMessage = gnssReceiver.querySoftwareVersion(GNSSDefinitions::SoftwareType::Reserved);
    LOG_DEBUG << "message that will be transmitted " ;

    /*for(int i = 0 ; i < gnssMessage.messageBody.size(); i++)
        LOG_DEBUG << gnssMessage.messageBody[i];
*/
//    HAL_UART_Transmit(&huart5, gnssMessage.messageBody.data(),gnssMessage.messageBody.size(), 1000);
    uint8_t tx_data[] = {0xA0, 0xA1, 0x00, 0x02, 0x02, 0x00, 0x02, 0x0D, 0x0A};
    for(int i = 0 ; i < 9; i++)
        LOG_DEBUG << tx_data[i];
    HAL_UART_Transmit(&huart5, tx_data,9, 1000);
    return gnssTask->end_of_frame_flag;
}


void GNSSTask::execute() {
    // configure the pins
    HAL_GPIO_WritePin(P5V_RF_EN_GPIO_Port, P5V_RF_EN_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GNSS_RSTN_GPIO_Port, GNSS_RSTN_Pin, GPIO_PIN_SET);
    // disabling the half buffer interrupt

    // variables
    etl::vector<uint8_t, 512> message_copy;
    etl::string<512> message_copy_string;
    taskHandle = xTaskGetCurrentTaskHandle();
    HAL_UARTEx_ReceiveToIdle_DMA(&huart5, gnssTask->rxDmaBuffer.data(), 1024);
    while(true){
        checkTheConnection();
        vTaskDelay(500);
        xTaskNotifyWait(0, 0, nullptr, portMAX_DELAY);
        LOG_DEBUG << "counter = "  << gnssTask->counter;
        LOG_DEBUG << "size = " << gnssTask->dmaRxSize;
        if(gnssTask->dmaRxSize < 40){
            for(uint16_t i = 0 ; i < gnssTask->dmaRxSize ; i++)
            {
//                message_copy.push_back(gnssTask->rxDmaBuffer[i]);
//                message_copy_string.push_back(gnssTask->rxDmaBuffer[i]);
             LOG_DEBUG << gnssTask->rxDmaBuffer[i];
            }
        }

        gnssTask->rxDmaBuffer.clear();
        LOG_DEBUG << message_copy_string.c_str();
        message_copy_string.clear();

    }
}

