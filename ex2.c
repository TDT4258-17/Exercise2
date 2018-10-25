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
#define   SAMPLE_PERIOD   311

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
 uint32_t sample(uint32_t counter)
 {
 	//busy wait
 	while(*TIMER1_CNT<SAMPLE_PERIOD){}
 	
 	uint16_t samplingTimer = *TIMER1_CNT;
		if (samplingTimer > SAMPLE_PERIOD){
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
 void buzzNote(int note,int duration)
 {
 	uint16_t maxCount = 45000 / note;
 	uint16_t counter = *TIMER1_CNT;
 	if (counter > maxCount){
			*TIMER1_CNT = 0;
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
 void playTune(int note)
 {
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
 void startupMelody() {
 	uint16_t note = 0;
	
	for( uint32_t startMelodyCounter = 0; startMelodyCounter<135000 ; startMelodyCounter++ ) // 3 seconds startup melody
	{
		//Busy wait
		uint16_t samplingTimer = *TIMER1_CNT; 
		while(*TIMER1_CNT<SAMPLE_PERIOD){
			samplingTimer = *TIMER1_CNT;
		}
		// note frequency in terms of sampling frequency
 		
 		uint16_t noteFreqMaxCount = 45000 / note;
		
 			if (noteFreqCounter > NoteFreqMaxCount){
				
				if (toggle){
					// mute if note is 0
					if(note!=0)
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
		uint16_t songNoteMaxCount = 5625
			
		*TIMER1_CNT = 0;
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
