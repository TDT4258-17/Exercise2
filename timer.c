#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

void startTimer()
{
	// TIMER1_CMD is a write only register
	*TIMER1_CMD = 1;		// start timer1
}

/*
 * function to setup the timer 
 */
 
void setupTimer()
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
	*TIMER1_TOP = 317;		// set period between interrupts.
							//    317 times 14MHz cycles 
							// => 44.16403785 KHz frequency, closest to 44.100 KHz
 
}
