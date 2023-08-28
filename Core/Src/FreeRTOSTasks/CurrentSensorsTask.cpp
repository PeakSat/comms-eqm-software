#include "CurrentSensorsTask.hpp"
#include "ina3221.hpp"
#include "etl/string.h"


void CurrentSensorsTask::execute() {
    char channel[4][6] = { "", "FPGA", "UHF", "SBAND" };
    auto error = INA3221::Error::NO_ERRORS;
    INA3221::INA3221 currentSensor = INA3221::INA3221(hi2c1, INA3221::INA3221Config(), error);
    if (error != INA3221::Error::NO_ERRORS) {
        LOG_ERROR << "Config problem";
    }

    while (true) {
        Logger::format.precision(Precision);
        auto currConfig = currentSensor.getConfigRegister();
        if (!currConfig.has_value()) {
           LOG_DEBUG << "PROBLEM with Config";
            continue;
        }

        // LOG_INFO << "Current config\t" << currConfig.value(); 

        for (int i = 1; i <= 3; i++) {
            auto shuntCurrent = currentSensor.getCurrent(i);
            auto shuntVoltage = currentSensor.getShuntVoltage(i);
            auto busVoltage = currentSensor.getBusVoltage(i);
            auto power = currentSensor.getPower(i);
            
            LOG_DEBUG << "Channel shunt current\t" << i << " " << channel[i] << ": " << shuntCurrent.value() << " mA ";
            LOG_DEBUG << "Channel shunt Voltage\t" << i << " " << channel[i] << ": " << shuntVoltage.value() << " mV ";
            LOG_DEBUG << "Channel bus Voltage\t" << i  << " " << channel[i] << ": " << busVoltage.value() << " mV ";
            LOG_DEBUG << "Channel power\t\t" << i << " " << channel[i] << ": " << power.value() << " mW\n";
        }

        vTaskDelay(pdMS_TO_TICKS(DelayMs));
    }

}
