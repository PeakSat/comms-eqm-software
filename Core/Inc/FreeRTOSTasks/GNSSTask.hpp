#pragma once

#include "Task.hpp"
#include "COMMS_Definitions.hpp"
#include "queue.h"
#include "GNSSDefinitions.hpp"
#include "GNSS.hpp"
#include "GNSSMessage.hpp"

using namespace GNSSDefinitions;

extern DMA_HandleTypeDef hdma_uart5_rx;
extern UART_HandleTypeDef huart5;


class GNSSTask : public Task {
public:
    /**
     * Stack Parameters
    */
    const static inline uint16_t TaskStackDepth = 5000;
    StackType_t taskStack[TaskStackDepth];


    /**
     * objects of necessary classes
     */
    static GNSSReceiver gnssReceiver;

    /**
    * Variables for the Receive Operation from GNSS
    */
    uint16_t dmaRxSize;
    etl::vector<uint8_t, 1024> rxDmaBuffer;
    uint8_t end_of_frame_flag = 0;
    uint16_t counter = 0;


    /**
     * Queue for incoming messages
     */

    /**
     * GNSS Task Constructor
     */
    GNSSTask() : Task("GNSS Logging Task") {
        __HAL_DMA_DISABLE_IT(&hdma_uart5_rx, DMA_IT_HT);
        // disabling the full buffer interrupt
        __HAL_DMA_DISABLE_IT(&hdma_uart5_rx, DMA_IT_TC);
    }
    uint8_t checkTheConnection();
    /**
     * execute
     */
    void execute();
    /**
     * Task Creation
     */
    void createTask() {
        taskHandle = xTaskCreateStatic(vClassTask < GNSSTask > , this->TaskName,
                          GNSSTask::TaskStackDepth, this, tskIDLE_PRIORITY + 1,
                          this->taskStack, &(this->taskBuffer));
    }
private:

};
inline std::optional<GNSSTask> gnssTask;
