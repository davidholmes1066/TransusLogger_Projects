#include <avr/io.h>
#include <stdint.h>

#define INTVCC 2.114										//VCC / 1.6 (Measure VCC and calibrate parameter)
#define ADCOFFSET 170											//Measure ADC offset and adjust parameter
#define NAVRAGE 30


#ifndef ADC_H_
#define ADC_H_


void init_ADC(void);
uint16_t read_ADC(uint8_t MeasurementParameter);
float read_ADCV(uint8_t MeasurementParameter);


#endif /* ADC_H_ */