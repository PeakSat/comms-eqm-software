#include "TransceiverTask.hpp"

using namespace AT86RF215;

AT86RF215::At86rf215 TransceiverTask::transceiver = AT86RF215::At86rf215(&hspi4, AT86RF215::AT86RF215Configuration());

uint8_t TransceiverTask::checkTheSPI() {
    uint8_t error_t = 0;
    DevicePartNumber dpn = transceiver.get_part_number(error);
    switch (dpn) {
        case DevicePartNumber::AT86RF215:
            LOG_DEBUG << "Part Number : AT86RF215" ;
            break;
        case DevicePartNumber::AT86RF215IQ:
            LOG_DEBUG << "Part Number : AT86RF215IQ" ;
            break;
        case DevicePartNumber::AT86RF215M:
            LOG_DEBUG << "Part Number : AT86RF215M" ;
            break;
        case DevicePartNumber::AT86RF215_INVALID:
            LOG_DEBUG << "Invalid";
            error_t = 1;
            break;
    }
    if(error != NO_ERRORS){
        error_t = 1;
        switch (error) {
            case FAILED_READING_FROM_REGISTER:
                LOG_DEBUG << "Failed reading from register" ;
                break;
            default:
                LOG_DEBUG << "some other error";
        }
    }
    if(error_t == 1)
        transceiver.chip_reset(error);
    return error_t;
}

TransceiverTask::PacketType TransceiverTask::createRandomPacket(uint16_t length) {
    PacketType packet;
    for (std::size_t i = 0; i < length; i++) {
        packet[i] = i;
    }
    return packet;
}

void TransceiverTask::setConfiguration(uint16_t pllFrequency09, uint8_t pllChannelNumber09) {
    CustomConfig.pllFrequency09 = pllFrequency09;
    CustomConfig.pllChannelNumber09 = pllChannelNumber09;
    CustomConfig.pllChannelMode09 = AT86RF215::PLLChannelMode::FineResolution450;
    CustomConfig.powerAmplifierRampTime09 = AT86RF215::PowerAmplifierRampTime::RF_PARAMP32U;
    CustomConfig.transmitterCutOffFrequency09 = TransmitterCutOffFrequency::RF_FLC80KHZ;
    transceiver.config = CustomConfig;
}

/*
* The frequency cannot be lower than 377000 as specified in section 6.3.2. The frequency range related
* to Fine Resolution Channel Scheme CNM.CM=1 is from 389.5MHz to 510MHz
*/
uint16_t TransceiverTask::calculatePllChannelFrequency09(uint32_t frequency) {
    uint32_t N = (frequency - 377000) * 65536 / 6500;
    return N >> 8;
}

/*
* The frequency cannot be lower than 377000 as specified in section 6.3.2. The frequency range related
* to Fine Resolution Channel Scheme CNM.CM = 1 is from 389.5MHz to 510MHz
*/
uint8_t TransceiverTask::calculatePllChannelNumber09(uint32_t frequency) {
    uint32_t N = (frequency - 377000) * 65536 / 6500;
    return N & 0xFF;
}

void  TransceiverTask::directModConfig(bool enable){
    Error err;
    transceiver.set_direct_modulation(RF09, enable, err);
    uint8_t temp = (transceiver.spi_read_8(BBC0_FSKDM, error)) & 0b11111110;
    // enable direct modulation and pre - emphasis filter
    transceiver.spi_write_8(BBC0_FSKDM, temp | 0b00000011, error);
}

void TransceiverTask::modulationConfig(){
    Error err;
    // BT = 1 , MIDXS = 1, MIDX = 1, MOR = B-FSK
    transceiver.spi_write_8(BBC0_FSKC0, 86, err);
    directModConfig(true);
}

void TransceiverTask::execute() {
    // Turn off the PA for the TX
    //HAL_GPIO_WritePin(RF_RST_GPIO_Port, RF_RST_Pin, GPIO_PIN_SET);
    //
    HAL_GPIO_WritePin(EN_PA_UHF_GPIO_Port, EN_PA_UHF_Pin, GPIO_PIN_SET);
    // Turn off the RX
    HAL_GPIO_WritePin(EN_RX_UHF_GPIO_Port, EN_RX_UHF_Pin, GPIO_PIN_SET);
    // Turn on RF power supply
   //vTaskDelay(pdMS_TO_TICKS(5000));
    HAL_GPIO_WritePin(P5V_RF_EN_GPIO_Port, P5V_RF_EN_Pin, GPIO_PIN_SET);



    while(checkTheSPI() != 0);


    setConfiguration(calculatePllChannelFrequency09(FrequencyUHF), calculatePllChannelNumber09(FrequencyUHF));
    transceiver.chip_reset(error);
    transceiver.setup(error);
    transceiver.spi_write_8(AT86RF215::RegisterAddress::RF09_PADFE, 2 << 6, error);
    uint16_t currentPacketLength = 16;
    PacketType packet = createRandomPacket(currentPacketLength);

    modulationConfig();
    uint8_t option = 0;
    //transceiver.transmitBasebandPacketsRx(AT86RF215::RF09, error);
    HAL_GPIO_WritePin(EN_PA_UHF_GPIO_Port, EN_PA_UHF_Pin, GPIO_PIN_RESET);
    vTaskDelay(pdMS_TO_TICKS(200));
    while(true){

        if(option == 0)
        {
            transceiver.transmitBasebandPacketsTx(AT86RF215::RF09, packet.data(), currentPacketLength, error);
            LOG_DEBUG << "signal transmitted";
            vTaskDelay(pdMS_TO_TICKS(2));
        }
        else{
            for(int i = 0 ; i < 2047; i++)
                if(transceiver.received_packet[i] != 0)
                    LOG_DEBUG <<transceiver.received_packet[i];
            //LOG_DEBUG << transceiver.get_receiver_energy_detection(AT86RF215::RF09, error);
            /*
            if(transceiver.get_rssi(AT86RF215::RF09, error) > min && < max )
            {
                // then read the packet
                if(my packet is mine)
                {
                    // read it and print the packet
                }
                else{
                    // print wrong packet
                }
            }
            else{
                // clear the received packet variable and store this packet to another variable for post processing
            }
            */


        }

    }
}
