#include "TemperatureSensorsTask.hpp"
#include "TMP117.hpp"

void TemperatureSensorsTask::execute() {
    auto config = TMP117::Config();
    etl::vector<TMP117::TMP117, 3> tempSensors = {
            TMP117::TMP117(hi2c1, TMP117::I2CAddress::Address1, config),
            TMP117::TMP117(hi2c1, TMP117::I2CAddress::Address3, config),
            TMP117::TMP117(hi2c1, TMP117::I2CAddress::Address4, config)
    };
    etl::vector<TMP117::I2CAddress, 3> addresses = {
            TMP117::I2CAddress::Address1,
            TMP117::I2CAddress::Address3,
            TMP117::I2CAddress::Address4
    };
    while(true){
        uint8_t i = 0;
        for (TMP117::TMP117 tempSensor : tempSensors) {
            i++;
            etl::pair<TMP117::Error, float> temperature = tempSensor.getTemperature(true);
            if (temperature.first == TMP117::Error::NoErrors) {
                Logger::format.precision(LoggerPrecision);
                LOG_DEBUG << "Temperature at address " << addresses[i] << " is " << temperature.second;
                PlatformParameters::commsPCBTemperature1.setValue(temperature.second);
            } else {
                LOG_ERROR << "Error getting temperature";
            }
        }
        vTaskDelay(pdMS_TO_TICKS(DelayMs));
    }
}
