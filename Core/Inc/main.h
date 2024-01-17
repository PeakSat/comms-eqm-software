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
void main_cpp();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MMC_RST_Pin GPIO_PIN_13
#define MMC_RST_GPIO_Port GPIOC
#define RF_IRQ_Pin GPIO_PIN_1
#define RF_IRQ_GPIO_Port GPIOC
#define RF_IRQ_EXTI_IRQn EXTI1_IRQn
#define EN_UHF_AMP_RX__Pin GPIO_PIN_1
#define EN_UHF_AMP_RX__GPIO_Port GPIOA
#define MONITOR_CRITICAL_Pin GPIO_PIN_2
#define MONITOR_CRITICAL_GPIO_Port GPIOA
#define MONITOR_WARNING_Pin GPIO_PIN_3
#define MONITOR_WARNING_GPIO_Port GPIOA
#define VSET_AGC_UHF_Pin GPIO_PIN_5
#define VSET_AGC_UHF_GPIO_Port GPIOA
#define GAIN_SET_UHF_Pin GPIO_PIN_4
#define GAIN_SET_UHF_GPIO_Port GPIOC
#define AGC_TEMP_UHF_Pin GPIO_PIN_5
#define AGC_TEMP_UHF_GPIO_Port GPIOC
#define EN_AGC_UHF_Pin GPIO_PIN_1
#define EN_AGC_UHF_GPIO_Port GPIOB
#define EN_PA_UHF_Pin GPIO_PIN_2
#define EN_PA_UHF_GPIO_Port GPIOB
#define RF_RST_Pin GPIO_PIN_7
#define RF_RST_GPIO_Port GPIOE
#define ALERT_T_PA_U_Pin GPIO_PIN_8
#define ALERT_T_PA_U_GPIO_Port GPIOE
#define FLAGB_TX_UHF_Pin GPIO_PIN_9
#define FLAGB_TX_UHF_GPIO_Port GPIOE
#define FLAGB_RX_UHF_Pin GPIO_PIN_10
#define FLAGB_RX_UHF_GPIO_Port GPIOE
#define EN_RX_UHF_Pin GPIO_PIN_11
#define EN_RX_UHF_GPIO_Port GPIOE
#define ALERT_T_PCB_Pin GPIO_PIN_12
#define ALERT_T_PCB_GPIO_Port GPIOE
#define P5V_RF_EN_Pin GPIO_PIN_13
#define P5V_RF_EN_GPIO_Port GPIOE
#define LED_PE14_Pin GPIO_PIN_14
#define LED_PE14_GPIO_Port GPIOE
#define LED_PE15_Pin GPIO_PIN_15
#define LED_PE15_GPIO_Port GPIOE
#define BUS_SCL_Pin GPIO_PIN_10
#define BUS_SCL_GPIO_Port GPIOB
#define GNSS_UART_RX_Pin GPIO_PIN_12
#define GNSS_UART_RX_GPIO_Port GPIOB
#define GNSS_UART_TX_Pin GPIO_PIN_13
#define GNSS_UART_TX_GPIO_Port GPIOB
#define GNSS_RSTN_Pin GPIO_PIN_14
#define GNSS_RSTN_GPIO_Port GPIOB
#define MONITOR_PG_Pin GPIO_PIN_10
#define MONITOR_PG_GPIO_Port GPIOD
#define MONITOR_TC_Pin GPIO_PIN_11
#define MONITOR_TC_GPIO_Port GPIOD
#define ALERT_T_PA_S_Pin GPIO_PIN_14
#define ALERT_T_PA_S_GPIO_Port GPIOD
#define MMC_EN_Pin GPIO_PIN_6
#define MMC_EN_GPIO_Port GPIOC
#define P5V_RF_PG_Pin GPIO_PIN_7
#define P5V_RF_PG_GPIO_Port GPIOC
#define P3V3_RF_PG_Pin GPIO_PIN_9
#define P3V3_RF_PG_GPIO_Port GPIOA
#define MEM_SEL_Pin GPIO_PIN_10
#define MEM_SEL_GPIO_Port GPIOA
#define JTMS_SWDIO_Pin GPIO_PIN_13
#define JTMS_SWDIO_GPIO_Port GPIOA
#define JTCK_SWCLK_Pin GPIO_PIN_14
#define JTCK_SWCLK_GPIO_Port GPIOA
#define MCU_MMC_D2_Pin GPIO_PIN_10
#define MCU_MMC_D2_GPIO_Port GPIOC
#define MCU_MMC_D3_Pin GPIO_PIN_11
#define MCU_MMC_D3_GPIO_Port GPIOC
#define MCU_MMC_CK_Pin GPIO_PIN_12
#define MCU_MMC_CK_GPIO_Port GPIOC
#define MCU_MMC_CMD_Pin GPIO_PIN_2
#define MCU_MMC_CMD_GPIO_Port GPIOD
#define CAN1_FAULT_Pin GPIO_PIN_3
#define CAN1_FAULT_GPIO_Port GPIOD
#define CAN1_S_Pin GPIO_PIN_4
#define CAN1_S_GPIO_Port GPIOD
#define CAN2_FAULT_Pin GPIO_PIN_5
#define CAN2_FAULT_GPIO_Port GPIOD
#define CAN2_S_Pin GPIO_PIN_7
#define CAN2_S_GPIO_Port GPIOD
#define JTDO_SWO_Pin GPIO_PIN_3
#define JTDO_SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
