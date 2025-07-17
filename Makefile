CC=arm-none-eabi-gcc
CFLAGS=-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall -O2 -ffreestanding -nostdlib -I.
LDFLAGS=-T linker.ld -nostdlib -Wl,-Map=build/bettermeowbit.map

SRC=src/main.c src/startup.c src/ili9341.c
OBJ=$(SRC:.c=.o)

all: build/bettermeowbit.uf2

build/bettermeowbit.elf: $(OBJ) linker.ld
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o build/bettermeowbit.elf

build/bettermeowbit.bin: build/bettermeowbit.elf
	arm-none-eabi-objcopy -O binary build/bettermeowbit.elf build/bettermeowbit.bin

build/bettermeowbit.uf2: build/bettermeowbit.bin
	python3 tools/uf2conv.py build/bettermeowbit.bin -c -o build/bettermeowbit.uf2

clean:
	rm -rf build/*.o build/*.elf build/*.bin build/*.uf2
