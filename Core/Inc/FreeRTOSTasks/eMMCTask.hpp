#pragma once

#include <optional>
#include "Task.hpp"

class eMMCTask : public Task {
private:
    const static inline uint16_t DelayMs = 15000;
    const static inline uint16_t TaskStackDepth = 2000;

    StackType_t taskStack[TaskStackDepth];
public:

    void execute();

    eMMCTask() : Task("eMMC Memory Functions") {}

    void createTask(){
        xTaskCreateStatic(vClassTask<eMMCTask>, this->TaskName,
                          eMMCTask::TaskStackDepth, this, tskIDLE_PRIORITY + 1,
                          this->taskStack, &(this->taskBuffer));
    }
};

inline std::optional<eMMCTask> eMMCTask;
