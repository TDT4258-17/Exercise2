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

static int8_t sine_signed[32] = {0, 25, 49, 71, 90, 106, 117, 125, 127, 125, 117, 106, 90, 71, 49, 25, 0, -25, -49, -71, -90, -106, -117, -125, -127, -125, -117, -106, -90, -71, -49, -25};
static uint8_t sine_unsigned[32] = {127, 152, 176, 198, 217, 233, 244, 252, 254, 252, 244, 233, 217, 198, 176, 152, 127, 102, 78, 56, 37, 21, 10, 2, 0, 2, 10, 21, 37, 56, 78, 102 };

/*
 * Declaration of peripheral setup functions 
 */
void setupTimer(uint32_t period);
void setupDAC();
void setupNVIC();
void setupGPIO();

int notesStarWars(uint16_t songCounter);
int notesSound1(uint16_t songCounter);
int notesSound2(uint16_t songCounter);
int notesSound3(uint16_t songCounter);

void playMelody(uint8_t sound);

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
	setupTimer(SAMPLE_PERIOD);

	/*
	 * Enable interrupt handling 
	 */
	setupNVIC();

	playMelody(0);

	/*
	 * TODO for higher energy efficiency, sleep while waiting for
	 * interrupts instead of infinite loop for busy-waiting 
	 */
	// bool toggle = false;

	while (1)
	{	
		//startupMelody();
		uint16_t buttons = *GPIO_PC_DIN;

		if (buttons >= 4)
		{
			playMelody(1);
		}
		else if (buttons >= 2)
		{
			playMelody(2);
		}
		else if (buttons >= 1)
		{
			playMelody(3);
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


void playMelody(uint8_t sound)
{
	uint16_t note = 1; // 1 means mute
	bool toggle = false;
	
	for ( uint32_t startMelodyCounter = 0; startMelodyCounter < 315000 ; startMelodyCounter++ ) // 7 seconds startup melody
	{
		/* SAMPLING PART */
		uint16_t samplingTimer = *TIMER1_CNT; 
		while (samplingTimer < SAMPLE_PERIOD)
		{//Busy wait
			samplingTimer = *TIMER1_CNT;
		}
		// note frequency in terms of sampling frequency
		*TIMER1_CNT = 0;

		/* NOTE PART */
		uint16_t noteFreqMaxCount = 45000 / note; //we are calculating the frequency in terms of the sampling frequency
		
		if (startMelodyCounter % noteFreqMaxCount == 0)
		{
			if (toggle)
			{
				// mute if note is 1
				if (note != 1)
				{
					*DAC0_CH0DATA = 512;
				}
				toggle = false;
			}
			else
			{
				*DAC0_CH0DATA = 0;
				toggle = true;
			}
		}
		// each note is activated for 0.125 seconds or 5625 samples
		uint16_t songNoteMaxCount = 5625;
		uint16_t songCounter = startMelodyCounter / songNoteMaxCount;

		if (startMelodyCounter % songNoteMaxCount == 0)
		{
			switch (sound)
			{
				case 0:
					note = notesStarWars(songCounter);
				break;
				case 1:
					note = notesSound1(songCounter);
				break;
				case 2:
					note = notesSound2(songCounter);
				break;
				case 3:
					note = notesSound3(songCounter);
				break;

			}
			
		}
	}
}

int notesStarWars(uint16_t songCounter)
{
	switch(songCounter)
	{
		case 0: return NOTE_F4;			
		case 1:	return NOTE_F4;
		case 2: return NOTE_GS4;
		case 3: return NOTE_GS4;
		case 4: return NOTE_GS4;
		case 5: return NOTE_GS4;
		case 6: return NOTE_F4;
		case 7: return NOTE_F4;
		case 8: return NOTE_F4;
		case 9: return NOTE_A4;
		case 10: return NOTE_C5;
		case 11: return NOTE_C5;
		case 12: return NOTE_C5;
		case 13: return NOTE_C5;
		case 14: return NOTE_A4;
		case 15: return NOTE_A4;
		case 16: return NOTE_A4;
		case 17: return NOTE_C5;
		case 18: return NOTE_E5;
		case 19: return NOTE_E5;
		case 20: return NOTE_E5;
		case 21: return NOTE_E5;
		case 22: return NOTE_E5;
		case 23: return 1;
		case 24: return 1;
		case 25: return 1;
		case 26: return 1;
		case 27: return NOTE_F4;			
		case 28: return NOTE_F4;
		case 29: return NOTE_GS4;
		case 30: return NOTE_GS4;
		case 31: return NOTE_GS4;
		case 32: return NOTE_GS4;
		case 33: return NOTE_F4;
		case 34: return NOTE_F4;
		case 35: return NOTE_F4;
		case 36: return NOTE_C5;
		case 37: return NOTE_A4;
		case 38: return NOTE_A4;
		case 39: return NOTE_A4;
		case 40: return NOTE_A4;
		case 41: return NOTE_F4;
		case 42: return NOTE_F4;
		case 43: return NOTE_F4;
		case 44: return NOTE_C5;
		case 45: return NOTE_A4;
		case 46: return NOTE_A4;
		case 47: return NOTE_A4;
		case 48: return NOTE_A4;
		case 49: return NOTE_A4;

		default: return 1;
	}
}

int notesSound1(uint16_t songCounter)
{
	switch(songCounter)
	{
		case 0: return NOTE_F4;			
		case 1:	return NOTE_F4;
		case 2: return NOTE_GS4;
		case 3: return NOTE_GS4;
		case 4: return NOTE_GS4;
		case 5: return NOTE_GS4;
		case 6: return NOTE_F4;
		case 7: return NOTE_F4;
		case 8: return NOTE_F4;
		case 9: return NOTE_A4;
		case 10: return NOTE_C5;
		case 11: return NOTE_C5;
		case 12: return NOTE_C5;
		case 13: return NOTE_C5;
		case 14: return NOTE_A4;
		case 15: return NOTE_A4;
		case 16: return NOTE_A4;
		case 17: return NOTE_C5;
		case 18: return NOTE_E5;
		case 19: return NOTE_E5;
		case 20: return NOTE_E5;
		case 21: return NOTE_E5;
		case 22: return NOTE_E5;
		case 23: return 1;
		case 24: return 1;
		case 25: return 1;
		case 26: return 1;
		case 27: return NOTE_F4;			
		case 28: return NOTE_F4;
		case 29: return NOTE_GS4;
		case 30: return NOTE_GS4;
		case 31: return NOTE_GS4;
		case 32: return NOTE_GS4;
		case 33: return NOTE_F4;
		case 34: return NOTE_F4;
		case 35: return NOTE_F4;
		case 36: return NOTE_C5;
		case 37: return NOTE_A4;
		case 38: return NOTE_A4;
		case 39: return NOTE_A4;
		case 40: return NOTE_A4;
		case 41: return NOTE_F4;
		case 42: return NOTE_F4;
		case 43: return NOTE_F4;
		case 44: return NOTE_C5;
		case 45: return NOTE_A4;
		case 46: return NOTE_A4;
		case 47: return NOTE_A4;
		case 48: return NOTE_A4;
		case 49: return NOTE_A4;

		default: return 1;
	}
}

int notesSound2(uint16_t songCounter)
{
	switch(songCounter)
	{
		case 0: return NOTE_F4;			
		case 1:	return NOTE_F4;
		case 2: return NOTE_GS4;
		case 3: return NOTE_GS4;
		case 4: return NOTE_GS4;
		case 5: return NOTE_GS4;
		case 6: return NOTE_F4;
		case 7: return NOTE_F4;
		case 8: return NOTE_F4;
		case 9: return NOTE_A4;
		case 10: return NOTE_C5;
		case 11: return NOTE_C5;
		case 12: return NOTE_C5;
		case 13: return NOTE_C5;
		case 14: return NOTE_A4;
		case 15: return NOTE_A4;
		case 16: return NOTE_A4;
		case 17: return NOTE_C5;
		case 18: return NOTE_E5;
		case 19: return NOTE_E5;
		case 20: return NOTE_E5;
		case 21: return NOTE_E5;
		case 22: return NOTE_E5;
		case 23: return 1;
		case 24: return 1;
		case 25: return 1;
		case 26: return 1;
		case 27: return NOTE_F4;			
		case 28: return NOTE_F4;
		case 29: return NOTE_GS4;
		case 30: return NOTE_GS4;
		case 31: return NOTE_GS4;
		case 32: return NOTE_GS4;
		case 33: return NOTE_F4;
		case 34: return NOTE_F4;
		case 35: return NOTE_F4;
		case 36: return NOTE_C5;
		case 37: return NOTE_A4;
		case 38: return NOTE_A4;
		case 39: return NOTE_A4;
		case 40: return NOTE_A4;
		case 41: return NOTE_F4;
		case 42: return NOTE_F4;
		case 43: return NOTE_F4;
		case 44: return NOTE_C5;
		case 45: return NOTE_A4;
		case 46: return NOTE_A4;
		case 47: return NOTE_A4;
		case 48: return NOTE_A4;
		case 49: return NOTE_A4;

		default: return 1;
	}
}

int notesSound3(uint16_t songCounter)
{
	switch(songCounter)
	{
		case 0: return NOTE_F4;			
		case 1:	return NOTE_F4;
		case 2: return NOTE_GS4;
		case 3: return NOTE_GS4;
		case 4: return NOTE_GS4;
		case 5: return NOTE_GS4;
		case 6: return NOTE_F4;
		case 7: return NOTE_F4;
		case 8: return NOTE_F4;
		case 9: return NOTE_A4;
		case 10: return NOTE_C5;
		case 11: return NOTE_C5;
		case 12: return NOTE_C5;
		case 13: return NOTE_C5;
		case 14: return NOTE_A4;
		case 15: return NOTE_A4;
		case 16: return NOTE_A4;
		case 17: return NOTE_C5;
		case 18: return NOTE_E5;
		case 19: return NOTE_E5;
		case 20: return NOTE_E5;
		case 21: return NOTE_E5;
		case 22: return NOTE_E5;
		case 23: return 1;
		case 24: return 1;
		case 25: return 1;
		case 26: return 1;
		case 27: return NOTE_F4;			
		case 28: return NOTE_F4;
		case 29: return NOTE_GS4;
		case 30: return NOTE_GS4;
		case 31: return NOTE_GS4;
		case 32: return NOTE_GS4;
		case 33: return NOTE_F4;
		case 34: return NOTE_F4;
		case 35: return NOTE_F4;
		case 36: return NOTE_C5;
		case 37: return NOTE_A4;
		case 38: return NOTE_A4;
		case 39: return NOTE_A4;
		case 40: return NOTE_A4;
		case 41: return NOTE_F4;
		case 42: return NOTE_F4;
		case 43: return NOTE_F4;
		case 44: return NOTE_C5;
		case 45: return NOTE_A4;
		case 46: return NOTE_A4;
		case 47: return NOTE_A4;
		case 48: return NOTE_A4;
		case 49: return NOTE_A4;

		default: return 1;
	}
}