#include <avr/interrupt.h>
#include "TLC5940.h"

uint8_t is_init = 0;

uint8_t gsData[gsDataSize];
volatile uint8_t gsUpdateFlag;

uint8_t firstCycleFlag;


void TLC5940_SetAllGS(uint16_t value) {
	uint8_t tmp1 = (value >> 4);
	uint8_t tmp2 = (uint8_t)(value << 4) | (tmp1 >> 4);
	gsData_t i = 0;
	do {
		gsData[i++] = tmp1;              // bits: 11 10 09 08 07 06 05 04
		gsData[i++] = tmp2;              // bits: 03 02 01 00 11 10 09 08
		gsData[i++] = (uint8_t)value;    // bits: 07 06 05 04 03 02 01 00
	} while (i < gsDataSize);
}

void TLC5940_SetGS(channel_t channel, uint16_t value) {
	channel = numChannels - 1 - channel;
	uint16_t i = (uint16_t)channel * 3 / 2;

	switch (channel % 2) {
		case 0:
			gsData[i] = (value >> 4);
			i++;
			gsData[i] = (gsData[i] & 0x0F) | (uint8_t)(value << 4);
			break;
		default: // case 1:
			gsData[i] = (gsData[i] & 0xF0) | (value >> 8);
			i++;
			gsData[i] = (uint8_t)value;
			break;
	}
}

void TLC5940_Init(void) {
  if (is_init) {
    return;
  } else {
    is_init = 1;
  }
	setOutput(GSCLK_DDR, GSCLK_PIN);
	setOutput(SCLK_DDR, SCLK_PIN);
	setOutput(XLAT_DDR, XLAT_PIN);
	setOutput(BLANK_DDR, BLANK_PIN);
	setOutput(SIN_DDR, SIN_PIN);

	setLow(GSCLK_PORT, GSCLK_PIN);
	setLow(SCLK_PORT, SCLK_PIN);
	setLow(XLAT_PORT, XLAT_PIN);
	setHigh(BLANK_PORT, BLANK_PIN);
  firstCycleFlag = 1;

  // Enable SPI, Master, set clock rate fck/2
	SPCR = (1 << SPE) | (1 << MSTR);
	SPSR = (1 << SPI2X);

  // Timer3 for pulsing GSCLK to drive the chip
  TCCR3A = (1 << COM3A1)      // set on BOTTOM, clear on OCR3A (non-inverting), and output on OC3A
           | (1 << WGM31);    // Fast pwm with ICR3 top
  OCR3A = 0;                // duty factor (as short a pulse as possible)
  ICR3 = 1;
  TCCR3B = (1<<CS30) //| (1<<CS32)        // no prescale, (start pwm output)
         | (1<<WGM32)       // Fast pwm with ICR3 top
         | (1<<WGM33);      // Fast pwm with ICR3 top
  // Timer1 for pulsing XLAT & BLANK
 	TCCR1A = (1 << WGM11); // CTC with OCR1A as TOP
  TCCR1B = (1 << CS11); // fck/8 slower than gsclk
 	OCR1A = 1; // generate one interrupt every 8 cycles
  // TIMSK1 |= (1 << OCIE1A); // enable Timer1

}

ISR(TIMER1_COMPA_vect) {
  static uint8_t xlat_needPulse=0;
  setHigh(BLANK_PORT, BLANK_PIN);

  if (xlat_needPulse) {
    pulse(XLAT_PORT, XLAT_PIN);
    xlat_needPulse = 0;
  }

  if (firstCycleFlag) {
    pulse(SCLK_PORT, SCLK_PIN);
    firstCycleFlag = 0;
  }

  setLow(BLANK_PORT, BLANK_PIN);
  TLC5940_RefreshGSData();
  if (gsUpdateFlag) {
		for (gsData_t i = 0; i < gsDataSize; i++) {
			SPDR = gsData[i];
			while (!(SPSR & (1 << SPIF)));
		}
		xlat_needPulse = 1;
		gsUpdateFlag = 0;
	}

}

void TLC5940_Enable(void) {
  TIMSK1 |= (1 << OCIE1A);
}

void TLC5940_Disable(void) {
  TIMSK1 &= ~(1<<OCIE1A);
}
