/*
 * ultra.c
 *
 *  Created on: Oct 12, 2023
 *      Author: Kerolossamehel-shaip
 */

#include <avr/interrupt.h>
#include <util/delay.h>
#include "gpio.h"
#include "ultra.h"
#include "icu.h"

uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 distance=0;


Ultrasonic_init(void){
	ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};
	ICU_init(&ICU_Configurations);
	ICU_setEdgeDetectionType(RAISING);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_LOW);
}
Ultrasonic_Trigger(void){
	/*another method*/
	/*GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_HIGH);

	_delay_us(10);
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_LOW);*/

	TCNT0 = 0; // Set Timer Initial Value 0
	OCR0 = 10; // Set Compare Value

	TIMSK |= (1<<OCIE0); // Enable Timer0 Compare Interrupt

	/* Configure timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. CTC Mode WGM01=1 & WGM00=0
	 * 3. No need for OC0 in this example so COM00=0 & COM01=0
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<FOC0) | (1<<WGM01) | (1<<CS01);
}

uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();

	return	distance=g_timeHigh/58+1;


}
Ultrasonic_edgeProcessing(void){
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_clearTimerValue();
		/* Detect falling edge */
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = ICU_getInputCaptureValue();
		/* Detect rising edge */
		ICU_clearTimerValue();

		ICU_setEdgeDetectionType(RAISING);
		g_edgeCount=0;
	}


}

unsigned char g_tick = 0;


ISR(TIMER0_COMP_vect)
{

	g_tick++;
	if(g_tick==1){
	PORTB ^= (1<<PB5);}

	else{
		PORTB &= ~(1<<PB5);
		TCCR0 =0;
		g_tick=0;}


}
