#ifndef __POWER_H
#define __POWER_H

#include <stdio.h>
#define  PWR_ON     	printf("POWER_ON\r\n");
#define  PWR_OFF    	printf("POWER_OFF\r\n");
#define  CHARGE_ON		printf("CHARGE_ON\r\n");
#define  CHARGE_OFF		printf("CHARGE_OFF\r\n");

void Power_Init(void);

#endif


