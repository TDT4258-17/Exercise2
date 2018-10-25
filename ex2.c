#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "notes.h"

/*
 * TODO calculate the appropriate sample period for the sound wave(s) you 
 * want to generate. The core clock (which the timer clock is derived
 * from) runs at 14 MHz by default. Also remember that the timer counter
 * registers are 16 bits. 
 */
/*
 * The period between sound samples, in clock cycles (not Hz)
 */
#define   SAMPLE_PERIOD   311 // which gives us 45 KHz

/*
 * Declaration of peripheral setup functions 
 */
void setupTimer(uint32_t period);
void setupDAC();
void setupNVIC();
void setupGPIO();

/*
 * Your code will start executing here 
 */
int playStarWars(uint16_t songCounter)
{
	switch(songCounter)
	{
		case 0: return NOTE_F4;			
		case 1;	return NOTE_F4;
		case 2: return NOTE_GS4;
		case 3: return NOTE_GS4;
		case 4: return NOTE_GS4;
		case 5: return NOTE_GS4;
		case 6: return NOTE_F4;
		case 7: return NOTE_F4;
		case 6: return NOTE_F4;
		case 2: return 
		case 2: return 
	}
}

 void startupMelody() {
 	uint16_t note = 1; // 1 means mute
	
	for( uint32_t startMelodyCounter = 0; startMelodyCounter<135000 ; startMelodyCounter++ ) // 3 seconds startup melody
	{
		/* SAMPLING PART */
		//Busy wait
		uint16_t samplingTimer = *TIMER1_CNT; 
		while(*TIMER1_CNT<SAMPLE_PERIOD){
			samplingTimer = *TIMER1_CNT;
		}
		// note frequency in terms of sampling frequency
		*TIMER1_CNT = 0;

 		/* NOTE PART */
 		uint16_t noteFreqMaxCount = 45000 / note; //we are calculating the frequency in terms of the sampling frequency
		
 			if (startMelodyCounter % NoteFreqMaxCount = 0){
				
				if (toggle){
					// mute if note is 1
					if(note!=1)
					{ 
						*DAC0_CH0DATA = 512;
					}
					toggle = false;
				}
				else{
					*DAC0_CH0DATA = 0;
					toggle = true;
				}
			}
		// each note is activated for 0.125 seconds or 5625 samples
		uint16_t songNoteMaxCount = 5625;
		uint16_t songCounter = startMelodyCounter / NoteFreqMaxCount;
		if (startMelodyCounter % NoteFreqMaxCount = 0){

			note = playStarWars(songCounter)

		}


			
		
		playTune(NOTE_G3,20000)	
			
 	}
}

int main(void)
{
	/*
	 * Call the peripheral setup functions 
	 */
	setupGPIO();
	setupDAC();
	setupTimer(SAMPLE_PERIOD);

	/*
	 * Enable interrupt handling 
	 */
	setupNVIC();

	/*
	 * TODO for higher energy efficiency, sleep while waiting for
	 * interrupts instead of infinite loop for busy-waiting 
	 */
	 bool toggle = false;
	while (1) {
		sample();

		uint16_t samplingTimer = *TIMER1_CNT;
		if (samplingTimer > SAMPLE_PERIOD){
			// Sample
			*TIMER1_CNT = 0;
			
			uint16_t noteMaxCount = 45000 / note;
 			if (noteCounter > NoteMaxCount){
				
				if (toggle){
					*DAC0_CH0DATA = 512;
					toggle = false;
				}
				else{
					*DAC0_CH0DATA = 0;
					toggle = true;
				}
			}	 	
		}

	}

	return 0;
}

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
	 
	 *ISER0 = 0x802 ;		// enable timer interrupt (bit 12) and GPIO interrupt (bit 11)
	 *GPIO_EXTIPSELL = 0x22222222;
	 *GPIO_IEN = 0xff;
	 *GPIO_EXTIFALL = 0xff;
	 *GPIO_EXTIRISE = 0xff;
	 *GPIO_IFC = *GPIO_IF;
	 
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
