/*
 * handle.h
 *
 * Created: 13/12/2023 12:25:49
 *  Author: david
 */ 
#include <avr/io.h>
#include "ADC.h"
#include "DAC.h"

#define Is (17.0/1000)
#define Itollerance (0.5/1000)


#ifndef HANDLE_H_
#define HANDLE_H_

void manage_BatCurrent(void);



#endif /* HANDLE_H_ */