#include "min_task_schedule.h"

typedef struct {
	int task_id;
	int delay_ms;
	void (*task_fun)();

}TaskSchedule;

int is_task_heart_interrupt=0;
static app_timer_id_t task_heart_tick;//1ms一次
void task_fun(){}
void heart_interrupt_handle(){
	is_task_heart_interrupt=1;
}
TaskSchedule tasks[]=
{
	{
		0,-1,task_fun
	},
	{
		1,-1,task_fun
	},
	{
		2,-1,task_fun
	},
	{
		3,-1,task_fun
	},
	{
		4,-1,task_fun
	}
};

void init_task_schedule()
{
	app_timer_create(&task_heart_tick,APP_TIMER_MODE_SINGLE_SHOT,heart_interrupt_handle);
	app_timer_start(task_heart_tick,30,NULL);//心跳时长1ms
	
}

void task_set(int task_id,void (*task_fun))
{
	tasks[task_id].task_fun=task_fun;
}

void task_restart(int task_id,int delay_ms)
{
	tasks[task_id].delay_ms=delay_ms;
	app_timer_start(task_heart_tick,30,NULL);//心跳时长1ms
}
void task_stop(int task_id)
{
	tasks[task_id].delay_ms=-1;
}
void task_schedule()
{
	if(is_task_heart_interrupt)
	{
		int i=0;
		int tick_continue=0;
		is_task_heart_interrupt=0;
		for(i=0;i<5;i++)
		{
			if(tasks[i].delay_ms>0)
			{
				tasks[i].delay_ms--;
				tick_continue=1;
			}
			else if(tasks[i].delay_ms==0)
			{
				tasks[i].delay_ms--;
				tasks[i].task_fun();
			}			
		}
		if(tick_continue)
		{
			app_timer_start(task_heart_tick,30,NULL);//心跳时长1ms
		}
	}
}











