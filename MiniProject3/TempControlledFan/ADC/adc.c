/*
 * adc.c
 *
 *  Created on: Oct 6, 2023
 *      Author: Mahmoud Khalafallah
 */

#include "adc.h"
#include "../common_macros.h"
#include "../GPIO/gpio.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*
 * Description:
 * ADC Initialization
 * takes a structure of the configuration details
 * defining prescaler and reference voltage
 * set the channel to be zero by default
 */
void ADC_init(const ADC_ConfigType * a_configurations) {

	ADMUX = (a_configurations->ref_volt) << 6 ;
	ADCSRA = ((ADCSRA & 0xF8) | a_configurations->prescaler) | 1<<ADEN;
}

/*
 * Description:
 * reading the analog value on a certain channel
 * takes the number of the channel
 * waits until the controller converts the analog value to digital value
 * returns the digital value
 */
uint16 ADC_readChannel(uint8 a_channelNum) {

	a_channelNum &= 0x1F;

	ADMUX &= 0xE0;

	ADMUX |= a_channelNum;

	SET_BIT(ADCSRA, ADSC);

	LOOP_UNTIL_BIT_IS_SET(ADCSRA, ADIF);

	SET_BIT(ADCSRA,ADIF);

	return ADC;
}
