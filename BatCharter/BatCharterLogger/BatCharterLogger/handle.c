#include "handle.h"

void manage_BatCurrent(void)
{
	float Bat1V;
	float Bat1I;
	float Bat2V;
	float Bat2I;
	uint16_t DACB1;
	uint16_t DACB2;
	
	enum measurment {Battery1V, Battery1I, Battery2V, Battery2I};
		
	Bat1V = (read_ADCV(Battery1V))*10;												//Read battery 1 voltage
	Bat2V = (read_ADCV(Battery2V))*10;												//Read battery 2 voltage
	
	if(Bat1V>1)																		//Bat 1 control loop
	{
		PORTA.OUTSET = PIN7_bm;														//Enable status LED
		Bat1I = (read_ADCV(Battery1I)/Rs);											//Calculate current
		if (Bat1I < Is)
		{
			DACB1 = DACA.CH0DATA;													//Get DAC DATA					
			DACB1++;
			write_DAC(DACB1, 0);													//Write new DATA to DAC
		}
		else if (Bat1I > Is)
		{
			DACB1 = DACA.CH0DATA;													//Get DAC DATA
			DACB1--;
			write_DAC(DACB1, 0);													//Write new DATA to DAC
		}
	}
	else
	{
		PORTA.OUTCLR = PIN7_bm;														//B1 Not connected stop measuring
		write_DAC(0, 0);
	}
	
	
	
	if(Bat2V>1)																		//Bat 2 control loop
	{
		PORTA.OUTSET = PIN6_bm;														//Enable status LED
		Bat2I = (read_ADCV(Battery2I)/Rs);											//Calculate current
		if (Bat2I < Is)
		{
			DACB2 = DACA.CH1DATA;													//Get DAC DATA
			DACB2++;
			write_DAC(DACB2, 1);													//Write new DATA to DAC
		}
		else if (Bat2I > Is)
		{
			DACB2 = DACA.CH1DATA;													//Get DAC DATA
			DACB2--;
			write_DAC(DACB2, 1);													//Write new DATA to DAC
		}
	}
	else
	{
		PORTA.OUTCLR = PIN6_bm;														//B2 Not connected stop measuring
		write_DAC(0, 1);
	}

}