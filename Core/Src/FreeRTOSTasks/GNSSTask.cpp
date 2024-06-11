#include "GNSSTask.hpp"
#include "GNSS.hpp"
#include "FreeRTOS.h"
#include "semphr.h"

void GNSSTask::sendDataToGNSS() {
    GNSSMessage gnssMessage;
    gnssMessage = gnssReceiver.configureNMEATalkerID(GNSSDefinitions::TalkerIDType::GPMode,GNSSDefinitions::Attributes::UpdateSRAMandFLASH);
//    gnssMessage = gnssReceiver.configureNMEATalkerID(GNSSDefinitions::TalkerIDType::GNMode,GNSSDefinitions::Attributes::UpdateSRAMandFLASH);
//    gnssMessage = gnssReceiver.setFactoryDefaults();

    LOG_DEBUG << "the message that will be send";
    for(uint8_t byte:gnssMessage.messageBody)
            LOG_DEBUG << byte;
    HAL_UART_Transmit(&huart5, gnssMessage.messageBody.data(),gnssMessage.messageBody.size(), 1000);
//    uint8_t tx_data[] = {0xA0, 0xA1, 0x00, 0x02, 0x02, 0x00, 0x02, 0x0D, 0x0A};
//    uint8_t get_gps_data[] = {0xA0, 0xA1, 0x00, 0x02, 0x30, 0x00, 0x30, 0x0D, 0x0A};
//    uint8_t config_nmea_id[10] = {0xA0,0xA1, 0x00, 0x03, 0x4B, 0x00, 0x01, 0x4A, 0x0D, 0x0A};
//    uint8_t nmea_id_only_sram[9] = {0xA0,0xA1, 0x00, 0x03, 0x4B, 0x10, 0x00, 0x0D, 0x0A};
}


void GNSSTask::execute(){
    // configure the pins
    HAL_GPIO_WritePin(P5V_RF_EN_GPIO_Port, P5V_RF_EN_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GNSS_RSTN_GPIO_Port, GNSS_RSTN_Pin, GPIO_PIN_SET);

    // variables
    uint8_t flag = 0;
    static std::string message;

    __HAL_DMA_DISABLE_IT(&hdma_uart5_rx, DMA_IT_HT);
    // disabling the full buffer interrupt
    __HAL_DMA_DISABLE_IT(&hdma_uart5_rx, DMA_IT_TC);
    HAL_UARTEx_ReceiveToIdle_DMA(&huart5, rxDmaBuffer.data(), 1024);

    vTaskDelay(50);

    while(true){
        vTaskDelay(50);
        if(flag == 0)
            sendDataToGNSS();
        xTaskNotifyWait(0, 0, nullptr, portMAX_DELAY);
        for(uint16_t i = 0 ; i < dmaRxSize; i++){
            if(rxDmaBuffer[i] == 36){
                message.clear();
            }
            if(rxDmaBuffer[i] == 144)
                LOG_DEBUG << "GLONASS EMPHERIS DATA";
            if(rxDmaBuffer[i] == 147)
                LOG_DEBUG << "GNSS NMEA TALKER ID";
            if(rxDmaBuffer[i] == 168)
                LOG_DEBUG << "NAVIGATION DATA";
            if(rxDmaBuffer[i] == 132)
                LOG_DEBUG << "NACK";
            if(rxDmaBuffer[i] == 131)
            {
                LOG_DEBUG << "ACK";
                flag = 1;
            }
            message += rxDmaBuffer[i];
            if(rxDmaBuffer[i] == 10)
                LOG_DEBUG << message;
        }
        rxDmaBuffer.clear();
    }
}




