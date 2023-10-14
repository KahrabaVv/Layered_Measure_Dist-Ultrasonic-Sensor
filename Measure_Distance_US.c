/*
 * Measure_Distance_US.c
 *
 *  Created on: Oct 12, 2023
 *      Author: Kerolossamehel-shaip
 */
#include <avr/io.h>
#include "icu.h"
#include "lcd.h"
#include "ultra.h"

uint16 sum=0;
int main()
{
	SREG |= (1<<7);
	LCD_init();
	Ultrasonic_init();

	LCD_displayString("Distance =    ");
	while(1)
	{
	 sum=Ultrasonic_readDistance();


		LCD_moveCursor(0,11);
		/* display the distance on LCD screen */
		LCD_intgerToString(sum);
		LCD_displayString("cm ");

	}
}
