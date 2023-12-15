#include "UART.h"

void init_UART(void)
{
	PORTC_DIRCLR = PIN2_bm;												//Set RX pin USARTC0 C2 as input
	PORTC_DIRSET = PIN3_bm;												//Set TX pin USARTC0 C3 as output
	PORTC_OUTSET = PIN3_bm;												//Set TX pin to high
	
	USARTC0.BAUDCTRLB |= (0x0D<<4);										//Set BSCALE to -3 for baud 115200
	USARTC0.BAUDCTRLA |= (0x83);										//Set BSEL to 131 for baud 115200

	USARTC0.CTRLC |= (0x03);											//Sets amount of data bits to 8
	USARTC0.CTRLB |= (0x03<<3);											//Sets the Rx and TX enable bits
}

uint8_t check_UART(void)
{
	if(((USARTC0.STATUS)&(0x80))==1)									//Check DATA ready interrupt flag
	{
		return 1;														//Data ready to be read
	}
	
	else
	{
		return 0;														//No Data in DATA register to be read
	}
}

uint8_t read_UART(void)
{
	uint8_t data;
	while(((USARTC0.STATUS)&(0x80))==0)									//Wait for DATA buffer to fill
	{
		//Do Nothing
	}
	
	data = USARTC0.DATA;												//read 8 data bits
	USARTC0.STATUS |= (0x80);											//Clear DATA ready to read flag
	
	return data;
}

void write8_UART(uint8_t data)
{
	USARTC0.DATA = data;												//Write data to DATA register
	while(((USARTC0.STATUS)&(0x40))==0)									//Wait for DATA buffer to be written
	{
		//Do nothing
	}
		
	USARTC0.STATUS |= (0x40);											//Clear DATA written IR flag
}

void writeF_UART(float data)
{
	uint8_t *sendarray = (uint8_t*)(&data);								//converts float to 4 separate bytes in send array
	write8_UART(sendarray[0]);											//Sends separate bytes (LF)
	write8_UART(sendarray[1]);
	write8_UART(sendarray[2]);
	write8_UART(sendarray[3]);
}