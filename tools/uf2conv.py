#!/usr/bin/env python3
# uf2conv.py - converts .bin to .uf2 format for Meowbit and other UF2 devices

import sys
import os
import struct

# UF2 constants
UF2_MAGIC_START0 = 0x0A324655
UF2_MAGIC_START1 = 0x9E5D5157
UF2_MAGIC_END    = 0x0AB16F30

# Family ID for STM32F4 (Meowbit uses STM32F401)
UF2_FAMILY_ID = 0x68ed2b88

def create_uf2_block(data, addr, flags, block_no, total_blocks):
    block = bytearray(512)
    # Header
    struct.pack_into("<IIIIIIII", block, 0,
        UF2_MAGIC_START0, UF2_MAGIC_START1,
        flags,
        addr,
        len(data),
        block_no,
        total_blocks,
        UF2_FAMILY_ID)
    # Data
    block[32:32+len(data)] = data
    # Footer
    struct.pack_into("<I", block, 512 - 4, UF2_MAGIC_END)
    return block

def bin_to_uf2(bin_path, uf2_path):
    with open(bin_path, "rb") as f:
        data = f.read()

    block_size = 256
    total_blocks = (len(data) + block_size - 1) // block_size

    with open(uf2_path, "wb") as uf2:
        for block_no in range(total_blocks):
            start = block_no * block_size
            end = min(start + block_size, len(data))
            chunk = data[start:end]
            addr = 0x08000000 + start  # Flash start address for STM32F4
            flags = 0x0  # No special flags
            block = create_uf2_block(chunk, addr, flags, block_no, total_blocks)
            uf2.write(block)

def main():
    if len(sys.argv) != 5 or sys.argv[1] != '-c' or sys.argv[3] != '-o':
        print(f"Usage: {sys.argv[0]} -c <input.bin> -o <output.uf2>")
        return

    bin_path = sys.argv[2]
    uf2_path = sys.argv[4]

    if not os.path.isfile(bin_path):
        print(f"Error: File {bin_path} does not exist.")
        return

    bin_to_uf2(bin_path, uf2_path)
    print(f"Converted {bin_path} to {uf2_path}")

if __name__ == "__main__":
    main()
