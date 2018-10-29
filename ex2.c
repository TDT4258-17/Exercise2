#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/*
 * TODO calculate the appropriate sample period for the sound wave(s) you 
 * want to generate. The core clock (which the timer clock is derived
 * from) runs at 14 MHz by default. Also remember that the timer counter
 * registers are 16 bits. 
 */
 
//static int8_t sine_signed[32] = {0, 25, 49, 71, 90, 106, 117, 125, 127, 125, 117, 106, 90, 71, 49, 25, 0, -25, -49, -71, -90, -106, -117, -125, -127, -125, -117, -106, -90, -71, -49, -25};
//static uint8_t sine_unsigned[] = {127, 152, 176, 198, 217, 233, 244, 252, 254, 252, 244, 233, 217, 198, 176, 152, 127, 102, 78, 56, 37, 21, 10, 2, 0, 2, 10, 21, 37, 56, 78, 102 };

/*
 * Declaration of peripheral setup functions 
 */
void setupTimer();
void setupDAC();
void setupNVIC();
void setupGPIO();

int notesStartup(uint16_t songCounter);
void playMelody(uint16_t length, int (*noteTable)(uint16_t));

void startTimer();
void stopTimer();

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
	
	playMelody(8, notesStartup);
	
	stopTimer();
	setupTimer();

	/*
	 * Enable interrupt handling 
	 */
	
	setupNVIC();
	
	/*
	 * TODO for higher energy efficiency, sleep while waiting for
	 * interrupts instead of infinite loop for busy-waiting 
	 */
	 
	*SCR |= 0x02; // enable automatic return to sleep after return from ISR
	
	while (1)
	{
		__asm volatile ("wfi"); // Finally, this worked.
	}

	return 0;
}


//		wfi;
//		WFI;
//		WFI();
//		wfi();
//		__wfi();
//		_wfi();
//		__WFI();
//		asm("wfi");
//		__asm("wfi"); // Finally, this worked.

void setupNVIC()
{
	/*
	 * TODO use the NVIC ISERx registers to enable handling of
	 * interrupt(s) remember two things are necessary for interrupt
	 * handling: - the peripheral must generate an interrupt signal - the
	 * NVIC must be configured to make the CPU handle the signal You will
	 * need TIMER1, GPIO odd and GPIO even interrupt handling for this
	 * assignment. 
	 */
	 
	*ISER0 |=  0x802;	// Enable even and odd GPIO interrupts
	*ISER0 |= 0x1000;	// Enable TIMER1 interrupts
	
	*GPIO_EXTIPSELL = 0x22222222;
	*GPIO_IEN = 0xff;
	*GPIO_EXTIFALL = 0xff;
	*GPIO_EXTIRISE = 0xff;
	*GPIO_IFC = *GPIO_IF;
	
	*TIMER1_IEN = 1;
	*TIMER1_IFC = *TIMER1_IF;
}

/*
 * if other interrupt handlers are needed, use the following names:
 * NMI_Handler HardFault_Handler MemManage_Handler BusFault_Handler
 * UsageFault_Handler Reserved7_Handler Reserved8_Handler
 * Reserved9_Handler Reserved10_Handler SVC_Handler DebugMon_Handler
 * Reserved13_Handler PendSV_Handler SysTick_Handler DMA_IRQHandler
 * GPIO_EVEN_IRQHandler TIMER0_IRQHandler USART0_RX_IRQHandler
 * USART0_TX_IRQHandler USB_IRQHandler ACMP0_IRQHandler ADC0_IRQHandler
 * DAC0_IRQHandler I2C0_IRQHandler I2C1_IRQHandler GPIO_ODD_IRQHandler
 * TIMER1_IRQHandler TIMER2_IRQHandler TIMER3_IRQHandler
 * USART1_RX_IRQHandler USART1_TX_IRQHandler LESENSE_IRQHandler
 * USART2_RX_IRQHandler USART2_TX_IRQHandler UART0_RX_IRQHandler
 * UART0_TX_IRQHandler UART1_RX_IRQHandler UART1_TX_IRQHandler
 * LEUART0_IRQHandler LEUART1_IRQHandler LETIMER0_IRQHandler
 * PCNT0_IRQHandler PCNT1_IRQHandler PCNT2_IRQHandler RTC_IRQHandler
 * BURTC_IRQHandler CMU_IRQHandler VCMP_IRQHandler LCD_IRQHandler
 * MSC_IRQHandler AES_IRQHandler EBI_IRQHandler EMU_IRQHandler 
 */


