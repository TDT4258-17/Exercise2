#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

void startTimer()
{
	*TIMER1_CNT = 0;
	// TIMER1_CMD is a write only register
	*TIMER1_CMD = 1;		// start timer1
}

void stopTimer()
{
	// TIMER1_CMD is a write only register
	*TIMER1_CMD = 2;		// stop timer1
}

void setupTimerForInterrupts()
{
	*TIMER1_CMD = 2;
	*CMU_HFPERCLKEN0 |= 0b01000000;	// set enable clock to timer module
	*TIMER1_CTRL &= 0xf0ffffff;
	*TIMER1_TOP = 1750;		// => 8 KHz frequency
//	*TIMER1_TOP = 7000;		// => 2 KHz frequency
//	*TIMER1_TOP = 28000;	// => 500 Hz frequency
	*TIMER1_CMD = 1;		// start timer1
}

void setupTimerForStartup()
{
	*CMU_HFPERCLKEN0 |= 0b01000000;	// set enable clock to timer module
	*TIMER1_TOP = 0xffff;
	*TIMER1_CTRL &= 0xf0ffffff;
	*TIMER1_CTRL |= 0x05000000;
	*TIMER1_CMD = 1;		// start timer1
}

