/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MMC_RST_Pin GPIO_PIN_13
#define MMC_RST_GPIO_Port GPIOC
#define EN_S_BAND_TX_Pin GPIO_PIN_0
#define EN_S_BAND_TX_GPIO_Port GPIOA
#define EN_UHF_AMP_RX__Pin GPIO_PIN_1
#define EN_UHF_AMP_RX__GPIO_Port GPIOA
#define MONITOR_CRITICAL_Pin GPIO_PIN_2
#define MONITOR_CRITICAL_GPIO_Port GPIOA
#define MONITOR_WARNING_Pin GPIO_PIN_3
#define MONITOR_WARNING_GPIO_Port GPIOA
#define LED_PE14_Pin GPIO_PIN_14
#define LED_PE14_GPIO_Port GPIOE
#define LED_PE15_Pin GPIO_PIN_15
#define LED_PE15_GPIO_Port GPIOE
#define BUS_SCL_Pin GPIO_PIN_10
#define BUS_SCL_GPIO_Port GPIOB
#define BUS_SDA_Pin GPIO_PIN_11
#define BUS_SDA_GPIO_Port GPIOB
#define FPGA_NSS_Pin GPIO_PIN_12
#define FPGA_NSS_GPIO_Port GPIOB
#define FPGA_SCK_Pin GPIO_PIN_13
#define FPGA_SCK_GPIO_Port GPIOB
#define FPGA_MISO_Pin GPIO_PIN_14
#define FPGA_MISO_GPIO_Port GPIOB
#define FPGA_MOSI_Pin GPIO_PIN_15
#define FPGA_MOSI_GPIO_Port GPIOB
#define MMC_EN_Pin GPIO_PIN_6
#define MMC_EN_GPIO_Port GPIOC
#define P3V3_RF_PG_Pin GPIO_PIN_9
#define P3V3_RF_PG_GPIO_Port GPIOA
#define MEM_SEL_Pin GPIO_PIN_10
#define MEM_SEL_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
