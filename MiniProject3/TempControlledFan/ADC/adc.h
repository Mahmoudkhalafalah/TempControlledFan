/************************************************************************************
 * Module: ADC
 *
 * File Name: adc.b
 *
 * Description: header file for the AVR ADC driver
 *
 * Author: Mahmoud Khalafallah
 *
 ************************************************************************************/
#ifndef ADC_H_
#define ADC_H_

#include "../std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_REFRENCE_VOLTAGE 2.56
#define ADC_MAXIMUM_VALUE 1023

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum {
	AREF, AVCC, INTERNAL_VREF = 3
} ADC_ReferenceVolatge;

typedef enum {
	F_CPU_2=1, F_CPU_4, F_CPU_8, F_CPU_16, F_CPU_32,F_CPU_64,F_CPU_128
} ADC_Prescaler;

typedef struct {
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
} ADC_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*
 * Description:
 * ADC Initialization
 * takes a structure of the configuration details
 * defining prescaler and reference voltage
 * set the channel to be zero by default
 */
void ADC_init(const ADC_ConfigType * a_configurations);
/*
 * Description:
 * reading the analog value on a certain channel
 * takes the number of the channel
 * waits until the controller converts the analog value to digital value
 * returns the digital value
 */
uint16 ADC_readChannel(uint8 a_channelNumber);

#endif /* ADC_H_ */
