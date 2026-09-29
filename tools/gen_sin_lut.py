#!/usr/bin/env python3  
  
import argparse  
import math  
  
def parse_args():  
    parser = argparse.ArgumentParser(description="Generate a single C header with sine lookup table.")  
    parser.add_argument("--table-length", type=int, required=True, help="Size of the lookup table (TABLE_LENGTH).")  
    parser.add_argument("--output-path", type=str, required=True, help="Output file path")  
    return parser.parse_args()  
  
def generate_table_data(table_length):  
    sine = []  
  
    for i in range(table_length):  
        val_sin = math.sin(i / table_length * 2 * math.pi)
        sine.append(val_sin)  
  
    return sine
  
def write_header(filename, sine):  
    with open(filename, 'w') as f:  
        f.write("#ifndef SIN_LUT_H\n")  
        f.write("#define SIN_LUT_H\n\n")  
        f.write('#include "synth_lib/config.h"\n\n')
  
        f.write("static const float sinTable[SIN_LUT_LENGTH] = {\n")  
        for i, val in enumerate(sine):  
            comma = "," if i < len(sine) - 1 else ""  
            f.write(f"    {val:.6f}{comma}\n")  
        f.write("};\n\n")  
  
        f.write("#endif\n")  
  
def main():  
    args = parse_args()  
  
    if args.table_length < 1:  
        raise ValueError("Table length must be at least 1.")  
  
    sinewave = generate_table_data(args.table_length)  
  
    write_header(args.output_path, sinewave)
  
    print(f"Generated {args.output_path} for size {args.table_length}.")  
  
if __name__ == "__main__":  
    main()  
