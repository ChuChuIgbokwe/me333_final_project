#include "isense.h"
#include "NU32.h"

#define SAMPLE_TIME 10       // 10 core timer ticks = 250 ns
#define AVERAGE_SAMPLES 100 // number of ADCs to be avaraged

unsigned int adc_sample_convert(int pin) { // sample and convert the value on the given adc pin
                                           // the pin should be configured as an analog input in
                                           // AD1PCFG
    unsigned int elapsed = 0, finish_time = 0;
    AD1CHSbits.CH0SA = pin;                // connect pin AN14 to MUXA for sampling
    AD1CON1bits.SAMP = 1;                  // start sampling
    elapsed = _CP0_GET_COUNT();
    finish_time = elapsed + SAMPLE_TIME;
    while (_CP0_GET_COUNT() < finish_time) { 
      ;                                   // sample for more than 250 ns
    }
    AD1CON1bits.SAMP = 0;                 // stop sampling and start converting
    while (!AD1CON1bits.DONE) {
      ;                                   // wait for the conversion process to finish
    }
    return ADC1BUF0;                      // read the buffer with the result
}

void isense_init()     // initialize the current sensor
{
	  AD1PCFGbits.PCFG0 = 0;                  // AN0 is an adc pin
	  AD1CON3bits.ADCS = 2;                   // ADC clock period is Tad = 2*(ADCS+1)*Tpb =
	                                          //                           2*3*12.5ns = 75ns
	  AD1CON1bits.ADON = 1;                   // turn on A/D converter

}


short isense_ticks()   // read the current sensor, in ADC ticks
{
	int adcval = 0;
	int i = 0;
	for (i = 0; i < AVERAGE_SAMPLES; ++i)
	{
		adcval += adc_sample_convert(0);	// use D0 of AN0
	}
	return adcval/AVERAGE_SAMPLES;
}


int isense_amps()      // read the current sensor, in mA
{

}

