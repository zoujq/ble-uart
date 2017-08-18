#ifndef MIN_TASK_SCHEDULE_H
#define MIN_TASK_SCHEDULE_H

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

#define UART_TASK 0
#define AT_TASK   1
#define SYSTEM_OFF 2
#define UART_POWER_DOWN_TASK 3
void init_task_schedule();
void task_set(int task_id,void (*task_fun));
void task_restart(int task_id,int delay_ms);
void task_stop(int task_id);
void task_schedule();


#endif