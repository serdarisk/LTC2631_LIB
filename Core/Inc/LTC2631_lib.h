/*
kütüphane kullanımı için main.c kodları yazımı:
1-I2C portunu ve adresi hafızasında tutacak LTC2631_HandleTypeDef struct ı yazılmalı
2-main içinde adres belirlenmeli
3-HAL_StatusTypeDef LTC2631_Init fonksiyonu çağırılmalı
4-son olarak LTC2631_SetVoltage fonksiyonu çağırılmalı
*/


#ifndef LTC2631_H
#define LTC2631_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

#define LTC2631_CMD_WRITE_TO_INPUT_REG  0x00
#define LTC2631_CMD_UPDATE_DAC          0x10
#define LTC2631_CMD_WRITE_AND_UPDATE    0x30
#define LTC2631_CMD_POWER_DOWN          0x40

typedef struct {
    I2C_HandleTypeDef *hi2c;
    uint8_t device_address;
} LTC2631_HandleTypeDef;

HAL_StatusTypeDef LTC2631_Init(LTC2631_HandleTypeDef *dev, I2C_HandleTypeDef *hi2c, uint8_t address);
HAL_StatusTypeDef LTC2631_SetRawValue(LTC2631_HandleTypeDef *dev, uint16_t value);
HAL_StatusTypeDef LTC2631_SetVoltage(LTC2631_HandleTypeDef *dev, float voltage, float vRef);
HAL_StatusTypeDef LTC2631_PowerDown(LTC2631_HandleTypeDef *dev);

#endif
