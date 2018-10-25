#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/*
 * function to setup the timer 
 */
void setupTimer(uint16_t period)
{
	/*
	 * TODO enable and set up the timer
	 * 
	 * 1. Enable clock to timer by setting bit 6 in CMU_HFPERCLKEN0 2.
	 * Write the period to register TIMER1_TOP 3. Enable timer interrupt
	 * generation by writing 1 to TIMER1_IEN 4. Start the timer by writing 
	 * 1 to TIMER1_CMD
	 * 
	 * This will cause a timer interrupt to be generated every (period)
	 * cycles. Remember to configure the NVIC as well, otherwise the
	 * interrupt handler will not be invoked. 
	 */
	 
	 *CMU_HFPERCLKEN0 |= 0b01000000;	// set enable clock to timer module
	 *TIMER1_TOP = 0xffff;				// set period between interrupts 1st method
	 //*TIMER1_TOP = period;			// set period between interrupts 2nd method
	 //*TIMER1_IEN = 1;					// enable timer interrupt
	 *TIMER1_CMD = 1;					// start timer1
	 // The prescalar is set to 0 
	 // *TIMER1_CTRL |= 0x00000000;		// set prescalar to A
	 
//	 *TIMER2_TOP = 0xffff;				// set period between interrupts 1st method
	 //*TIMER1_TOP = period;			// set period between interrupts 2nd method
	 //*TIMER1_IEN = 1;					// enable timer interrupt
//	 *TIMER2_CMD = 1;					// start timer1
	 // The prescalar is set to 0 
//	 *TIMER2_CTRL &= 0xf0ffffff;		// set prescalar to A
//	 *TIMER2_CTRL |= 0x05000000;		// set prescalar to A	 
}
