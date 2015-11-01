#----------------------------------------------------------------------------
# On command line:
#
# make all = Make software.
#
# make clean = Clean out built project files.
#
# make coff = Convert ELF to AVR COFF.
#
# make extcoff = Convert ELF to AVR Extended COFF.
#
# make program = Download the hex file to the device.
#                Please customize your programmer settings(PROGRAM_CMD)
#
# make teensy = Download the hex file to the device, using teensy_loader_cli.
#               (must have teensy_loader_cli installed).
#
# make dfu = Download the hex file to the device, using dfu-programmer (must
#            have dfu-programmer installed).
#
# make flip = Download the hex file to the device, using Atmel FLIP (must
#             have Atmel FLIP installed).
#
# make dfu-ee = Download the eeprom file to the device, using dfu-programmer
#               (must have dfu-programmer installed).
#
# make flip-ee = Download the eeprom file to the device, using Atmel FLIP
#                (must have Atmel FLIP installed).
#
# make debug = Start either simulavr or avarice as specified for debugging,
#              with avr-gdb or avr-insight as the front end for debugging.
#
# make filename.s = Just compile filename.c into the assembler code only.
#
# make filename.i = Create a preprocessed source file for use in submitting
#                   bug reports to the GCC project.
#
# To rebuild project do "make clean" then "make all".
#----------------------------------------------------------------------------

# Target file name (without extension).
TARGET = npkcpad_lufa

# Directory common source filess exist
TMK_DIR = ../../tmk_core

# Directory keyboard dependent files exist
TARGET_DIR = .

# project specific files
SRC =	keymap_common.c \
	matrix.c \
	led.c \
	backlight.c \
	TLC5940.c

ifdef KEYMAP
    SRC := keymap_$(KEYMAP).c $(SRC)
else
    SRC := keymap_numpad.c $(SRC)
endif

CONFIG_H = config.h

ifndef DEV
	DEV=/dev/tty.usbmodem1D1151
endif

# MCU name
#MCU = at90usb1287
MCU = atmega32u4

# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the
#     processor frequency in Hz. You can then use this symbol in your source code to
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#
#     This will be an integer division of F_USB below, as it is sourced by
#     F_USB after it has run through any CPU prescalers. Note that this value
#     does not *change* the processor frequency - it should merely be updated to
#     reflect the processor speed set externally so that the code can use accurate
#     software delays.
F_CPU = 16000000


#
# LUFA specific
#
# Target architecture (see library "Board Types" documentation).
ARCH = AVR8

# Input clock frequency.
#     This will define a symbol, F_USB, in all source code files equal to the
#     input clock frequency (before any prescaling is performed) in Hz. This value may
#     differ from F_CPU if prescaling is used on the latter, and is required as the
#     raw input clock is fed directly to the PLL sections of the AVR for high speed
#     clock generation for the USB and other AVR subsections. Do NOT tack on a 'UL'
#     at the end, this will be done automatically to create a 32-bit value in your
#     source code.
#
#     If no clock division is performed on the input clock inside the AVR (via the
#     CPU clock adjust registers or the clock division fuses), this will be equal to F_CPU.
F_USB = $(F_CPU)

# Interrupt driven control endpoint task(+60)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT


# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=4096

# ---------- Begin TLC5940 Configuration Section ----------
# Define the number of TLC5940 chips that are linked in series
TLC5940_N = 1

SIN_DDR = DDRB
SIN_PORT = PORTB
SIN_PIN = PB2

SCLK_DDR = DDRB
SCLK_PORT = PORTB
SCLK_PIN = PB1

BLANK_DDR = DDRB
BLANK_PORT = PORTB
BLANK_PIN = PB6

XLAT_DDR = DDRB
XLAT_PORT = PORTB
XLAT_PIN = PB5

# This line integrates all options into a single flag called:
#     $(TLC5940_DEFINES)
# which should be appended to the definition of COMPILE below
TLC5940_DEFINES = -DTLC5940_N=$(TLC5940_N) \
                  -DTLC5940_MANUAL_DC_FUNCS=$(TLC5940_MANUAL_DC_FUNCS) \
									-DSIN_DDR=$(SIN_DDR) \
                  -DSIN_PORT=$(SIN_PORT) \
                  -DSIN_PIN=$(SIN_PIN) \
									-DSCLK_DDR=$(SCLK_DDR) \
                  -DSCLK_PORT=$(SCLK_PORT) \
                  -DSCLK_PIN=$(SCLK_PIN) \
									-DBLANK_DDR=$(BLANK_DDR) \
                  -DBLANK_PORT=$(BLANK_PORT) \
                  -DBLANK_PIN=$(BLANK_PIN) \
                  -DXLAT_DDR=$(XLAT_DDR) \
                  -DXLAT_PORT=$(XLAT_PORT) \
                  -DXLAT_PIN=$(XLAT_PIN)

OPT_DEFS += $(TLC5940_DEFINES)
# ---------- End TLC5940 Configuration Section ----------

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes	# Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = yes	# Mouse keys(+4700)
EXTRAKEY_ENABLE = yes	# Audio control and System control(+450)
CONSOLE_ENABLE = yes	# Console for debug(+400)
COMMAND_ENABLE = yes    # Commands for debug and configuration
NKRO_ENABLE = yes	# USB Nkey Rollover - not yet supported in LUFA
BACKLIGHT_ENABLE = yes # Enable backlight

# Optimize size but this may cause error "relocation truncated to fit"
#EXTRALDFLAGS = -Wl,--relax

# Search Path
VPATH += $(TARGET_DIR)
VPATH += $(TMK_DIR)

PROGRAM_CMD = avrdude -p$(MCU) -cavr109 -b57600 -Uflash:w:$(TARGET).hex -P$(DEV)


include $(TMK_DIR)/protocol/lufa.mk
include $(TMK_DIR)/common.mk
include $(TMK_DIR)/rules.mk
