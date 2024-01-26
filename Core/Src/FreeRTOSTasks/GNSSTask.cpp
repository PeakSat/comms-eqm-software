#include "GNSSTask.hpp"


void GNSSTask::execute() {
    taskHandle = xTaskGetCurrentTaskHandle();
    while(true){
        xTaskNotifyWait(0, 0, nullptr, portMAX_DELAY);

//        for(uint8_t i = 0 ; i < MaxGNSSMessageSize; i++)
//            incomingMessage.push_back(tcHandlingTask->RxDmaBuffer[i]);
//        tcHandlingTask->RxDmaBuffer.clear();

        // TC Parsing and Execution
//        etl::string<TcCommandSize> cobsDecodedMsg = COBSdecode<TcCommandSize>(TcCommand.data(), tcHandlingTask->incomingMessageSize);
//        uint8_t messageLength = cobsDecodedMsg.size();
//        uint8_t *ecssTCBytes = reinterpret_cast<uint8_t *>(cobsDecodedMsg.data());
//        auto ecssTC = MessageParser::parse(ecssTCBytes, messageLength);
        LOG_DEBUG << incomingMessage.c_str();
//        MessageParser::execute(ecssTC);

        incomingMessage.clear();
    }
}

