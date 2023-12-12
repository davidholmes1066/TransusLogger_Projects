#include <avr/io.h>
#include <xc.h>

#include "init.h"
#include "UART.h"

int main(void)
{
	init_CLK();												//Set clock to 32MHz
	init_LED();												//Set status LEDs
	init_UART();											//Set UART registers
	
    while(1)
    {
		write8_UART(0x48);									//Send test message
		write8_UART(0x49);
		write8_UART(0x21);
		write8_UART(0x15);
    }
}