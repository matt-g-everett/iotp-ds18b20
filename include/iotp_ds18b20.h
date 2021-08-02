#ifndef __ESP_LOGGER_H
#define __ESP_LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "freertos/FreeRTOS.h"
#include "ds18b20.h"

typedef void (*iotp_ds18b20_update)(float reading);

typedef struct {
    esp_mqtt_client_handle_t mqtt_client;
    uint8_t gpio_pin;
    iotp_ds18b20_update update_cb;
    uint8_t connected;
    DS18B20_RESOLUTION resolution;
    TickType_t interval;
    bool ntp_synced;
    float current;
} iotp_ds18b20_t;

typedef iotp_ds18b20_t *iotp_ds18b20_handle_t;

iotp_ds18b20_handle_t iotp_ds18b20_init(esp_mqtt_client_handle_t mqtt_client, uint8_t gpio_pin, iotp_ds18b20_update update_cb);
int iotp_ds18b20_get_connected(iotp_ds18b20_handle_t state);
void iotp_ds18b20_set_connected(iotp_ds18b20_handle_t state, int connected);
void iotp_ds18b20_set_ntp(iotp_ds18b20_handle_t handle, bool synced);
void iotp_ds18b20_task(void *pParam);

#ifdef __cplusplus
}
#endif

#endif
