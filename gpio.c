#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/*
 * function to set up GPIO mode and interrupts
 */
void setupGPIO()
{
	/* enable GPIO clock */
	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;

	/* set low drive strength */
	*GPIO_PA_CTRL = 1;

	/* set pins A8-15 as output */
	*GPIO_PA_MODEH = 0x55555555;

	/* set pins C8-15 as input */
	*GPIO_PC_MODEL = 0x33333333;

	/* enable pullup resistors */
	*GPIO_PC_DOUT = 0xff;

	/* set LEDS initially low */
	*GPIO_PA_DOUT = 0xff00;
}
