/*
kütüphane kullanımı için main.c kodları yazımı:
1-I2C portunu ve adresi hafızasında tutacak LTC2631_HandleTypeDef struct ı yazılmalı
2-main içinde adres belirlenmeli
3-HAL_StatusTypeDef LTC2631_Init fonksiyonu çağırılmalı
4-son olarak LTC2631_SetVoltage fonksiyonu çağırılmalı
*/


#include "LTC2631_lib.h"

HAL_StatusTypeDef LTC2631_Init(LTC2631_HandleTypeDef *dev, I2C_HandleTypeDef *hi2c, uint8_t address) {
    dev->hi2c = hi2c;
    dev->device_address = address;

//I2C hattı yanıt veriyor mu
    return HAL_I2C_IsDeviceReady(dev->hi2c, dev->device_address, 3, 100);
}

HAL_StatusTypeDef LTC2631_SendCommand(LTC2631_HandleTypeDef *dev, uint8_t command, uint16_t value) {
    uint8_t data[3];

    data[0] = command;                     //komut byteı
    data[1] = (value >> 4) & 0xFF;         //datasheette belirtilen sola dayalı 12bit
    data[2] = (value << 4) & 0xF0;

    return HAL_I2C_Master_Transmit(dev->hi2c, dev->device_address, data, 3, 100);

}

//örnek olarak wirite an update modu kullanıldı
HAL_StatusTypeDef LTC2631_SetRawValue(LTC2631_HandleTypeDef *dev, uint16_t value) {
    return LTC2631_SendCommand(dev, LTC2631_CMD_WRITE_AND_UPDATE, value);
}

//uyku modu
HAL_StatusTypeDef LTC2631_PowerDown(LTC2631_HandleTypeDef *dev) {
    return LTC2631_SendCommand(dev, LTC2631_CMD_POWER_DOWN, 0x0000);
}

HAL_StatusTypeDef LTC2631_SetVoltage(LTC2631_HandleTypeDef *dev, float voltage, float vRef) {
    if (voltage > vRef) voltage = vRef;
    if (voltage < 0.0f) voltage = 0.0f;

    uint16_t raw_val = (uint16_t)((voltage / vRef) * 4095.0f);
    return LTC2631_SetRawValue(dev, raw_val);
}



