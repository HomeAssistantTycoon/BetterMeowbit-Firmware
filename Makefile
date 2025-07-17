# Compiler settings
CC = arm-none-eabi-gcc
CFLAGS = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall -O2 -ffreestanding -nostdlib -I.

# Linker script
LDSCRIPT = linker.ld

# Source files
SRCS = src/main.c src/startup.c

# Build directory
BUILD = build

# Output files
ELF = $(BUILD)/bettermeowbit.elf
BIN = $(BUILD)/bettermeowbit.bin

# Object files
OBJS = $(SRCS:src/%.c=$(BUILD)/%.o)

.PHONY: all clean

all: $(BIN)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/%.o: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF): $(OBJS)
	$(CC) $(CFLAGS) -nostdlib -T $(LDSCRIPT) -Wl,-Map=$(BUILD)/bettermeowbit.map -o $@ $^

$(BIN): $(ELF)
	arm-none-eabi-objcopy -O binary $< $@

clean:
	rm -rf $(BUILD)

