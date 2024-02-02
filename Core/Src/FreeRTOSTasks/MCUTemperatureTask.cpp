#include "MCUTemperatureTask.hpp"

void MCUTemperatureTask::execute() {
    #ifdef STM32
    #else
    AFEC0_ConversionStart();
    #endif





    while (true) {
        #ifdef STM32
        if (HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
        {
            /* Calibration Error */
            Error_Handler();
        }
        HAL_ADC_Start(&hadc3);

        HAL_ADC_PollForConversion(&hadc3, timeoutPollForConversion);

        const uint16_t* const ADC_TEMP_3V3_30C =  reinterpret_cast<uint16_t*>(0x1FF1E820);
        const uint16_t* const ADC_TEMP_3V3_110C =  reinterpret_cast<uint16_t*>(0x1FF1E840);
        const float CALIBRATION_REFERENCE_VOLTAGE = 3.3F;

        const float REFERENCE_VOLTAGE = 3.28F; // supplied with Vref+ or VDDA

// scale constants to current reference voltage
        float adcCalTemp30C = static_cast<float>(*ADC_TEMP_3V3_30C) * (REFERENCE_VOLTAGE/CALIBRATION_REFERENCE_VOLTAGE);
        float adcCalTemp110C = static_cast<float>(*ADC_TEMP_3V3_110C) * (REFERENCE_VOLTAGE/CALIBRATION_REFERENCE_VOLTAGE);


        uint16_t adcTempValue = HAL_ADC_GetValue(&hadc3);

        float temperature = (static_cast<float>(adcTempValue) - adcCalTemp30C)/(adcCalTemp110C - adcCalTemp30C) * (110.0F - 30.0F) + 30.0F;
        LOG_DEBUG << "MCU Internal Temperature is " << temperature;

        HAL_ADC_Stop(&hadc3);
        vTaskDelay(pdMS_TO_TICKS(delayMs));

        #else
        AFEC0_ConversionStart();
        vTaskDelay(pdMS_TO_TICKS(1));
        uint16_t ADCconversion = AFEC0_ChannelResultGet(AFEC_CH11);
        float voltageConversion = static_cast<float>(ADCconversion) * PositiveVoltageReference / MaxADCValue;
        const float MCUtemperature =
                (voltageConversion - TypicalVoltageAt25) / TemperatureSensitivity + ReferenceTemperature;
        LOG_DEBUG << "The temperature of the MCU is: " << MCUtemperature << " degrees Celsius";
        CommonParameters::mcuTemperature.setValue(MCUtemperature);
        vTaskDelay(pdMS_TO_TICKS(delayMs));
        #endif

    }
}