#ifndef USER_BLE_CONTROL_H
#define USER_BLE_CONTROL_H

#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "nrf_svc.h"
#include "nrf51.h"
#include "nrf51_bitfields.h"
#include "nrf_error_soc.h"
#include "nrf_soc.h"
#include "nrf_sdm.h"
#include "simple_uart.h"
#include "ble_flash.h"
#include "app_timer.h"
#include "ble_gap.h"
#include "AT_cmd.h"
#include "app_gpiote.h"

#include "nrf_gpio.h"

#define DISCONNECT_BLE_SWITCH 13
#define WAKEUP_BLE_SWITCH     23
#define BLE_STATUS            29

#define BLE_CONNECTED 0
#define BLE_DISCONNECTED 1
void init_user_ble_control();
void write_ble_status(int status);
void gpio_event_handler(uint32_t event_pins_low_to_high, uint32_t event_pins_high_to_low);
void delay_to_sleep_handle();
void enter_system_off();

#endif