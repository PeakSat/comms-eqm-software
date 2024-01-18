#include "eMMC/Driver.hpp"

using namespace eMMC;

extern MMC_HandleTypeDef hmmc1;

uint8_t eMMC::initializeEMMC(){
    if(HAL_MMC_ConfigWideBusOperation(&hmmc1, SDMMC_BUS_WIDE_4B)!=HAL_OK){
        return 1;
    }
    if(HAL_MMC_Init(&hmmc1)!=HAL_OK){
        return 2;
    }
    if(HAL_MMC_InitCard(&hmmc1)!=HAL_OK){
        return 3;
    }
    return 0;
}

HAL_MMC_CardInfoTypeDef eMMC::checkEMMC(){
    HAL_MMC_CardInfoTypeDef mmc_info;
    HAL_MMC_GetCardInfo(&hmmc1, &mmc_info);
    return mmc_info;
}

HAL_StatusTypeDef eMMC::writeBlockEMMC(uint8_t* write_data, uint32_t block_address){
    return HAL_MMC_WriteBlocks(&hmmc1, write_data, block_address, 1, 1000);
}

HAL_StatusTypeDef eMMC::readBlockEMMC(uint8_t* read_data, uint32_t block_address){
    return HAL_MMC_ReadBlocks(&hmmc1, read_data, block_address, 1, 1000);
}

HAL_StatusTypeDef eMMC::eraseBlocksEMMC(uint32_t block_address_start, uint32_t block_address_end){
    return HAL_MMC_Erase(&hmmc1, block_address_start, block_address_end);
}

