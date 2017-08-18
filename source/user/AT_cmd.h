#ifndef AT_CMD_H
#define AT_CMD_H

#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "nrf_svc.h"
#include "nrf51.h"
#include "nrf51_bitfields.h"
#include "nrf_error_soc.h"
#include "nrf_soc.h"
#include "simple_uart.h"
#include "ble_flash.h"
#include "app_timer.h"
#include "ble_gap.h"
#include "min_task_schedule.h"

#define BLE_NAME_ADDR_PAGE_MUN (BLE_FLASH_PAGE_END-1)
#define BLE_NAME_ADDR  ((uint32_t*)(BLE_FLASH_PAGE_SIZE * BLE_NAME_ADDR_PAGE_MUN))//flash for store ble name
typedef struct
{
	uint8_t *cmd_name;
	void (*cmd_fun)(const uint8_t *str);
} ATStruct;

typedef struct {
	char ble_name[56];
	uint32_t ble_boud;
	uint8_t sleep_sign;
}BLE_INFO;
char *get_ble_name();
void store_ble_info();
void init_user_data();

void AT_cmd_parser(const uint8_t *str);
void cmd_manage_ble_name(const uint8_t *cmd);
void cmd_close_ad(const uint8_t *cmd);
void cmd_ble_disconnect(const uint8_t *cmd);
void cmd_at_reset(const uint8_t *cmd);
void cmd_at_change_boud(const uint8_t *cmd);
void cmd_at_mac(const uint8_t *cmd);


#endif