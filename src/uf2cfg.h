#define UF2_VERSION "1.00"
#define PRODUCT_NAME "NRF52 Board"
#define BOARD_ID "NRF52-generic-v0"
#define INDEX_URL "https://pxt.io"
#define UF2_NUM_BLOCKS 8000
#define VOLUME_LABEL "NRFBOOT"
#define FLASH_SIZE (1024*1024)
// where the UF2 files are allowed to write data - we allow MBR, since it seems part of the softdevice .hex file
#define USER_FLASH_START 0x0
#define USER_FLASH_END BOOTLOADER_START_ADDR

#define FLASH_PAGE_SIZE 4096
