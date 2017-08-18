#include "user_ble_control.h"


static app_gpiote_user_id_t p_user_id=1;
void init_user_ble_control()
{
	int ret=-10;
	//蓝牙状态输出
	nrf_gpio_cfg_output(BLE_STATUS);//配置蓝牙状态	
	
	//下降沿断开蓝牙连接
	APP_GPIOTE_INIT(3);
	// DISCONNECT_BLE_SWITCH 下降沿断开蓝牙连接，平时为高电平
	nrf_gpio_cfg_input(DISCONNECT_BLE_SWITCH, NRF_GPIO_PIN_PULLUP);  
	nrf_gpio_cfg_input(WAKEUP_BLE_SWITCH, NRF_GPIO_PIN_PULLUP);   	 	
	
	uint32_t  low_to_high_bitmask = (0x00000001<<DISCONNECT_BLE_SWITCH) | (0x00000001<<WAKEUP_BLE_SWITCH); 
	uint32_t  high_to_low_bitmask = (0x00000001<<DISCONNECT_BLE_SWITCH) | (0x00000001<<WAKEUP_BLE_SWITCH); 
	ret=app_gpiote_user_register( &p_user_id, low_to_high_bitmask , high_to_low_bitmask,gpio_event_handler);
	ret=app_gpiote_user_enable (p_user_id);
 	
	//// 初始化
	write_ble_status(BLE_DISCONNECTED);	
	ble_log("user_ble_control inited");
	task_set(SYSTEM_OFF,enter_system_off);
}
/**
 * @brief Function for write ble status.
 *
 * Note Low is connected, Height is disconneted
 *
 * @param 0,1
 */
void write_ble_status(int status)
{
	if(status)
	{
		nrf_gpio_pin_set(BLE_STATUS);
	}
	else
	{
		 nrf_gpio_pin_clear(BLE_STATUS);
	}           
}
/**
 * @brief Function for set ble disconnet.
 *
 * Note if Low ,disconnect ble with phone and mustn't be connnect. if Height ,ble is connect able  
 *
 */
void gpio_event_handler(uint32_t event_pins_low_to_high, uint32_t event_pins_high_to_low)
{
	ble_log("gpio_event_handler"); 
	extern void ble_stop_current_connect(void * p_event_data, uint16_t event_size);		  
	if (event_pins_high_to_low & (0x00000001<<DISCONNECT_BLE_SWITCH))   
	{      
		app_sched_event_put(0,0,ble_stop_current_connect);
	}
	if (event_pins_high_to_low & (0x00000001<<WAKEUP_BLE_SWITCH))   
	{      
		extern void uart_reinit(void);
		uart_reinit();
		ble_log("WAKEUP_BLE_SWITCH event_pins_high_to_low"); 
	}
	if (event_pins_low_to_high & (0x00000001<<WAKEUP_BLE_SWITCH))   
	{      
		task_restart(SYSTEM_OFF,100);
		task_restart(UART_POWER_DOWN_TASK,3);
		ble_log("WAKEUP_BLE_SWITCH event_pins_low_to_high");
	}
}
int get_uart_enable_pin_state()
{
	uint32_t p_pins=0;  
	app_gpiote_pins_state_get(p_user_id,&p_pins);
	if(p_pins & (0x00000001<<WAKEUP_BLE_SWITCH))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void enter_system_off()
{
	extern BLE_INFO ble_info;
	extern void ready_to_sleep();
	if(ble_info.sleep_sign)
	{
		ble_log("enter_sleep");   
		ready_to_sleep();
		nrf_gpio_cfg_sense_input(WAKEUP_BLE_SWITCH, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW); 
		sd_power_system_off();
	}
}




