#include <avr/io.h>
#include <stdlib.h>
#include <xc.h>

#include "init.h"
#include "UART.h"
#include "ADC.h"
#include "DAC.h"
#include "handle.h"

int main(void)
{
	init_CLK();																		//Set clock to 32MHz
	init_LED();																		//Set status LEDs
	init_UART();																	//Set UART registers
	init_ADC();																		//Set ADC registers
	init_DAC();																		//Set DAC parameters
	
	enum measurment {Battery1V, Battery1I, Battery2V, Battery2I};
	float Bat2V;
	float Bat2I;
	uint16_t DACB2;
	
    while(1)
    {
		manage_BatCurrent();
	}
}