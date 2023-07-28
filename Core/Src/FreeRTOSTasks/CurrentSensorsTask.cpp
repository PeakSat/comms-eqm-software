#include "CurrentSensorsTask.hpp"
#include "ina3221.hpp"
#include "etl/map.h"
#include "etl/string.h"

enum Channels {
    FPGA = 1,
    UHF = 2,
    SBAND = 3
};

char* channel[4] = { " ", "FPGA", "UHF", "SBAND" };

void CurrentSensorsTask::execute() {
    auto error = INA3221::Error::NO_ERRORS;


    INA3221::INA3221 currentSensor = INA3221::INA3221(hi2c1, INA3221::INA3221Config(), error);
//    LOG_ERROR << "error status " << (uint8_t) error << "\b\r";
    if (error != INA3221::Error::NO_ERRORS) {
        LOG_ERROR << "Config problem\b\r";
    }

    while (true) {
        auto currConfig = currentSensor.getConfigRegister();
        if (!currConfig.has_value()) {
//            LOG_DEBUG << "PROBLEM with Config\r\b";
            continue;
        }
//        LOG_DEBUG << "Config " << currConfig.value() << "\r\b";
        for (int i = 2; i <= 2; i++) {
            auto shuntCurrent = currentSensor.getCurrent(i);
            auto shuntVoltage = currentSensor.getShuntVoltage(i);
            auto busVoltage = currentSensor.getBusVoltage(i);
            auto power = currentSensor.getPower(i);
            if (!shuntCurrent.has_value()) {
                LOG_ERROR << "Cannot get voltage\r\b";
                continue;
            }
            Logger::format.precision(Precision);
            LOG_DEBUG << "Channel shunt current\t" << i << " " << channel[i] << ": " << shuntCurrent.value() << " mA ";
//            LOG_DEBUG << "Channel shunt Voltage\t" << i << " " << channel[i] << ": " << shuntVoltage.value() << " mV ";
//            LOG_DEBUG << "Channel bus Voltage\t" << i  << " " << channel[i] << ": " << busVoltage.value() << " mV ";
//            LOG_DEBUG << "Channel power\t\t" << i << " " << channel[i] << ": " << power.value() << " mW \n";
        }

        vTaskDelay(pdMS_TO_TICKS(DelayMs));
    }

}
