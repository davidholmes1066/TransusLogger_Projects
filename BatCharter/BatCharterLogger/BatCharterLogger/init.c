#include <avr/io.h>
#include "init.h"

void init_LED(void)
{
	PORTC.DIRSET |= (0x01);										//Set PC0 MCU LED as outputs
	PORTD.DIRSET |= (0x80);										//Set PD7 Status LED as output
	
	PORTC.OUTSET |= (0x01);										//Enable MCU LED
	//PORTD.OUTSET |= (0x80);										//Enable Status LED
}
void init_CLK(void)
{
	OSC.CTRL |= OSC_RC32MEN_bm;												// Enable internal 32 MHz oscillator
	while(!(OSC.STATUS & OSC_RC32MRDY_bm));									// Wait for oscillator is ready
	CCP = CCP_IOREG_gc;														// Security signature to modify clock
	CLK.CTRL = CLK_SCLKSEL_RC32M_gc;										// Select 32 MHz oscillator
	CLK.PSCTRL = CLK_PSADIV_1_gc;											// Set PSA to 1
	CLK.PSCTRL = CLK_PSBCDIV_1_1_gc;										// Set PSB&PSC to 1
}
