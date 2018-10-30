#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

bool needNewDacData = false;
uint8_t soundPlaying = 0; //Variable that hold info about what sound is playing right now. 0: no sound is playing 1: sound 1 is playing etc.
static uint32_t sampleIndex = 0;

extern uint8_t song1[];
extern uint16_t song1Size;
extern uint8_t song2[];
extern uint16_t song2Size;
extern uint8_t effect1[];
extern uint16_t effect1Size;

void startTimer();

static inline void GPIO_IRQHandler()
{
	*GPIO_IFC = *GPIO_IF;
	
	if (soundPlaying == 0)
	{
		uint8_t button = ~(*GPIO_PC_DIN);
		if (button & 1)
		{
			soundPlaying = 1;
			*GPIO_PA_DOUT = ~(1 << 8);
			// Start timer1
			*TIMER1_CMD = 1;
		}
		else if (button & 2)
		{
			soundPlaying = 2;
			*GPIO_PA_DOUT = ~(1 << 9);
			// Start timer1
			*TIMER1_CMD = 1;
		}
		else if (button & 4)
		{
			soundPlaying = 3;
			*GPIO_PA_DOUT = ~(1 << 10);
			// Start timer1
			*TIMER1_CMD = 1;
		}
		
	}
}

static inline void soundPlayDone()
{
	*GPIO_PA_DOUT = 0xff00;
	sampleIndex = 0;
	soundPlaying = 0;
	*TIMER1_CNT = 0;
	// Stop timer1
	*TIMER1_CMD = 2;
}

/*
 * TIMER1 interrupt handler 
 */
void __attribute__ ((interrupt)) TIMER1_IRQHandler()
{
	/*
	 * TODO feed new samples to the DAC remember to clear the pending
	 * interrupt by writing 1 to TIMER1_IFC 
	 */
	
 	*TIMER1_IFC = *TIMER1_IF;
 	if (soundPlaying == 1)
	{
		*DAC0_CH0DATA = effect1[sampleIndex];
		*DAC0_CH1DATA = effect1[sampleIndex];
	 	sampleIndex++;
		
		if (sampleIndex > effect1Size)
		{
			soundPlayDone();
		}
	}
	
	else if (soundPlaying == 2)
	{
		*DAC0_CH0DATA = song2[sampleIndex];
		*DAC0_CH1DATA = song2[sampleIndex];
	 	sampleIndex++;
		
		if (sampleIndex > song2Size)
		{
			soundPlayDone();
		} 
	}
	else if (soundPlaying == 3)
 	{
		*DAC0_CH0DATA = song1[sampleIndex/4]; // song1 has sample rate 2000Hz, one fourth of the others
		*DAC0_CH1DATA = song1[sampleIndex/4];
	 	sampleIndex++;
	
		if (sampleIndex/4 > song1Size)
		{
			soundPlayDone();
		} 	
	}
}

/*
 * GPIO even pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	/*
	 * TODO handle button pressed event, remember to clear pending
	 * interrupt 
	 */
	 
	GPIO_IRQHandler();
	 
}

/*
 * GPIO odd pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	/*
	 * TODO handle button pressed event, remember to clear pending
	 * interrupt 
	 */
	 
	GPIO_IRQHandler();
	 
}
