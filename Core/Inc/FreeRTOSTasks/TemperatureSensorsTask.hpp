#pragma once

#include <optional>
#include "Task.hpp"
#include "main.h"
#include "CurrentSensorsTask.hpp"

extern I2C_HandleTypeDef hi2c1;

class TemperatureSensorsTask : public Task {
private:
    const static inline uint16_t DelayMs = 1000;
    const static inline uint16_t TaskStackDepth = 2000;
    const static inline uint8_t LoggerPrecision = 2;

    StackType_t taskStack[TaskStackDepth];
public:

    void execute();

    static inline TaskHandle_t temperatureSensorTaskHandle;

    TemperatureSensorsTask() : Task("External Temperature Sensors") {}

    void createTask(){
        temperatureSensorTaskHandle = xTaskCreateStatic(vClassTask<TemperatureSensorsTask>, this->TaskName,
                          TemperatureSensorsTask::TaskStackDepth, this, tskIDLE_PRIORITY + 1,
                          this->taskStack, &(this->taskBuffer));
    }
};

inline std::optional<TemperatureSensorsTask> temperatureSensorsTask;
