/*
 * main.c
 *
 *  Created on: Oct 13, 2023
 *      Author: Mahmoud Khalafallah
 */

#include "LCD/lcd.h"
#include "ADC/adc.h"
#include "LM35/lm35.h"
#include "Motor/motor.h"

int main(void) {

	LCD_Init(); /* initializing lcd */
	ADC_ConfigType configurations = { INTERNAL_VREF, F_CPU_8 }; /*define configurations for adc*/
	ADC_init(&configurations); /* initializing adc */
	DCMotor_init(); /* initializing motor */
	uint8 temperature = LM35_getTemperature(); /*define variable for temperature and give it the initial temp*/
	uint8 fanIsON = FALSE; /*defining a variable for fan state*/
	LCD_SetCursor(0, 4);
	LCD_displayString("FAN is ");
	LCD_SetCursor(1, 4);
	LCD_displayString("TEMP = ");
	while (1) {
		/*read the temperature*/
		temperature = LM35_getTemperature();

		/*
		 * depending on temperature:
		 * the fan changes the speed
		 */
		if (temperature >= 90) {
			fanIsON = TRUE;
			DCMotor_rotate(CLOCK_WISE, MOTOR_THREE_QUARTERS_SPEED);
		} else if (temperature >= 60) {
			fanIsON = TRUE;
			DCMotor_rotate(CLOCK_WISE, MOTOR_HALF_SPEED);
		} else if (temperature >= 30) {
			fanIsON = TRUE;
			DCMotor_rotate(CLOCK_WISE, MOTOR_QUARTER_SPEED);
		} else {
			fanIsON = FALSE;
			DCMotor_rotate(STOP, 0);
		}
		/* displaying fan state*/
		LCD_SetCursor(0, 11);
		LCD_displayString((fanIsON) ? "ON " : "OFF");
		/*displaying temperature*/
		LCD_SetCursor(1, 11);
		LCD_PrintNum16Bit(temperature);
		LCD_displayString(" C  ");
	}
}
