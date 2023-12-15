#include "ADC.h"


void init_ADC(void)
{
	PORTD_DIRCLR = PIN0_bm;													//Set PD0 as input (Battery 1 Voltage) (ADC PIN 8)
	PORTD_DIRCLR = PIN1_bm;													//Set PD0 as input (Battery 1 Current) (ADC PIN 9)
	PORTD_DIRCLR = PIN2_bm;													//Set PD0 as input (Battery 2 Voltage) (ADC PIN 10)
	PORTD_DIRCLR = PIN3_bm;													//Set PD0 as input (Battery 2 Current) (ADC PIN 11)
	
	ADCA.PRESCALER = (0x07);												//Set ADCA clock speed to 125kHz
	ADCA.REFCTRL |= ADC_RESOLUTION_12BIT_gc;								//Set ADCA to 12bit resolution
	ADCA.REFCTRL |= ADC_REFSEL_INTVCC_gc;									//Set ADCA reference voltage to (supply voltage/1.6)
	
	ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN10_gc;								//Multiplexes PD0 to ADCA channel 8 (Battery 1 Voltage)
	
	ADCA.CH0.CTRL |= ADC_CH_INPUTMODE_SINGLEENDED_gc;						//Set ADCA channel 0 to single ended input
	ADCA.CH0.MUXCTRL |= ADC_CH_MUXNEG_INTGND_MODE3_gc;						//Set ADCA channel 0 lower reference voltage to internal GND
	ADCA.CTRLA |= (0x01);													//Enable ADCA
}

uint16_t read_ADC(uint8_t MeasurementParameter)
{
	uint16_t ADCRes;														//Temporary variable for storing ADC result
	
	switch (MeasurementParameter)
	{
		case 0:
			ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN8_gc;						//Multiplexes PD0 to ADCA channel 8 (Battery 1 Voltage)
			break;
		case 1:
			ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN9_gc;						//Multiplexes PD1 to ADCA channel 9 (Battery 1 Current)
			break;
		case 2:
			ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN10_gc;						//Multiplexes PD2 to ADCA channel 10 (Battery 2 Voltage)
			break;
		case 3:
			ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN11_gc;						//Multiplexes PD3 to ADCA channel 11 (Battery 2 Current)
			break;
		default:
			return 0;
			break;
	}
	
	ADCA.CTRLA |= (0x01);													//Enable ADCA
	
	for(int i = 0; i < 1000; i++)
	{
		//Do nothing for long time
	}
	
	ADCA.CTRLA |= (0x04);													//Start a conversion on ADCA
	
	while((ADCA.INTFLAGS&(0x01))!=1)										//Wait for ADC conversion
	{
		//Do nothing
	}
	
	ADCRes = ADCA.CH0.RES;													//Read ADC conversion
	ADCA.INTFLAGS &= (0x01);												//Clear interrupt flag
	
	return ADCRes;
}

float read_ADCV(uint8_t MeasurementParameter)
{
	float ADCRes[NAVRAGE];
	float ADCsum = 0;
	
	for(uint8_t i = 0; i < NAVRAGE; i++)
	{
		ADCRes[i] = (float)read_ADC(MeasurementParameter);					//Get ADC result
		ADCRes[i] = (((ADCRes[i])-ADCOFFSET)/4095)*INTVCC;					//Convert to volt
	}
	
	for(uint8_t i = 0; i < NAVRAGE; i++)
	{
		ADCsum += ADCRes[i];												//Calculate sum of results
	}
	
	ADCsum /= NAVRAGE;														//Calculate average of results
	
	
	return ADCsum;
}