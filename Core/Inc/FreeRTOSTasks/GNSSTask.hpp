#pragma once

#include "Task.hpp"
//#include "minmea.h"
#include "COMMS_Definitions.hpp"
#include "queue.h"

extern DMA_HandleTypeDef hdma_uart5_rx;
extern UART_HandleTypeDef huart5;

class GNSSTask : public Task {
public:
    /**
     * @see ParameterStatisticsService
     */
    void execute();

    const static inline uint16_t TaskStackDepth = 1200;

    StackType_t taskStack[TaskStackDepth];

    /**
* Buffer that holds the data of the DMA
*/
    typedef etl::string<GNSSMessageSize> GNSSMessage;
    uint8_t incomingMessage[256];
//    uint16_t incomingMessageSize = 0;
    /**
     * Queue for incoming messages
     */
    uint8_t messageQueueStorageArea[GNSSQueueSize * sizeof(GNSSMessage)];
    StaticQueue_t gnssQueue;
    QueueHandle_t gnssQueueHandle;

    GNSSTask() : Task("GNSS Logging Task") {
        gnssQueueHandle = xQueueCreateStatic(GNSSQueueSize, sizeof(GNSSMessage),
                                             messageQueueStorageArea,
                                             &gnssQueue);
        configASSERT(gnssQueueHandle);

        // disabling the half buffer interrupt //
        __HAL_DMA_DISABLE_IT(&hdma_uart5_rx, DMA_IT_HT);
        // disabling the full buffer interrupt //
        __HAL_DMA_DISABLE_IT(&hdma_uart5_rx, DMA_IT_TC);
        HAL_UARTEx_ReceiveToIdle_DMA(&huart5, incomingMessage, 256);
    }

    /**
     * Create freeRTOS Task
     */
    void createTask() {
        taskHandle = xTaskCreateStatic(vClassTask < GNSSTask > , this->TaskName,
                          GNSSTask::TaskStackDepth, this, tskIDLE_PRIORITY + 1,
                          this->taskStack, &(this->taskBuffer));
    }
private:

};

inline std::optional<GNSSTask> gnssTask;
