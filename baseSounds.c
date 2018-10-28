#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "notes.h"

#define   SAMPLE_PERIOD   311 // which gives us 45 KHz (45016.07717 Hz)

void playMelody(uint16_t length, int (*noteTable)(uint16_t))
{
	uint16_t note = 1; // 1 means mute
	bool toggle = false;
	const int startMelodyCounterLimit = length * 5625; // 45000*0.125 = 5625
	
	for ( uint32_t startMelodyCounter = 0; startMelodyCounter < startMelodyCounterLimit ; startMelodyCounter++ ) // 7 seconds startup melody
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
					*DAC0_CH0DATA = 256;
					*DAC0_CH1DATA = 256;
				}
				toggle = false;
			}
			else
			{
				*DAC0_CH0DATA = 0;
				*DAC0_CH1DATA = 0;
				toggle = true;
			}
		}
		// each note is activated for 0.125 seconds or 5625 samples
		uint16_t songNoteMaxCount = 5625;
		uint16_t songCounter = startMelodyCounter / songNoteMaxCount;

		if (startMelodyCounter % songNoteMaxCount == 0)
		{
			note = (*noteTable)(songCounter);
		}
	}

}
int notesStartup(uint16_t songCounter)
{
	switch(songCounter)
	{
	case 0: return NOTE_A4;
	case 1:	return NOTE_C5;
	case 2: return NOTE_E5;
	case 3: return NOTE_FS5;
	case 4: return NOTE_A5;
	case 5: return NOTE_C6;
	case 6: return NOTE_E6;
	case 7: return NOTE_FS6;
	case 8: return NOTE_A6;
	case 9: return NOTE_C7;
	case 10: return NOTE_E7;
	case 11: return NOTE_FS7;
	case 12: return 1;
	case 13: return NOTE_E5;
	case 14: return NOTE_C5;
	case 15: return NOTE_A3;
		
	default: return 1;
	}
	
}

int notesStarWars(uint16_t songCounter)
{
	switch(songCounter)
	{
		case 0: return NOTE_E4;
		case 1:	return NOTE_E4;
		case 2: return 1;
		case 3: return 1;
		case 4: return NOTE_E4;
		case 5: return NOTE_E4;
		case 6: return 1;
		case 7: return 1;
		case 8: return NOTE_E4;
		case 9: return NOTE_E4;
		case 10: return 1;
		case 11: return 1;
		case 12: return NOTE_F4;
		case 13: return NOTE_F4;
		case 14: return 1;
		case 15: return NOTE_C5;
		case 16: return NOTE_E4;
		case 17: return NOTE_E4;
		case 18: return 1;
		case 19: return 1;
		case 20: return NOTE_F4;
		case 21: return NOTE_F4;
		case 22: return 1;
		case 23: return NOTE_C5;
		case 24: return NOTE_E4;
		case 25: return NOTE_E4;
		
		case 26: return 1;
		case 27: return 1;			
		case 28: return 1;
		case 29: return 1;
		case 30: return 1;
		case 31: return 1;
		case 32: return NOTE_E5;
		case 33: return NOTE_E5;
		case 34: return 1;
		case 35: return 1;
		case 36: return NOTE_E5;
		case 37: return NOTE_E5;
		case 38: return 1;
		case 39: return 1;
		case 40: return NOTE_E5;
		case 41: return NOTE_E5;
		case 42: return 1;
		case 43: return 1;
		case 44: return NOTE_F5;
		case 45: return NOTE_F5;
		case 46: return 1;
		case 47: return NOTE_C5;
		case 48: return NOTE_GS4;
		case 49: return NOTE_GS4;
		case 50: return 1;
		case 51: return 1;
		case 52: return NOTE_F4;
		case 53: return NOTE_F4;
		case 54: return 1;
		case 55: return NOTE_C5;

		default: return 1;
	}
	/*
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
	}*/
}

int notesSound1(uint16_t songCounter)
{
	switch(songCounter)
	{
		case 0: return NOTE_D4;			
		case 1:	return NOTE_D4;
		case 2: return NOTE_D5;			//		
		case 3: return 1;
		case 4: return NOTE_A4;
		case 5: return 1;
		case 6: return 1;
		case 7: return NOTE_GS4;
		case 8: return 1;
		case 9: return NOTE_G4;
		case 10: return 1;
		case 11: return NOTE_F4;
		case 12: return 1;
		case 13: return NOTE_D4;
		case 14: return NOTE_F4;
		case 15: return NOTE_G4;
		case 16: return NOTE_C4;
		case 17: return NOTE_C4;
		case 18: return NOTE_D5;		//
		case 19: return 1;
		case 20: return NOTE_A4;
		case 21: return 1;
		case 22: return 1;
		case 23: return NOTE_GS4;
		case 24: return 1;
		case 25: return NOTE_G4;
		
		case 26: return 1;
		case 27: return NOTE_F4;
		case 28: return 1;
		case 29: return NOTE_D4;
		case 30: return NOTE_F4;
		case 31: return NOTE_G4;
		case 32: return NOTE_B3;
		case 33: return NOTE_B3;
		case 34: return NOTE_D5;		//
		case 35: return 1;
		case 36: return NOTE_A4;
		case 37: return 1;
		case 38: return 1;
		case 39: return NOTE_GS4;
		case 40: return 1;
		case 41: return NOTE_G4;
		case 42: return 1;
		case 43: return NOTE_F4;
		case 44: return 1;
		case 45: return NOTE_D4;
		case 46: return NOTE_F4;
		case 47: return NOTE_G4;
		case 48: return NOTE_AS3;
		case 49: return NOTE_AS3;
		case 50: return 1;
		case 51: return NOTE_D5;		//

		case 52: return 1;
		case 53: return NOTE_A4;
		case 54: return 1;
		case 55: return 1;
		case 56: return NOTE_GS4;
		case 57: return 1;
		case 58: return NOTE_G4;
		case 59: return 1;
		case 60: return NOTE_F4;
		case 61: return 1;
		case 62: return NOTE_D4;
		case 63: return NOTE_F4;
		case 64: return NOTE_G4;
		case 65: return NOTE_F4;
		case 66: return 1;
		case 67: return NOTE_F4;
		case 68: return NOTE_F4;
		
		
		
		case 69: return 1;
		case 70: return NOTE_F4;
		case 71: return 1;
		case 72: return NOTE_F4;
		case 73: return 1;
		case 74: return NOTE_D4;
		case 75: return 1;
		case 76: return NOTE_D4;
		case 77: return 1;
		case 78: return 1;
		case 79: return NOTE_D4;
		case 80: return 1;
		case 81: return NOTE_F4;
		case 82: return NOTE_F4;
		case 83: return NOTE_F4;
		case 84: return NOTE_F4;
		
		case 85: return 1;
		case 86: return NOTE_G4;
		case 87: return 1;
		case 88: return NOTE_GS4;
		case 89: return 1;
		case 90: return NOTE_G4;
		case 91: return NOTE_F4;
		case 92: return NOTE_D4;
		case 93: return NOTE_F4;
		case 94: return NOTE_G4;
		case 95: return 1;
		case 96: return 1;
		case 97: return NOTE_F4;
		case 98: return 1;
		case 99: return NOTE_F4;
		case 100: return NOTE_F4;
		case 101: return 1;
		case 102: return NOTE_G4;
		
		
		case 103: return 1;
		case 104: return NOTE_GS4;
		case 105: return 1;
		case 106: return NOTE_A4;
		case 107: return 1;
		case 108: return NOTE_C5;
		case 109: return 1;
		case 110: return NOTE_A4;
		case 111: return 1;
		case 112: return 1;
		case 113: return NOTE_D5;
		case 114: return 1;
		case 115: return NOTE_D5;
		case 116: return 1;
		case 117: return NOTE_D5;
		case 118: return NOTE_A4;
		case 119: return NOTE_D5;
		case 120: return NOTE_C5;
		case 121: return NOTE_C5;
		case 122: return 1;
		case 123: return 1;
		
		default: return 1;
	}
}

int notesSound2(uint16_t songCounter)
{
	switch(songCounter)
	{
		case 0: return NOTE_F5;			
		case 1:	return 1;
		case 2: return NOTE_C5;
		case 3: return 1;
		case 4: return NOTE_GS4;
		case 5: return 1;
		case 6: return NOTE_F4;
		case 7: return 1;
		case 8: return 1;
		case 9: return NOTE_B4;
		case 10: return NOTE_AS4;
		case 11: return 1;
		case 12: return NOTE_AS4;
		case 13: return NOTE_GS4;
		case 14: return NOTE_E4;
		case 15: return NOTE_F4;
		case 16: return 1;
		case 17: return NOTE_C5;
		case 18: return NOTE_AS4;
		case 19: return NOTE_GS4;
		case 20: return NOTE_AS4;
		case 21: return NOTE_C5;
		case 22: return NOTE_E4;
		case 23: return NOTE_F4;
		case 24: return NOTE_GS4;
		case 25: return NOTE_F4;

		case 26: return NOTE_E4;
		case 27: return NOTE_F5;			
		case 28: return 1;
		case 29: return NOTE_DS5;
		case 30: return NOTE_C5;
		case 31: return NOTE_GS4;
		
		case 32: return NOTE_F4;
		case 33: return NOTE_F4;
		
		case 34: return NOTE_CS4;
		case 35: return NOTE_CS4;
		
		case 36: return NOTE_G4;
		case 37: return NOTE_G4;
		
		case 38: return NOTE_CS4;
		case 39: return NOTE_CS4;
		
		case 40: return NOTE_GS4;
		case 41: return NOTE_GS4;
		
		case 42: return NOTE_CS4;
		case 43: return NOTE_CS4;
		
		case 44: return NOTE_AS4;
		case 45: return NOTE_AS4;
		
		case 46: return NOTE_CS4;
		case 47: return NOTE_CS4;
		
		case 48: return NOTE_C5;
		case 49: return NOTE_C5;
		
		case 50: return NOTE_AS4;
		case 51: return NOTE_AS4;
		
		case 52: return NOTE_F5;
		case 53: return NOTE_F5;
		
		case 54: return NOTE_C5;
		case 55: return NOTE_C5;
		
		case 56: return NOTE_E5;
		case 57: return NOTE_E5;
		
		case 58: return NOTE_CS5;
		case 59: return NOTE_CS5;
		
		case 60: return NOTE_C5;
		case 61: return NOTE_C5;
		
		case 62: return NOTE_C5;
		case 63: return NOTE_C5;
		
		case 64: return NOTE_C5;
		case 65: return 1;
		case 66: return NOTE_F5;
		case 67: return NOTE_C6;
		case 68: return NOTE_AS5;
		case 69: return NOTE_C6;
		case 70: return NOTE_F5;
		case 71: return NOTE_C6;
		case 72: return NOTE_AS5;
		case 73: return NOTE_C6;
		case 74: return NOTE_CS5;
		case 75: return NOTE_B5;
		case 76: return NOTE_AS5;
		case 77: return NOTE_B5;
		case 78: return NOTE_DS5;
		case 79: return NOTE_C6;
		
		case 80: return NOTE_G5;
		case 81: return NOTE_AS5;
		case 82: return NOTE_F5;
		case 83: return NOTE_C6;
		case 84: return NOTE_AS5;
		case 85: return NOTE_C6;
		case 86: return NOTE_G5;
		case 87: return NOTE_C6;
		case 88: return NOTE_AS5;
		case 89: return NOTE_C6;
		case 90: return NOTE_GS5;
		case 91: return NOTE_C6;
		case 92: return NOTE_AS5;
		case 93: return NOTE_C6;
		case 94: return NOTE_AS5;
		case 95: return NOTE_CS6;
		case 96: return NOTE_C6;
		case 97: return NOTE_CS6;
		case 98: return NOTE_CS5;
		case 99: return NOTE_GS5;
		case 100: return NOTE_G5;
		case 101: return NOTE_GS5;
		case 102: return NOTE_DS5;
		case 103: return NOTE_AS5;
		case 104: return NOTE_GS5;
		case 105: return NOTE_AS5;
		
		
		case 106: return NOTE_DS5;
		case 107: return NOTE_C6;
		case 108: return NOTE_AS5;
		case 109: return NOTE_C6;
		case 110: return NOTE_DS5;
		case 111: return NOTE_CS6;
		case 112: return NOTE_C6;
		case 113: return NOTE_CS6;
		case 114: return NOTE_C5;
		case 115: return NOTE_C5;
		case 116: return NOTE_AS4;
		case 117: return NOTE_AS4;
		case 118: return NOTE_F5;
		case 119: return NOTE_F5;
		case 120: return NOTE_C5;
		case 121: return NOTE_C5;
		case 122: return NOTE_E5;
		case 123: return NOTE_E5;
		case 124: return NOTE_CS5;
		case 125: return NOTE_CS5;
		case 126: return NOTE_C5;
		case 127: return NOTE_C5;
		case 128: return NOTE_C5;
		case 129: return NOTE_C5;
//		case 130: return NOTE_F5;
//		case 131: return 1;
		
		
		/*
		case : return NOTE_;
		case : return NOTE_;
		case : return NOTE_;
		case : return NOTE_;*/
		
		
		
		
		

		default: return 1;
	}
}

int notesSound3(uint16_t songCounter)
{
	switch(songCounter)
	{
		case 0: return NOTE_D4;			
		case 1:	return NOTE_D4;
		case 2: return 1;
		case 3: return 1;
		case 4: return NOTE_G4;
		case 5: return NOTE_G4;
		case 6: return 1;
		case 7: return 1;
		case 8: return 1;
		case 9: return 1;
		case 10: return NOTE_AS4;
		case 11: return NOTE_AS4;
		case 12: return NOTE_A4;
		case 13: return NOTE_A4;
		case 14: return 1;
		case 15: return 1;
		case 16: return NOTE_G4;
		case 17: return NOTE_G4;
		case 18: return 1;
		case 19: return 1;
		case 20: return 1;
		case 21: return 1;
		case 22: return 1;
		case 23: return 1;
		case 24: return NOTE_D5;
		case 25: return NOTE_D5;
		
		case 26: return 1;
		case 27: return 1;			
		case 28: return NOTE_C5;
		case 29: return NOTE_C5;
		case 30: return 1;
		case 31: return 1;
		case 32: return 1;
		case 33: return 1;
		case 34: return 1;
		case 35: return 1;
		case 36: return 1;
		case 37: return 1;
		case 38: return 1;
		case 39: return NOTE_A4;
		case 40: return NOTE_A4;
		/*
		case 41: return NOTE_F4;
		case 42: return NOTE_F4;
		case 43: return NOTE_F4;
		case 44: return NOTE_C5;
		case 45: return NOTE_A4;
		case 46: return NOTE_A4;
		case 47: return NOTE_A4;
		case 48: return NOTE_A4;
		case 49: return NOTE_A4;*/

		default: return 1;
	}
}
