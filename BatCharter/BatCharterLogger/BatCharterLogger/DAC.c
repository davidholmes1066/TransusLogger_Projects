#include "DAC.h"

void init_DAC(void)
{
	DACA.CTRLC = DAC_REFSEL_AVCC_gc;										//set DAC reference to AVCC
	DACA.CTRLB = DAC_CHSEL_DUAL_gc;											//set DAC to channel 0
	DACA.CTRLA = DAC_CH0EN_bm | DAC_CH1EN_bm | DAC_ENABLE_bm;				//Enable DAC
	//Write: to register DACA.CH0DATA and DACA.CH1DATA
}

void write_DAC(uint16_t Data, uint8_t channel)
{
	switch (channel)
	{
	case 0:
		DACA.CH0DATA = Data;												//Write data to channel 0
		break;
	case 1:
		DACA.CH1DATA = Data;												//Write data to channel 1
		break;
	default:
		break;
	}
}
