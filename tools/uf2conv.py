#!/usr/bin/env python3
# UF2 Converter for STM32 (minimal)

import struct
import sys
import os

UF2_MAGIC_START0 = 0x0A324655  # "UF2\n"
UF2_MAGIC_START1 = 0x9E5D5157
UF2_MAGIC_END = 0x0AB16F30

def convert_to_uf2(bin_file, uf2_file):
    with open(bin_file, "rb") as f:
        data = f.read()

    block_size = 256
    num_blocks = (len(data) + block_size - 1) // block_size
    with open(uf2_file, "wb") as out:
        for block_no in range(num_blocks):
            ptr = block_no * block_size
            chunk = data[ptr:ptr + block_size]
            if len(chunk) < block_size:
                chunk += bytes([0x00] * (block_size - len(chunk)))

            target_addr = 0x08000000 + ptr  # Flash origin
            header = struct.pack("<IIIIIIII",
                                 UF2_MAGIC_START0,
                                 UF2_MAGIC_START1,
                                 0, 0x2000,  # flags, target size
                                 target_addr,
                                 block_size,
                                 block_no,
                                 num_blocks)
            header += struct.pack("<I", 0)  # file container ID
            header += chunk
            header += struct.pack("<I", UF2_MAGIC_END)
            out.write(header)

if __name__ == "__main__":
    if "-c" in sys.argv:
        idx = sys.argv.index("-c")
        bin_file = sys.argv[idx + 1]
        if "-o" in sys.argv:
            idx = sys.argv.index("-o")
            uf2_file = sys.argv[idx + 1]
            convert_to_uf2(bin_file, uf2_file)
        else:
            print("Missing -o option")
    else:
        print("Usage: uf2conv.py -c firmware.bin -o firmware.uf2")
