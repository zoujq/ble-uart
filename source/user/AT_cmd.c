#include "AT_cmd.h"

BLE_INFO ble_info;

ATStruct at_cmds[]=
{
	{
		"AT+NAME",cmd_manage_ble_name
	},
	{
		"AT+ADVEN",cmd_close_ad
	},
	{
		"AT+RST",cmd_at_reset
	},
	{
		"AT+BOUD",cmd_at_change_boud
	},
	{
		"AT+MAC",cmd_at_mac
	}
};

void AT_cmd_parser(const uint8_t *str)
{	
	int cmd_length=sizeof(at_cmds)/sizeof(at_cmds[0]);
	int i=0;
	for(i=0;i<cmd_length;i++)
	{
		if(strstr(str,at_cmds[i].cmd_name)!=NULL)
		{
			at_cmds[i].cmd_fun(str);
			break;
		}
	}
	if(i==cmd_length)
	{
		simple_uart_putstring("NOT FIND CMD\n");
	}
	
}
void handle_delay_exe_fun(void *ids);
void init_user_data()
{
	char *temp=(char *)BLE_NAME_ADDR;
	if(temp[0]>0 && temp[0]<0xFF)
	{
		memcpy((char *)&ble_info,(char *)BLE_NAME_ADDR,sizeof(BLE_INFO));
	}
	else
	{
		strcpy(ble_info.ble_name,"SmartShowS2");
		ble_info.sleep_sign=0;
		store_ble_info();
	}
	task_set(AT_TASK,handle_delay_exe_fun);
}

void handle_delay_exe_fun(void *ids)
{
	sd_flash_write(BLE_NAME_ADDR,(uint32_t*)(&ble_info),sizeof(BLE_INFO)/4+1);
}
void store_ble_info()
{	
	sd_flash_page_erase(BLE_NAME_ADDR_PAGE_MUN);
	task_restart(AT_TASK,50);
}
char *get_ble_name()
{
	return ble_info.ble_name;
}



void cmd_manage_ble_name(const uint8_t *cmd)
{	
	int len=strlen(cmd);
	if(strcmp(cmd,"AT+NAME")==0)
	{
		ble_log(get_ble_name());
		simple_uart_putstring(get_ble_name());
	}
	else
	{
		strcpy(ble_info.ble_name,(char *)(cmd+7));
		store_ble_info();
	}

}

void cmd_close_ad(const uint8_t *cmd)
{
		ble_log(cmd);
		if(strcmp(cmd,"AT+ADVEN0")==0)
		{
			simple_uart_putstring("OK\n");
			ble_info.sleep_sign=1;
			store_ble_info();
			
		}
		else
		{
			simple_uart_putstring("OK\n");
			ble_info.sleep_sign=0;
			store_ble_info();
										
		}
}
void cmd_at_reset(const uint8_t *cmd)
{
		simple_uart_putstring("OK\n");
		NVIC_SystemReset();
}
void cmd_at_change_boud(const uint8_t *cmd)
{
	if(strcmp(cmd,"AT+BOUD0")==0)
	{
		ble_info.ble_boud=115200;
	}
	else if(strcmp(cmd,"AT+BOUD1")==0)
	{
		ble_info.ble_boud=57600;
	}
	else if(strcmp(cmd,"AT+BOUD2")==0)
	{
		ble_info.ble_boud=38400;
	}
	else if(strcmp(cmd,"AT+BOUD3")==0)
	{
		ble_info.ble_boud=19200;
	}
	else if(strcmp(cmd,"AT+BOUD4")==0)
	{
		ble_info.ble_boud=9600;
	}
	store_ble_info();
	simple_uart_putstring("OK\n");
}
void cmd_at_mac(const uint8_t *cmd)
{
	ble_gap_addr_t addr;
	uint8_t ret[50];

	sd_ble_gap_address_get(&addr);
	sprintf(ret,"%X%X%X%X%X%X",addr.addr[5],addr.addr[4],addr.addr[3],addr.addr[2],addr.addr[1],addr.addr[0]);
	simple_uart_putstring(ret);
}

