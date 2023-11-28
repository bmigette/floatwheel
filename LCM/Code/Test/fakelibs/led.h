#ifndef __LED_H
#define __LED_H

#include <stdint.h>
#include <stdio.h>

#define  LED1_ON     printf("LED1_ON\r\n");
#define  LED1_OFF    printf("LED1_OFF\r\n");
#define  LED1_FILP   printf("LED1_FILP\r\n");

#define  LED_B_ON    printf("LED_B_ON\r\n");
#define  LED_B_OFF   printf("LED_B_OFF\r\n");

#define  LED_F_ON    printf("LED_F_ON\r\n");
#define  LED_F_OFF   printf("LED_F_OFF\r\n");

extern uint16_t LED_Counter;
//extern uint16_t LED_Filp_Time;

void LED_Init(void);
//void LED1_Filp_Time(uint16_t filp_time);

#endif


