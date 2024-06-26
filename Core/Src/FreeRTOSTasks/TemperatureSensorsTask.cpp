#include "TemperatureSensorsTask.hpp"
#include "TMP117.hpp"

void TemperatureSensorsTask::execute() {
    auto config = TMP117::Config();
    etl::vector<TMP117::TMP117, 3> tempSensors = {
            TMP117::TMP117(hi2c1, TMP117::I2CAddress::Address1, config),
            TMP117::TMP117(hi2c1, TMP117::I2CAddress::Address3, config),
            TMP117::TMP117(hi2c1, TMP117::I2CAddress::Address4, config)
    };

    while(true){
        for (TMP117::TMP117 tempSensor : tempSensors) {
            etl::pair<TMP117::Error, float> temperature = tempSensor.getTemperature(true);
            if (temperature.first == TMP117::Error::NoErrors) {
                Logger::format.precision(LoggerPrecision);
                LOG_DEBUG << "Temperature at address " << TMP117::I2CAddress::Address1 << " is " << temperature.second;
                PlatformParameters::commsPCBTemperature1.setValue(temperature.second);
            } else {
                LOG_ERROR << "Error getting temperature";
            }
        }
//        vTaskResume(CurrentSensorsTask::currentSensorTaskHandle);
//        vTaskSuspend(NULL);
//
        vTaskDelay(DelayMs);
    }
}
