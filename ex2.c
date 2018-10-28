#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/*
 * Declaration of peripheral setup functions
 */
void setupTimer();
void setupDAC();
void setupNVIC();
void setupGPIO();

/*
 * Declaration of music playing functions
 */
void playMelody(uint16_t length, int (*noteTable)(uint16_t));
void playMelodyAlternative(uint16_t length, int (*noteTable)(uint16_t));

int notesStartup(uint16_t noteCounter);
int notesStarWars(uint16_t noteCounter);
int notesSound1(uint16_t noteCounter);
int notesSound2(uint16_t noteCounter);
int notesSound3(uint16_t noteCounter);

/*
 * Your code will start executing here 
 */
int main(void)
{
	/*
	 * Call the peripheral setup functions 
	 */
	setupGPIO();
	setupDAC();
	setupTimer();

	playMelody(16, notesStartup);

	while (1)
	{	
		uint8_t buttons = ~(*GPIO_PC_DIN);
		
		if (buttons & 8)
		{
			*GPIO_PA_DOUT = 0x0800;
			playMelody(124, notesSound1);
			*GPIO_PA_DOUT = 0xff00;
		}
		else if (buttons & 4)
		{
			*GPIO_PA_DOUT = 0x0400;
			playMelody(132, notesSound2);
			*GPIO_PA_DOUT = 0xff00;
		}
		else if (buttons & 2)
		{
			*GPIO_PA_DOUT = 0x0200;
			playMelody(41, notesSound3);
			*GPIO_PA_DOUT = 0xff00;
		}
		else if (buttons & 1)
		{
			*GPIO_PA_DOUT = 0x0100;
			playMelody(56, notesStarWars);
			*GPIO_PA_DOUT = 0xff00;
		}
	}
	return 0;
}
