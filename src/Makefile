## Copyright (c) 2016, Devan Lai
##
## Permission to use, copy, modify, and/or distribute this software
## for any purpose with or without fee is hereby granted, provided
## that the above copyright notice and this permission notice
## appear in all copies.
##
## THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
## WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
## WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
## AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
## CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
## LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
## NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
## CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

-include local.mk

BINARY = uf2boot
OPENCM3_DIR = ../libopencm3

UF2_VERSION_BASE = $(shell git describe --dirty --always --tags)
VER_FLAGS = -DUF2_VERSION='"$(UF2_VERSION_BASE)"'

TARGET ?= BLUEPILL
include targets.mk

SRCS := $(wildcard *.c)
SRCS += $(wildcard $(TARGET_COMMON_DIR)/*.c)
SRCS += $(wildcard $(TARGET_SPEC_DIR)/*.c)

BUILD = build/$(TARGET)

OBJS += $(addprefix $(BUILD)/,$(SRCS:.c=.o))
DEPS  = $(addprefix $(BUILD)/,$(SRCS:.c=.d))

ELF = $(BUILD)/$(BINARY).elf

all: $(BUILD) $(BUILD)/$(BINARY).bin size

$(BUILD):
	mkdir -p $(BUILD)/stm32f103

clean::
	rm -rf build/

include rules.mk

size: $(OBJS) $(ELF)
	@$(PREFIX)-size $(ELF)

BMP = $(shell ls -1 /dev/cu.usbmodem* | head -1)
BMP_ARGS = -ex "target extended-remote $(BMP)" -ex "mon swdp_scan" -ex "attach 1"
GDB = arm-none-eabi-gdb

flash: $(ELF)
	$(GDB) $(BMP_ARGS) -ex "load" -ex "quit" $(ELF)

gdb: $(ELF)
	$(GDB) $(BMP_ARGS) $(ELF)

ocd-gdb: $(ELF)
	-$(GDB) --eval "target remote | $(OOCD) -f $(OOCD_INTERFACE) -f $(OOCD_BOARD) -f debug.cfg" $(ELF)

erase:
	$(OOCD) -f $(OOCD_INTERFACE) -f $(OOCD_BOARD) \
            -c "init" -c "reset init" \
            -c "stm32f1x unlock 0; reset halt" \
            -c "flash erase_sector 0 0 last" -c "reset" -c "shutdown"

.PHONY += debug size erase

OBJS := $(sort $(OBJS))

# Add the base directory to the header search path
CPPFLAGS += -I.

# Add target config directory to the header search path
CPPFLAGS += -I$(TARGET_COMMON_DIR)/
CPPFLAGS += -I$(TARGET_SPEC_DIR)/

DROPNAME = uf2-stm32f103-$(UF2_VERSION_BASE)

do-drop: all
	mkdir -p build/$(DROPNAME)
	cp $(BUILD)/$(BINARY).bin build/$(DROPNAME)/$(BINARY)-$(TARGET).bin

drop:
	rm -rf build
	set -e; for t in BLUEPILL JACDAC ; do $(MAKE) TARGET=$$t do-drop ; done
	cd build; 7z a $(DROPNAME).zip $(DROPNAME)
