#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
 
//static int8_t sine_signed[32] = {0, 25, 49, 71, 90, 106, 117, 125, 127, 125, 117, 106, 90, 71, 49, 25, 0, -25, -49, -71, -90, -106, -117, -125, -127, -125, -117, -106, -90, -71, -49, -25};
//static uint8_t sine_unsigned[] = {127, 152, 176, 198, 217, 233, 244, 252, 254, 252, 244, 233, 217, 198, 176, 152, 127, 102, 78, 56, 37, 21, 10, 2, 0, 2, 10, 21, 37, 56, 78, 102 };

/* Declaration of peripheral setup functions */
void setupGPIO();
void setupDAC();
void setupTimerForStartup();
void setupTimerForInterrupts();
void setupNVIC();

int notesStartup(uint16_t songCounter);
void playMelody(uint16_t length, int (*noteTable)(uint16_t));

void startTimer();
void stopTimer();


int main(void)
{
	/* Calling the peripheral setup functions */
	setupGPIO();
	setupDAC();
	setupTimerForStartup();

	playMelody(12, notesStartup);
	
	setupTimerForInterrupts();
	setupNVIC();	// Enable interrupt handling
	 
	*SCR |= 0x02; // enable automatic return to sleep after return from ISR
	
	while (1)
	{
		__asm ("wfi"); // Finally, this worked.
	}

	return 0;
}

void setupNVIC()
{
	*ISER0 |=  0x802;	// Enable even and odd GPIO interrupts
	*ISER0 |= 0x1000;	// Enable TIMER1 interrupts
	
	*GPIO_EXTIPSELL = 0x22222222;	// Choose Port C bits for interrupt generation
	*GPIO_IEN = 0xff;				// Enable GPIO interrupts for 8 least sig bits
	*GPIO_EXTIFALL = 0xff;			// generate interrupt at falling edge
	*GPIO_EXTIRISE = 0xff;			// generate interrupt at rising edge
	
	*TIMER1_IEN = 1;				// Enable interrupts for 8 least sig bits

	*TIMER1_IFC = *TIMER1_IF;		// Initially clear interrupt flags
	*GPIO_IFC = *GPIO_IF;
}
