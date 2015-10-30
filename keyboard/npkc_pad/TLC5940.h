#ifndef TLC5940_H
#define TLC5940_H

/*
Setup pins
*/
#ifndef SIN_DDR
#define SIN_DDR DDRB
#endif
#ifndef SIN_PORT
#define SIN_PORT PORTB
#endif
#ifndef SIN_PIN
#define SIN_PIN PB2
#endif

#ifndef SCLK_DDR
#define SCLK_DDR DDRB
#endif
#ifndef SCLK_PORT
#define SCLK_PORT PORTB
#endif
#ifndef SCLK_PIN
#define SCLK_PIN PB1
#endif

#ifndef BLANK_DDR
#define BLANK_DDR DDRB
#endif
#ifndef BLANK_PORT
#define BLANK_PORT PORTB
#endif
#ifndef BLANK_PIN
#define BLANK_PIN PB6
#endif

#ifndef XLAT_DDR
#define XLAT_DDR DDRB
#endif
#ifndef XLAT_PORT
#define XLAT_PORT PORTB
#endif
#ifndef XLAT_PIN
#define XLAT_PIN PB5
#endif

#ifndef TLC5940_N
#define TLC5940_N 1
#endif

// GSCLK PIN has to be PC6 for Pro Micro

#define GSCLK_DDR DDRC
#define GSCLK_PORT PORTC
#define GSCLK_PIN PC6

//------------------------

#define LED_P0 3
#define LED_P1 3
#define LED_P2 7
#define LED_P3 11
#define LED_P4 2
#define LED_P5 6
#define LED_P6 10
#define LED_P7 1
#define LED_P8 5
#define LED_P9 9
#define LED_PDOT 12

#define LED_NLCK 0
#define LED_PSLS 4
#define LED_PAST 8
#define LED_PENT 15
#define LED_PPLS 14
#define LED_PMNS 13

//--------------------------

#define setOutput(ddr, pin) ((ddr) |= (1 << (pin)))
#define setLow(port, pin) ((port) &= ~(1 << (pin)))
#define setHigh(port, pin) ((port) |= (1 << (pin)))
#define pulse(port, pin) do { \
                         	setHigh((port), (pin)); \
                         	setLow((port), (pin)); \
                         } while (0)
#define outputState(port, pin) ((port) & (1 << (pin)))

#if (24 * TLC5940_N > 255)
#define gsData_t uint16_t
#else
#define gsData_t uint8_t
#endif

#if (16 * TLC5940_N > 255)
#define channel_t uint16_t
#else
#define channel_t uint8_t
#endif

#define gsDataSize ((gsData_t)24 * TLC5940_N)
#define numChannels ((channel_t)16 * TLC5940_N)

//-----------------------------
extern uint8_t gsData[gsDataSize];
extern volatile uint8_t gsUpdateFlag;
static inline void TLC5940_SetGSUpdateFlag(void) {
	__asm__ volatile ("" ::: "memory");
	gsUpdateFlag = 1;
}

void TLC5940_SetAllGS(uint16_t value);
void TLC5940_SetGS(channel_t channel, uint16_t value);
void TLC5940_Init(void);
void TLC5940_Enable(void);
void TLC5940_Disable(void);
void TLC5940_RefreshGSData(void);

#endif
