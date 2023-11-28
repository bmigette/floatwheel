#include "tasktest.h"
#include "math.h"

uint8_t errCode = 0;

 void WS2812_Power_Display(uint8_t brightness)
{
	uint8_t numleds = 11 - Power_Display_Flag;
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	// 20% and below: red
	// 40% and below: yellow
	// > 40% white
	r = brightness;
	if (numleds > 2)
		g = brightness;
	if (numleds > 4)
		b = brightness;
	
	if (Power_Display_Flag > 0) {
		WS2812_Set_AllColours(1, numleds, r, g, b);
	}
	else {
		WS2812_Set_AllColours(5, 6, brightness, 0, brightness);
	}
	WS2812_Refresh();
}

uint8_t status_brightness = 1;
/**************************************************
 * @brie   : WS2812_Calc_Bri()
 * @note   : Pulsate brightness
 * @param  : times 1 means 200ms
**************************************************/
 uint8_t WS2812_Calc_Bri(uint8_t cnt)
{	
	if(cnt < 50)
	{
		status_brightness++;
	}
	else
	{
		status_brightness--;
	}
	
	if(status_brightness < 1)
	{
		status_brightness = 1;
	}
	
	if(status_brightness > 50)
	{
		status_brightness = 50;
	}
	
	return status_brightness;
}


/**************************************************
 * @brie   :WS2812_Charge()
 * @note   :Power LED display while charging
 **************************************************/
 void WS2812_Charge(void)
{
	 uint8_t cnt = 0;
	WS2812_Power_Display(WS2812_Calc_Bri(cnt));
	cnt++;
	if(cnt == 100)
	{
		cnt = 0;
	}
	
	WS2812_Refresh();
}	

 void WS2812_Disabled(void)
{
	int brightness = WS2812_Measure;
	if (brightness < 20)
		brightness = 20;

	// 2 red LEDs in the center
	WS2812_Set_AllColours(5, 6, brightness, 0, 0);
	WS2812_Refresh();
}

// Idle animation:
 void WS2812_Idle(void)
{
	 int cnt = 0;
	cnt++;
	if(cnt == 8 * 512)
	{
		cnt = 0;
	}
	if ((cnt % 80) == 0) {
		int r, g, b;
		int div = cnt >> 3; // fast div by 8
		int idx = div % 10;
		r = div; if (r > 255) r = 0;
		g = -128 + div; if (g < 0) g = 0; if (g > 255) g = 0;
		b = 256 + div; if (b < 0) b = 0; if (b > 255) b = 0;
		WS2812_Set_AllColours(idx, idx, r, g, b);
		WS2812_Refresh();
	}
}

void Power_Task(void)
{
	 uint8_t power_flag_last = 0; //��һ�ε�״̬
	 uint8_t power_step = 0;

	if (Power_Flag == 4) {
		if(Power_Time > VESC_SHUTDOWN_TIME)
		{
			Power_Flag = 3;
		}
	}
	
	if(power_flag_last == Power_Flag && Power_Flag != 1)
	{
		return;
	}
	power_flag_last = Power_Flag;
	
	switch(Power_Flag)
	{
		case 1://VESC Power On
			PWR_ON;
			switch(power_step)
			{
				case 0:
					Power_Time = 0;
					power_step = 1;
				break;
				
				case 1:
					if(Power_Time > VESC_BOOT_TIME)
					{
						Power_Flag = 2; // Boot completed
						Gear_Position = 1; // The default setting is 1st gear after power-on.
						Buzzer_Flag = 2;    // The default buzzer sounds when powering on
						power_step = 0;
						WS2812_Display_Flag = 1;
					}
				break;
			}
			
		break;	

		case 3:// VESC is shut down (either auto-shutdown or button press)
			WS2812_Display_Flag = 0;
			PWR_OFF;
		break;

		case 4:// New Power state for shutdown sequence
			WS2812_Display_Flag = 3;
		default:
		break;
	}
}

void CheckPowerLevel(float battery_voltage)
{
	 float battery_voltage_last = 0;

	if((battery_voltage > (battery_voltage_last+VOLTAGE_RECEIPT)) || (battery_voltage < (battery_voltage_last - VOLTAGE_RECEIPT)))
	{
		if(battery_voltage>4.07)
		{
			Power_Display_Flag = 1;
		}
		else if(battery_voltage>4.025)
		{
			Power_Display_Flag = 2;
		}
		else if(battery_voltage>3.91)
		{
			Power_Display_Flag = 3;
		}
		else if(battery_voltage>3.834)
		{
			Power_Display_Flag = 4;
		}
		else if(battery_voltage>3.746)
		{
			Power_Display_Flag = 5;
		}
		else if(battery_voltage>3.607)
		{
			Power_Display_Flag = 6;
		}
		else if(battery_voltage>3.49)
		{
			Power_Display_Flag = 7;
		}
		else if(battery_voltage>3.351)
		{
			Power_Display_Flag = 8;
		}
		else if(battery_voltage>3.168)
		{
			Power_Display_Flag = 9;
		}
		else if(battery_voltage>2.81)
		{
			Power_Display_Flag = 10;
		}

		battery_voltage_last = battery_voltage;
	}
}

/**************************************************
 * @brie   :Charge_Task()
 * @note   :Check for charge start/end conditions
 **************************************************/
void Charge_Task(void)
{
	 uint8_t charge_step = 0; 

	if(Charge_Flag > 0)
	{
		if(V_I == 0 && Charge_Time > 150)
		{
			if(Charge_Current < CHARGE_CURRENT && Charge_Current > 0)
			{
				Charge_Flag = 3;
				Shutdown_Cnt++;
				if(Shutdown_Cnt>10)
				{
					Charge_Flag = 0;
					Charge_Voltage = 0;
					//Charge_Current = 0;
					Charger_Detection_1ms = 0;
					charge_step = 0;
					Shutdown_Cnt = 0;
					Charge_Time = 0;
					V_I = 1;
					LED1_ON; // Use ADC3 to measure charge voltage
					CHARGE_OFF;
				}
			}
			else
			{
				Shutdown_Cnt = 0;
			}
		}
		else if(Charge_Time > 150)
		{
			if(Charge_Flag == 2)
			{
				CheckPowerLevel((Charge_Voltage+1)/BATTERY_STRING);
			}
		}
	}
	else //	Charge_Flag == 0
	{
		charge_step = 0;
		if(Charge_Voltage > CHARGING_VOLTAGE)// && (Charge_Current > 0.1))
		{
			if(Charger_Detection_1ms > CHARGER_DETECTION_DELAY)
			{
				if (Charge_Flag != 2)
					Charge_Flag = 1;
				WS2812_Display_Flag = 0;
			}
		}
		else {
			Charger_Detection_1ms = 0;
			return;
		}
	}

	switch(charge_step)
	{
		case 0:
			Charge_Time = 0;
			charge_step = 1;
		break;
		
		case 1:
			if(Charge_Time > 1000)  //��ʱ1S
			{
				charge_step = 2;
			}
		break;
		
		case 2:
			CHARGE_ON;
			Charge_Flag = 2;
		    charge_step = 3;
			//Power_Flag = 1;	// Boot the VESC
		break;
		
		case 3:
			Charge_Time = 0;
			charge_step = 4;
		break;
			
		case 4:	
			if(Charge_Time > DETECTION_SWITCH_TIME) 
			{
				V_I = 1;
				Charge_Time = 0;
				LED1_ON; // Use ADC3 to measure charge voltage
				charge_step = 5;
			}
		break;
			
		case 5:
			if(Charge_Time > DETECTION_SWITCH_TIME) 
			{
				V_I = 0;
				Charge_Time = 0;
				LED1_OFF; // Use ADC3 to measure charge current
				charge_step = 4;
			}		
		break;
			
		
		default:
			if (errCode == 0)
				errCode = 3;
			
		break;
		
	}
}
