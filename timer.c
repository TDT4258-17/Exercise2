#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/*
 * function to setup the timer 
 */
void setupTimer()
{
	/* enable clock to timer module */
	*CMU_HFPERCLKEN0 |= 0b01000000;

	/* set period between interrupts 1st method */
	*TIMER1_TOP = 0xffff;

	/* start timer1 */
	*TIMER1_CMD = 1;					

	/* Set timer1 prescalar to 32 for timer frequency of 437500 */
	*TIMER1_CTRL &= 0xf0ffffff;
	*TIMER1_CTRL |= 0x05000000;
}
