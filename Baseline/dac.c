#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

void setupDAC()
{
	/* enable DAC peripheral clock */
	*CMU_HFPERCLKEN0 = *CMU_HFPERCLKEN0 | 0x20000;

	/* Prescale DAC clock */
	*DAC0_CTRL = 0x50010;

	/* enable channel 0 */
	*DAC0_CH0CTRL = 1;

	/* enable channel 1 */
	*DAC0_CH1CTRL = 1;
}
