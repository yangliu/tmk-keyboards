#include <stdint.h>
#include "progmem.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "backlight.h"
#include "timer.h"
#include "action_layer.h"

#include "TLC5940.h"


/*
Key => LED definitions
*/
const channel_t LED_ZONE_NUMS[] PROGMEM = {LED_P0,LED_P1,LED_P2,LED_P3,LED_P4,LED_P5,LED_P6,LED_P7,LED_P8,LED_P9,LED_PDOT};
const channel_t LED_ZONE_TOPROW[] PROGMEM ={LED_NLCK,LED_PSLS,LED_PAST,LED_PMNS};
const channel_t LED_ZONE_FUNCS[] PROGMEM ={LED_NLCK,LED_PSLS,LED_PAST,LED_PMNS,LED_PPLS,LED_PENT};

const uint16_t BRIGHTNESS_LEVEL[] PROGMEM = {0, 700, 1500, 2400, 3400, 4095};
const channel_t LED_SNAKE_SEQ[] PROGMEM = {LED_NLCK, LED_P7, LED_P4, LED_P1, LED_P0, LED_P2, LED_P5, LED_P8, LED_PSLS, LED_PAST, LED_P9, LED_P6, LED_P3, LED_PDOT, LED_PENT, LED_PPLS, LED_PMNS};
const uint8_t LED_SNAKE_INTERVAL = 100;
const uint16_t LED_BREATHING_TABLE[] PROGMEM = {0,0,0,0,16,16,16,32,32,48,64,80,80,96,112,144,160,176,192,224,240,272,288,320,336,368,400,432,464,496,528,560,592,640,672,704,752,784,832,864,912,944,992,1040,1072,1120,1168,1216,1264,1312,1360,1408,1440,1488,1552,1600,1648,1696,1744,1792,1840,1888,1936,1984,2032,2096,2144,2192,2240,2288,2336,2384,2432,2480,2528,2592,2640,2672,2720,2768,2816,2864,2912,2960,3008,3040,3088,3136,3168,3216,3248,3296,3328,3376,3408,3440,3488,3520,3552,3584,3616,3648,3680,3712,3744,3760,3792,3808,3840,3856,3888,3904,3920,3936,3968,3984,4000,4000,4016,4032,4048,4048,4064,4064,4064,4080,4080,4080,4080,4080,4080,4080,4064,4064,4064,4048,4048,4032,4016,4000,4000,3984,3968,3936,3920,3904,3888,3856,3840,3808,3792,3760,3744,3712,3680,3648,3616,3584,3552,3520,3488,3440,3408,3376,3328,3296,3248,3216,3168,3136,3088,3040,3008,2960,2912,2864,2816,2768,2720,2672,2640,2592,2528,2480,2432,2384,2336,2288,2240,2192,2144,2096,2048,1984,1936,1888,1840,1792,1744,1696,1648,1600,1552,1488,1440,1408,1360,1312,1264,1216,1168,1120,1072,1040,992,944,912,864,832,784,752,704,672,640,592,560,528,496,464,432,400,368,336,320,288,272,240,224,192,176,160,144,112,96,80,80,64,48,32,32,16,16,16,0,0,0};
const uint8_t LED_BREATHING_INTERVALS[] PROGMEM = {30, 20, 10, 5};

const uint32_t LED_LAYER_SEL_LASTING = 5000;

const uint8_t numLED = 17;

uint8_t current_level = 0;
channel_t pos = 0;
uint8_t is_change_backlight = 0;




void Eff_Snake(void) {
	static int8_t pos = 0;
	static uint16_t last_timer = 0;
	static int8_t direction = 1;

	if (timer_elapsed(last_timer)<LED_SNAKE_INTERVAL) return;

	last_timer = timer_read();

	int8_t p4, p3, p2, p1;
	TLC5940_SetAllGS(200);

	p1 = pos-1*direction;
	p2 = pos-2*direction;
	p3 = pos-3*direction;
	p4 = pos-4*direction;
	TLC5940_SetGS(pgm_read_byte(&LED_SNAKE_SEQ[pos]), 4095);
	if (p1>=0 && p1<=numLED-1) TLC5940_SetGS(pgm_read_byte(&LED_SNAKE_SEQ[p1]), 3400);
	if (p2>=0 && p2<=numLED-1) TLC5940_SetGS(pgm_read_byte(&LED_SNAKE_SEQ[p2]), 2400);
	if (p3>=0 && p3<=numLED-1) TLC5940_SetGS(pgm_read_byte(&LED_SNAKE_SEQ[p3]), 1500);
	if (p4>=0 && p4<=numLED-1) TLC5940_SetGS(pgm_read_byte(&LED_SNAKE_SEQ[p4]), 700);
	TLC5940_SetGSUpdateFlag();

	pos = pos+direction;
	if (pos == numLED-1 || pos == 0) {
			direction *= -1;
	}
}

void Eff_Breathing_Full(uint8_t interval) {
	static uint8_t pos = 0;
	static uint16_t last_timer = 0;


	if (timer_elapsed(last_timer)<pgm_read_byte(&LED_BREATHING_INTERVALS[interval])) return;
	last_timer = timer_read();

	TLC5940_SetAllGS(pgm_read_word(&LED_BREATHING_TABLE[pos]));
	TLC5940_SetGSUpdateFlag();
	pos = (pos+1) % 256;
}

// uint8_t Eff_LayerSel(void) {
// 	// static uint8_t eff_layer_done = 1;
// 	static uint32_t prev_layer_state=0;
// 	static uint32_t on_timer=0;
// 	static uint16_t breathing_timer=0;
// 	static uint8_t breathing_pos=0;
//
// 	static uint8_t breathing_led_num = 0;
// 	static uint8_t breathing_leds[17];
//
// 	if (prev_layer_state == layer_state
// 			&& timer_elapsed32(on_timer) > LED_LAYER_SEL_LASTING) {
// 		// no layer change and current layer indication has done.
// 		return 0;
// 	}
//
// 	uint32_t layers = layer_state | default_layer_state;
// 	if (prev_layer_state != layer_state) {
// 		print("layer_state changed: layer_state="); print_bin32(layer_state); print("\n");
// 		prev_layer_state = layer_state;
// 		on_timer = timer_read32();
// 		breathing_pos = 0;
// 		breathing_led_num = 0;
//
// 		if (layers & (1UL<<0)) {
// 			// Layer 0, flashing the NLCK key and number area
// 			breathing_led_num = 12;
// 			breathing_leds[0] = LED_NLCK;
// 			for (int8_t j = 0; j < 11; j++) {
// 				breathing_leds[j+1] = pgm_read_byte(&LED_ZONE_NUMS[j]);
// 			}
// 		} else if (layers & (1UL<<1)) {
// 			// Layer 1
// 			breathing_led_num=3;
// 			breathing_leds[0] = LED_PSLS;
// 			breathing_leds[1] = LED_PAST;
// 			breathing_leds[2] = LED_PMNS;
// 		} else {
// 			breathing_led_num = 0;
// 		}
// 	}
// 	print("breathing_led_num = "); print_dec(breathing_led_num); print("\n");
// return 1;
// 	if (breathing_led_num > 0) {
// 		if (timer_elapsed(breathing_timer)>=2) {
// 			for (int8_t k = 0; k < breathing_led_num; k++) {
// 				TLC5940_SetGS(breathing_leds[k], pgm_read_byte(&LED_BREATHING_TABLE[breathing_pos]));
// 			}
// 			TLC5940_SetGSUpdateFlag();
// 			breathing_timer = timer_read();
// 		}
// 	}
// 	return 1;
// }



void TLC5940_RefreshGSData(void) {
	// channel_t ledi;
	while(gsUpdateFlag); // wait until we can modify GSData
	// if (Eff_LayerSel()) return;
	if (current_level>0 && current_level <= 5) {
		// all lights on mode, we don't need to constant update the GS data
		if (!is_change_backlight) return;
		is_change_backlight = 0;
		TLC5940_SetAllGS(pgm_read_word(&BRIGHTNESS_LEVEL[current_level]));
		TLC5940_SetGSUpdateFlag();
		return;
	} else if (current_level == 6) {
		// snake
		Eff_Snake();
		return;
	} else if (current_level > 6 && current_level <= 10) {
		// full keyboard breathing
		Eff_Breathing_Full(current_level-7);
		return;
	}

	// if (current_level > 10 && current_level <= 27) {
	// 	if (!is_change_backlight) return;
	// 	is_change_backlight = 0;
	// 	TLC5940_SetAllGS(0);
	// 	ledi = (current_level == 11 ? LED_P0 :
	// 		(current_level == 12 ? LED_P1 :
	// 		(current_level == 13 ? LED_P2 :
	// 		(current_level == 14 ? LED_P3 :
	// 		(current_level == 15 ? LED_P4 :
	// 		(current_level == 16 ? LED_P5 :
	// 		(current_level == 17 ? LED_P6 :
	// 		(current_level == 18 ? LED_P7 :
	// 		(current_level == 19 ? LED_P8 :
	// 		(current_level == 20 ? LED_P9 :
	// 		(current_level == 21 ? LED_PDOT :
	// 		(current_level == 22 ? LED_NLCK :
	// 		(current_level == 23 ? LED_PSLS :
	// 		(current_level == 24 ? LED_PAST :
	// 		(current_level == 25 ? LED_PMNS :
	// 		(current_level == 26 ? LED_PPLS :
	// 		LED_PENT))))))))))))))));
	// 	TLC5940_SetGS(ledi, 4095);
	// 	TLC5940_SetGSUpdateFlag();
	// 	return;
	//
	// 	// all light breath mode
	// }
}



void backlight_set(uint8_t level){
  current_level = level;
  print("Backlight Set, level: "); print_dec(level); print("\n");
  if (level>0) {
    TLC5940_Init();
    TLC5940_Enable();
  } else {
    TLC5940_Disable();
  }
  is_change_backlight = 1;
}
