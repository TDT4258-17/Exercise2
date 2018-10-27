#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

bool needNewDacData = false;

static inline void GPIO_IRQHandler()
{
	*GPIO_IFC = *GPIO_IF;
	*GPIO_PA_DOUT = (*GPIO_PC_DIN) << 8;
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
 	needNewDacData = true;
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
