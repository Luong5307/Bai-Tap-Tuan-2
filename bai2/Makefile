# Tên file đầu ra
TARGET = firmware

# Bối cảnh công cụ biên dịch
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# Cờ biên dịch và Linker
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g -Wall
LDFLAGS = -T STM32F103C8Tx_FLASH.ld --specs=nosys.specs -nostartfiles

# Danh sách các file nguồn (.c và .s)
SRCS = main.c startup_stm32f103xb.s
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)

# Target mặc định khi gõ 'make'
all: $(TARGET).bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Target nạp code bằng ST-Link V2
flash: $(TARGET).bin
	st-flash write $(TARGET).bin 0x08000000

# Target dọn dẹp các file rác
clean:
	rm -f *.o *.elf *.bin

.PHONY: all flash clean
