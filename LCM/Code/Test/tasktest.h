#ifndef __TASK_H
#define __TASK_H



#include "flag_bit.h"
#include "power.h"
#include "led.h"

#include "ws2812.h"



#define	  CHARGING_VOLTAGE	  		40
#define   BATTERY_STRING      		20
#define   SHUTDOWN_TIME		  		20
#define   VESC_RPM            		250
#define   VESC_BOOT_TIME      		4000
#define   VESC_SHUTDOWN_TIME      	1000
#define   DUTY_CYCLE          		0.9
#define   VOLTAGE_RECEIPT     		0.02
/*******************************************************************************/
#define   VESC_RPM_WIDTH      		-200
#define   WS2812_1_BRIGHTNESS 		100
#define   WS2812_2_BRIGHTNESS 		60
#define   WS2812_3_BRIGHTNESS 		30
#define   CHARGE_CURRENT			0.24
#define   DETECTION_SWITCH_TIME     500
#define   CHARGER_DETECTION_DELAY	1000

uint8_t errCode; //this is normally in vest uart


void Power_Task(void);
void Charge_Task(void);
void WS2812_Power_Display(uint8_t brightness); 
void WS2812_Charge(void);

#endif



