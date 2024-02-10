#include "GNSS.hpp"
#include "etl/vector.h"

GNSSMessage GNSSReceiver::configureSerialPort(uint8_t COMPort, BaudRate baudRate,
                                              Attributes attributes) {
    Payload payload;
    payload.push_back(COMPort);
    payload.push_back(static_cast<uint8_t>(baudRate));
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessages::ConfigureSerialPort, static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage GNSSReceiver::configureMessageType(ConfigurationType type, Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(type));
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessages::ConfigureMessageType, static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage GNSSReceiver::configureSystemPowerMode(PowerMode mode, Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(mode));
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessages::ConfigurePowerMode, static_cast<uint16_t>(payload.size()), payload};

}

GNSSMessage GNSSReceiver::configureSystemPositionRate(uint8_t rate, Attributes attributes) {
    Payload payload;
    payload.push_back(rate);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessages::ConfigurePositionUpdateRate, static_cast<uint16_t>(payload.size()), payload};

}

GNSSMessage
GNSSReceiver::configureDOPMask(DOPModeSelect mode, uint16_t PDOPvalue, uint16_t HDOPvalue, uint16_t GDOPvalue,
                               Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(mode));
    payload.push_back((PDOPvalue >> 8) & 0xFF);
    payload.push_back(PDOPvalue & 0xFF);
    payload.push_back((HDOPvalue >> 8) & 0xFF);
    payload.push_back(HDOPvalue & 0xFF);
    payload.push_back((GDOPvalue >> 8) & 0xFF);
    payload.push_back(GDOPvalue & 0xFF);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessages::ConfigureDOPMask, static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage
GNSSReceiver::configureElevationAndCNRMask(ElevationAndCNRModeSelect mode, uint8_t elevationMask, uint8_t CNRMask,
                                           Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(mode));
    payload.push_back(elevationMask);
    payload.push_back(CNRMask);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessages::ConfigureElevationAndCNRMask, static_cast<uint16_t>(payload.size()), payload};

}

GNSSMessage GNSSReceiver::configurePositionPinning(PositionPinning positionPinning, Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(positionPinning));
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessages::ConfigurePositionPinning, static_cast<uint16_t>(payload.size()), payload};

}

GNSSMessage
GNSSReceiver::configurePositionPinningParameters(uint16_t pinningSpeed, uint16_t pinningCnt, uint16_t unpiningSpeed,
                                                 uint16_t unpiningCnt, uint16_t unpinningDistance,
                                                 Attributes attributes) {
    Payload payload;
    payload.push_back((pinningSpeed >> 8) & 0xFF);
    payload.push_back(pinningSpeed & 0xFF);
    payload.push_back((pinningCnt >> 8) & 0xFF);
    payload.push_back(pinningCnt & 0xFF);
    payload.push_back((unpiningSpeed >> 8) & 0xFF);
    payload.push_back(unpiningSpeed & 0xFF);
    payload.push_back((unpiningCnt >> 8) & 0xFF);
    payload.push_back(unpiningCnt & 0xFF);
    payload.push_back((unpinningDistance >> 8) & 0xFF);
    payload.push_back(unpinningDistance & 0xFF);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessages::ConfigurePositionPinningParameters, static_cast<uint16_t>(payload.size()),
                       payload};
}

GNSSMessage GNSSReceiver::configure1PPSCableDelay(uint32_t cableDelay, Attributes attributes) {
    Payload payload;
    payload.push_back((cableDelay >> 24) & 0xFF);
    payload.push_back((cableDelay >> 16) & 0xFF);
    payload.push_back((cableDelay >> 8) & 0xFF);
    payload.push_back(cableDelay & 0xFF);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessages::Configure1PPSCableDelay, static_cast<uint16_t>(payload.size()), payload};

}

GNSSMessage GNSSReceiver::configureNMEATalkerID(TalkerIDType type, Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(type));
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessages::ConfigureNMEATalkerID, static_cast<uint16_t>(payload.size()), payload};

}

GNSSMessage
GNSSReceiver::configure1PPSTiming(TimingMode mode, uint16_t surveyLength, uint16_t standardDeviation, uint16_t latitude,
                                  uint16_t longtitude, uint16_t altitude, Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(mode));
    payload.push_back((surveyLength >> 8) & 0xFF);
    payload.push_back(surveyLength & 0xFF);
    payload.push_back((standardDeviation >> 8) & 0xFF);
    payload.push_back(standardDeviation & 0xFF);
    payload.push_back((latitude >> 8) & 0xFF);
    payload.push_back(latitude & 0xFF);
    payload.push_back((longtitude >> 8) & 0xFF);
    payload.push_back(longtitude & 0xFF);
    payload.push_back((altitude >> 8) & 0xFF);
    payload.push_back(altitude & 0xFF);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessages::Configure1PPSTiming, static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage GNSSReceiver::configure1PPSOutputMode(OutputMode mode, AlignSource source, Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(mode));
    payload.push_back(static_cast<uint8_t>(source));
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessages::Configure1PPSOutputMode, static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage
GNSSReceiver::configureSBAS(EnableSBAS enable, RangingSBAS ranging, uint8_t URAMask, CorrectionSBAS correction,
                            uint8_t numberOfTrackingChannels, uint8_t subsystemMask, Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(enable));
    payload.push_back(static_cast<uint8_t>(ranging));
    payload.push_back(URAMask);
    payload.push_back(static_cast<uint8_t>(correction));
    payload.push_back(numberOfTrackingChannels);
    payload.push_back(subsystemMask);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigureSBAS , static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage GNSSReceiver::configureQZSS(EnableQZSS enable, uint8_t noOfTrackingChannels, Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(enable));
    payload.push_back(noOfTrackingChannels);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigureQZSS, static_cast<uint16_t>(payload.size()), payload};

}

GNSSMessage GNSSReceiver::configureSBASAdvanced(EnableSBAS enable, RangingSBAS ranging, uint8_t rangingURAMask,
                                                CorrectionSBAS correction, uint8_t numTrackingChannels,
                                                uint8_t subsystemMask, uint8_t waasPRN, uint8_t egnosPRN,
                                                uint8_t msasPRN, uint8_t gaganPRN, uint8_t sdcmPRN, uint8_t bdsbasPRN,
                                                uint8_t southpanPRN, uint8_t attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(enable));
    payload.push_back(static_cast<uint8_t>(ranging));
    payload.push_back(rangingURAMask);
    payload.push_back(static_cast<uint8_t>(correction));
    payload.push_back(numTrackingChannels);
    payload.push_back(subsystemMask);
    payload.push_back(waasPRN);
    payload.push_back(egnosPRN);
    payload.push_back(msasPRN);
    payload.push_back(gaganPRN);
    payload.push_back(sdcmPRN);
    payload.push_back(bdsbasPRN);
    payload.push_back(southpanPRN);
    payload.push_back(attributes);
    return GNSSMessage{GNSSMessagesSubID::ConfigureSBASAdvanced, static_cast<uint16_t>(payload.size()), payload};

}

GNSSMessage GNSSReceiver::configureSAEE(EnableSAEE enable, Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(enable));
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigureSAEE, static_cast<uint16_t>(payload.size()), payload};

}

GNSSMessage
GNSSReceiver::configureExtendedNMEAMesaageInterval(const etl::vector<uint8_t, 12>& intervals, Attributes attributes) {
    Payload payload;
    for (uint8_t interval: intervals) {
        payload.push_back(interval);
    }
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigureExtendedNMEAMessageInterval, static_cast<uint16_t>(payload.size()),
                       payload};

}

GNSSMessage GNSSReceiver::configureInterferenceDetection(InterferenceDetectControl control, Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(control));
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigureInterferenceDetection, static_cast<uint16_t>(payload.size()),
                       payload};

}

GNSSMessage GNSSReceiver::configurePositionFixNavigationMap(FirstFixNavigationMask firstFix,
                                                            SubsequentFixNavigationMask subsequentFix,
                                                            Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(firstFix));
    payload.push_back(static_cast<uint8_t>(subsequentFix));
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigurePositionFixNavigationMask, static_cast<uint16_t>(payload.size()),
                       payload};
}

GNSSMessage
GNSSReceiver::configureUTCReferenceTimeSyncToGPSTime(EnableSyncToGPSTime enable, uint16_t utcYear, uint8_t utcMonth,
                                                     uint8_t utcDay, Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(enable));
    payload.push_back((utcYear >> 8) & 0xFF);
    payload.push_back(utcYear & 0xFF);
    payload.push_back(utcMonth);
    payload.push_back(utcDay);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigureUTCReferenceTimeSyncToGPSTime, static_cast<uint16_t>(payload.size()),
                       payload};
}

GNSSMessage GNSSReceiver::configureGNSSNavigationMode(NavigationMode mode, Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(mode));
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigureGNSSNavigationMode, static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage
GNSSReceiver::configureGNSSConstellationTypeForNavigationSolution(uint8_t constellationType, Attributes attributes) {
    Payload payload;
    payload.push_back(0x00);
    payload.push_back(constellationType);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigureGNSSConstellationTypeForNavigationSolution,
                       static_cast<uint16_t>(payload.size()), payload};

}

GNSSMessage
GNSSReceiver::SoftwareImageDownloadUsingROMExternalLoader(BaudRate baud, FlashType flashType, uint16_t flashID,
                                                          BufferUsedIndex bufferUsedIndex, Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(baud));
    payload.push_back(static_cast<uint8_t>(flashType));
    payload.push_back((flashID >> 8) & 0xFF);
    payload.push_back(flashID & 0xFF);
    payload.push_back(static_cast<uint8_t>(bufferUsedIndex));
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::SoftwareImageDownloadUsingROMExternalLoader,
                       static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage GNSSReceiver::configureGNSSDozeMode() {
    return GNSSMessage{GNSSMessagesSubID::ConfigureGNSSDozeMode, 0, {}};

}

GNSSMessage GNSSReceiver::configurePSTIMessageInterval(uint8_t PSTI_ID, uint8_t interval, Attributes attributes) {
    Payload payload;
    payload.push_back(PSTI_ID);
    payload.push_back(interval);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigurePSTIMessageInterval, static_cast<uint16_t>(payload.size()),
                       payload};

}

GNSSMessage GNSSReceiver::configureGNSSDatumIndex(uint16_t datumIndex, Attributes attributes) {
    Payload payload;
    payload.push_back((datumIndex >> 8) & 0xFF);
    payload.push_back(datumIndex & 0xFF);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigureGNSSDatumIndex, static_cast<uint16_t>(payload.size()), payload};

}

GNSSMessage GNSSReceiver::configureGPSUTCLeapSecondsInUTC(uint16_t utcYear, uint8_t utcMonth, uint8_t leapSeconds,
                                                          uint8_t insertSeconds, Attributes attributes) {
    Payload payload;
    payload.push_back((utcYear >> 8) & 0xFF);
    payload.push_back(utcYear & 0xFF);
    payload.push_back(utcMonth);
    payload.push_back(leapSeconds);
    payload.push_back(insertSeconds);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigureGPSUTCLeapSecondsInUTC, static_cast<uint16_t>(payload.size()),
                       payload};

}

GNSSMessage
GNSSReceiver::configureNavigationDataMessageInterval(uint8_t navigationDataMessageInterval, Attributes attributes) {
    Payload payload;
    payload.push_back(navigationDataMessageInterval);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigureNavigationDataMessageInterval, static_cast<uint16_t>(payload.size()),
                       payload};

}

GNSSMessage GNSSReceiver::configureGNSSGEOFencingDatabyPolygon() {
    return GNSSMessage{GNSSMessagesSubID::ConfigureGNSSGeoFencingDataByPolygon, 0, {}};

}

GNSSMessage GNSSReceiver::configureNMEAStringInterval(uint16_t nmeaString, uint8_t interval, Attributes attributes) {
    Payload payload;
    payload.push_back((nmeaString >> 8) & 0xFF);
    payload.push_back(nmeaString & 0xFF);
    payload.push_back(interval);
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::ConfigureNMEAStringInterval, static_cast<uint16_t>(payload.size()), payload};

}

GNSSMessage GNSSReceiver::SoftwareImageDownloadUsingInternalLoader(BaudRate baud, FlashType flashType, uint16_t flashID,
                                                                   BufferUsedIndex bufferUsedIndex,
                                                                   Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(baud));
    payload.push_back(static_cast<uint8_t>(flashType));
    payload.push_back((flashID >> 8) & 0xFF);
    payload.push_back(flashID & 0xFF);
    payload.push_back(static_cast<uint8_t>(bufferUsedIndex));
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::SoftwareImageDownloadUsingInternalLoader,
                       static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage GNSSReceiver::SoftwareImageDownloadUsingExternalLoader(BaudRate baud, FlashType flashType, uint16_t flashID,
                                                                   BufferUsedIndex bufferUsedIndex,
                                                                   Attributes attributes) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(baud));
    payload.push_back(static_cast<uint8_t>(flashType));
    payload.push_back((flashID >> 8) & 0xFF);
    payload.push_back(flashID & 0xFF);
    payload.push_back(static_cast<uint8_t>(bufferUsedIndex));
    payload.push_back(static_cast<uint8_t>(attributes));
    return GNSSMessage{GNSSMessagesSubID::SoftwareImageDownloadUsingExternalLoader,
                       static_cast<uint16_t>(payload.size()), payload};

}

GNSSMessage GNSSReceiver::querySoftwareVersion(SoftwareType softwareType) {
    Payload payload ;
    payload.push_back(static_cast<uint8_t>(softwareType));
    return GNSSMessage{GNSSMessages::QuerySoftwareVersion, static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage GNSSReceiver::querySoftwareCRC(SoftwareType softwareType) {
    Payload payload;
    payload.push_back(static_cast<uint8_t>(softwareType));
    return GNSSMessage{GNSSMessages::QuerySoftwareCRC, static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage GNSSReceiver::queryPositionUpdateRate() {
    return GNSSMessage{GNSSMessages::QueryPositionUpdateRate, 0, {}};
}

GNSSMessage GNSSReceiver::queryPowerMode() {
    return GNSSMessage{GNSSMessages::QueryPowerMode, 0, {}};
}

GNSSMessage GNSSReceiver::QueryDOPMask() {
    return GNSSMessage{GNSSMessages::QueryDOPMask, 0, {}};
}

GNSSMessage GNSSReceiver::QueryElevationandCNRMask() {
    return GNSSMessage{GNSSMessages::QueryElevationAndCNRMask, 0, {}};
}

GNSSMessage GNSSReceiver::queryPositionPinning() {
    return GNSSMessage{GNSSMessages::QueryPositionPinning, 0, {}};
}

GNSSMessage GNSSReceiver::query1PPSTiming() {
    return GNSSMessage{GNSSMessages::Query1PPSTiming, 0, {}};
}

GNSSMessage GNSSReceiver::query1PPSCableDelay() {
    return GNSSMessage{GNSSMessages::Query1PPSCableDelay, 0, {}};
}

GNSSMessage GNSSReceiver::queryNMEATalkerID() {
    return GNSSMessage{GNSSMessages::QueryNMEATalkID, 0, {}};
}

GNSSMessage GNSSReceiver::querySBASStatus() {
    return GNSSMessage{GNSSMessagesSubID::QuerySBASStatus, 0, {}};
}

GNSSMessage GNSSReceiver::queryQZSSStatus() {
    return GNSSMessage{GNSSMessagesSubID::QueryQZSSStatus, 0, {}};
}

GNSSMessage GNSSReceiver::querySBASAdvanced() {
    return GNSSMessage{GNSSMessagesSubID::QuerySBASAdvanced, 0, {}};
}

GNSSMessage GNSSReceiver::querySAEEStatus() {
    return GNSSMessage{GNSSMessagesSubID::QuerySAEE, 0, {}};
}

GNSSMessage GNSSReceiver::queryGNSSBootStatus() {
    return GNSSMessage{GNSSMessagesSubID::QueryBootStatus, 0, {}};
}

GNSSMessage GNSSReceiver::queryExtendedNMEAMesaageInterval() {
    return GNSSMessage{GNSSMessagesSubID::QueryExtendedNMEAMessageInterval, 0, {}};
}

GNSSMessage GNSSReceiver::queryInterferenceDetectionStatus() {
    return GNSSMessage{GNSSMessagesSubID::QueryInterferenceDetectionStatus, 0, {}};
}

GNSSMessage GNSSReceiver::queryGNSSParameterSearchEngineNumber() {
    return GNSSMessage{GNSSMessagesSubID::QueryGNSSParameterSearchEngineNumber, 0, {}};
}

GNSSMessage GNSSReceiver::queryPositionFixNavigationMap() {
    return GNSSMessage{GNSSMessagesSubID::QueryPositionFixNavigationMask, 0, {}};
}

GNSSMessage GNSSReceiver::QueryUTCReferenceTimeSyncToGPSTime() {
    return GNSSMessage{GNSSMessagesSubID::QueryUTCReferenceTimeSyncToGPSTime, 0, {}};
}

GNSSMessage GNSSReceiver::queryGNSSNavigationMode() {
    return GNSSMessage{GNSSMessagesSubID::QueryGNSSNavigationMode, 0, {}};
}

GNSSMessage GNSSReceiver::queryGNSSConstellationTypeForNavigationSolution() {
    return GNSSMessage{GNSSMessagesSubID::QueryGNSSConstellationTypeForNavigationSolution, 0, {}};
}

GNSSMessage GNSSReceiver::queryGPSTime() {
    return GNSSMessage{GNSSMessagesSubID::QueryGPSTime, 0, {}};
}

GNSSMessage GNSSReceiver::queryPSTIMessageInterval() {
    return GNSSMessage{GNSSMessagesSubID::QueryPSTIMessageInterval, 0, {}};
}

GNSSMessage GNSSReceiver::queryRequestedPSTIMessageInterval() {
    return GNSSMessage{GNSSMessagesSubID::QueryRequestedPSTIMessageInterval, 0, {}};
}

GNSSMessage GNSSReceiver::queryNavigationDataMessageInterval() {
    return GNSSMessage{GNSSMessagesSubID::QueryNavigationDataMessageInterval, 0, {}};
}

GNSSMessage GNSSReceiver::queryVersionExtentionString() {
    return GNSSMessage{GNSSMessagesSubID::QueryVersionExtensionString, 0, {}};
}

GNSSMessage GNSSReceiver::queryGNSSGEOFencingDatabyPolygon() {
    return GNSSMessage{GNSSMessagesSubID::QueryGNSSGeoFencingDataByPolygon, 0, {}};
}

GNSSMessage GNSSReceiver::queryGNSSMultiPolygonGEOFencingResult() {
    return GNSSMessage{GNSSMessagesSubID::QueryGNSSMultiPolygonGeoFencingResult, 0, {}};
}

GNSSMessage GNSSReceiver::queryNMEAStringInterval() {
    return GNSSMessage{GNSSMessagesSubID::QueryNMEAStringInterval, 0, {}};
}

GNSSMessage GNSSReceiver::queryRequestedNMEAStringInterval() {
    return GNSSMessage{GNSSMessagesSubID::QueryRequestedNMEAStringInterval, 0, {}};
}

GNSSMessage GNSSReceiver::getGPSEphemeris(uint8_t SV) {
    Payload payload;
    payload.push_back(SV);
    return GNSSMessage{GNSSMessages::GetGPSEphemeris, static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage GNSSReceiver::getGLONASSEphemeris(uint8_t SV) {
    Payload payload;
    payload.push_back(SV);
    return GNSSMessage{GNSSMessages::GetGLONASSEphemeris, static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage GNSSReceiver::setGLONASSEphemeris(uint8_t slotNumber, uint8_t kNumber, std::vector<uint8_t> ephemerisData0,
                                              std::vector<uint8_t> ephemerisData1, std::vector<uint8_t> ephemerisData2,
                                              std::vector<uint8_t> ephemerisData3) {
    Payload payload;
    payload.push_back(slotNumber);
    payload.push_back(kNumber);
    for (uint8_t byte: ephemerisData0) {
        payload.push_back(byte);
    }
    for (uint8_t byte: ephemerisData1) {
        payload.push_back(byte);
    }
    for (uint8_t byte: ephemerisData2) {
        payload.push_back(byte);
    }
    for (uint8_t byte: ephemerisData3) {
        payload.push_back(byte);
    }
    return GNSSMessage{GNSSMessages::SetGLONASSEphemeris, static_cast<uint16_t>(payload.size()), payload};
}

GNSSMessage GNSSReceiver::getGLONASSTimeCorrectionParameters() {
    return GNSSMessage{GNSSMessages::GetGLONASSTimeCorrectionParameters, 0, {}};
}

GNSSMessage GNSSReceiver::setFactoryDefaults() {
    return GNSSMessage{GNSSMessages::SetFactoryDefaults, 1, {1}};
}


