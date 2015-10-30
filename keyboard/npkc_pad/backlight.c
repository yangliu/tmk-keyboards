#include <stdint.h>
#include "progmem.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "backlight.h"

#include "TLC5940.h"


/*
Key => LED definitions
*/
const channel_t LED_ZONE_NUMS[] PROGMEM = {LED_P1,LED_P2,LED_P3,LED_P4,LED_P5,LED_P6,LED_P7,LED_P8,LED_P9,LED_PDOT};
const channel_t LED_ZONE_TOPROW[] PROGMEM ={LED_NLCK,LED_PSLS,LED_PAST,LED_PMNS};
const channel_t LED_ZONE_FUNCS[] PROGMEM ={LED_NLCK,LED_PSLS,LED_PAST,LED_PMNS,LED_PPLS,LED_PENT};

const uint16_t BRIGHTNESS_LEVEL[] PROGMEM = {0, 400, 800, 1200, 1600, 2000, 2400, 2800, 3200, 3600, 4095};

uint8_t current_level = 0;
channel_t pos = 0;
uint8_t is_change_backlight = 0;





void TLC5940_RefreshGSData(void) {
	channel_t ledi;
	while(gsUpdateFlag); // wait until we can modify GSData
	if (current_level>0 && current_level <= 10) {
		// all lights on mode, we don't need to constant update the GS data
		if (!is_change_backlight) return;
		is_change_backlight = 0;
		TLC5940_SetAllGS(pgm_read_word(&BRIGHTNESS_LEVEL[current_level]));
		TLC5940_SetGSUpdateFlag();
		return;
	}
	if (current_level > 10 && current_level <= 27) {
		if (!is_change_backlight) return;
		is_change_backlight = 0;
		TLC5940_SetAllGS(0);
		ledi = (current_level == 11 ? LED_P0 :
			(current_level == 12 ? LED_P1 :
			(current_level == 13 ? LED_P2 :
			(current_level == 14 ? LED_P3 :
			(current_level == 15 ? LED_P4 :
			(current_level == 16 ? LED_P5 :
			(current_level == 17 ? LED_P6 :
			(current_level == 18 ? LED_P7 :
			(current_level == 19 ? LED_P8 :
			(current_level == 20 ? LED_P9 :
			(current_level == 21 ? LED_PDOT :
			(current_level == 22 ? LED_NLCK :
			(current_level == 23 ? LED_PSLS :
			(current_level == 24 ? LED_PAST :
			(current_level == 25 ? LED_PMNS :
			(current_level == 26 ? LED_PPLS :
			LED_PENT))))))))))))))));
		TLC5940_SetGS(ledi, 4095);
		TLC5940_SetGSUpdateFlag();
		return;

		// all light breath mode
	}
  // channel_t prev_i, next_i;
  // prev_i = pos-1<0?numChannels-1:pos-1;
  // next_i = pos+1>numChannels-1?0:pos+1;
	//
  // TLC5940_SetGS(prev_i, 2000);
  // TLC5940_SetGS(pos, 4095);
  // TLC5940_SetGS(next_i, 2000);


  // _delay_ms(50);
  // pos = (pos + 1) % numChannels;

}



void backlight_set(uint8_t level){
  current_level = level;
  dprintf("Backlight Set, level: %d", level);
  if (level>0) {
    TLC5940_Init();
    TLC5940_Enable();
  } else {
    TLC5940_Disable();
  }
  is_change_backlight = 1;
}
