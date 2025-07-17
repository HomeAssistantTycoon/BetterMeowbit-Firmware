TARGET = bettermeowbit
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall -O2 -ffreestanding -nostdlib -I.

SRC = src/main.c src/startup.c
OBJ = $(SRC:.c=.o)

all: $(TARGET).uf2

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJ) linker.ld
	$(CC) $(CFLAGS) -T linker.ld -Wl,-Map,$(TARGET).map -o $@ $(OBJ)

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(TARGET).uf2: $(TARGET).bin
	python3 tools/uf2conv.py -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET).elf $(TARGET).bin $(TARGET).map $(TARGET).uf2
