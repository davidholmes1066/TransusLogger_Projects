#include <avr/io.h>

#define Rs 51.0
#define AVCC 3.4					//Analog VCC
#define Vf 0.45						//Forward voltage base-emitter


#ifndef DAC_H_
#define DAC_H_

void init_DAC(void);
void write_DAC(uint16_t Data, uint8_t channel);



#endif /* DAC_H_ */