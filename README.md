# UF2 bootloader for STM32F103

This project was initially forked off https://github.com/devanlai/dapboot though the DFU functionality has been removed
and replaced with a USB Mass Storage with [UF2 support](https://github.com/Microsoft/uf2)

Boards with this bootloader can be programmed at https://maker.makecode.com
using web interface using a graphical programming language or TypeScript (JavaScript with Types).

## Flashing bootloader from binaries

You will need a STLink/v2 (or other debugger) to flash it.

* https://github.com/mmoskal/uf2-stm32f103/releases
* download the latest ZIP file (`uf2-stm32f103-vX.Y.Z.zip`)
* run: `openocd -f interface/stlink-v2.cfg -f target/stm32f1x.cfg -c "program uf2boot-BLUEPILL.bin verify reset exit 0x8000000"`
* see if `BLUEPILL` drive appears; if not reset the board; the LED should be fading in and out about once per second

## Build instructions
The default target is a generic STM32F103 dev board with an LED on PC13, commonly referred to as a "bluepill" board.

To build other targets, you can override the
`TARGET` variable when invoking `make`.

    make clean
    make TARGET=STLINK

### Targets

| Target Name | Description | Link |
| ----------- | ----------- |----- |
|`BLUEPILL`   | Cheap dev board | http://wiki.stm32duino.com/index.php?title=Blue_Pill |
|`MAPLEMINI`  | LeafLabs Maple Mini board and clone derivatives | http://wiki.stm32duino.com/index.php?title=Maple_Mini |
|`STLINK`     | STLink/v2 hardware clones | https://wiki.paparazziuav.org/wiki/STLink#Clones |
| `PXT32`     | MakeCode Arcade console (currently disabled on Arcade site) | https://arcade.makecode.com |


## Flash instructions

The `make flash` target will use openocd to upload the bootloader to an attached board.
By default, the Makefile assumes you're using a STLink v2 based probe, but you can override this by overriding `OOCD_INTERFACE` variable. For example:

    make OOCD_INTERFACE=interface/cmsis-dap.cfg flash

## Overriding defaults
Local makefile settings can be set by creating a `local.mk`, which is automatically included.

Here is an example `local.mk` that changes the default target to the STLink/v2 and uses an unmodified STLink/v2 to flash it.

    TARGET ?= STLINK
    OOCD_INTERFACE ?= interface/stlink-v2.cfg

## Using the bootloader
### Building for the bootloader
The bootloader occupies the lower 16KiB of flash, so your application must offset its flash contents by 16KiB. This can be done by modifying your linker script or flags as appropriate.

### Switching to the bootloader
The bootloader can be built to look for arbitrary patterns, but the default for the STM32F103 target looks for a magic value stored in the RTC backup registers. Writing the magic value and then resetting will run the bootloader instead of the main application.

### WebUSB

The WebUSB isn't currently supported.

## Licensing
All contents of the dapboot project are licensed under terms that are compatible with the terms of the GNU Lesser General Public License version 3.

Non-libopencm3 related portions of the dapboot project are licensed under the less restrictive ISC license, except where otherwise specified in the headers of specific files.

The UF2 parts are licensed under MIT.

See the LICENSE file for full details.
