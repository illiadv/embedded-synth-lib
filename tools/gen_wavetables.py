#!/usr/bin/env python3  
  
import argparse  
import math  
  
def parse_args():  
    parser = argparse.ArgumentParser(description="Generate a single C header with lookup tables.")  
    parser.add_argument("--table-length", type=int, required=True, help="Size of the lookup table (TABLE_LENGTH).")  
    parser.add_argument("--max-sample-value", type=int, required=True, help="Maximum sample value (MAX_SAMPLE_VALUE).")  
    parser.add_argument("--output-path", type=str, required=True, help="Output file path")  
    return parser.parse_args()  
  
def generate_table_data(table_length, max_sample_value):  
    sinewave = []  
    sawtooth = []  
    triangle = []  
  
    for i in range(table_length):  
        # Sinewave
        val_sin = int(round(math.sin(i * 2 * math.pi / table_length) * max_sample_value))
        sinewave.append(val_sin)  
  
        # Sawtooth  
        val_saw = int(round(((float(i) / table_length) * 2 - 1.0) * max_sample_value))
        sawtooth.append(val_saw)  
  
        # Triangle  
        v = float(i) if i < table_length / 2 else table_length - float(i)
        v = v * 2.0  
        v = v / table_length * 2.0 - 1.0  
        val_tri = int(round(v * max_sample_value))
        triangle.append(val_tri)  
  
    return sinewave, sawtooth, triangle  
  
def write_header(filename, sinewave, sawtooth, triangle):  
    with open(filename, 'w') as f:  
        f.write("#ifndef WAVETABLES_H\n")  
        f.write("#define WAVETABLES_H\n\n")  
        f.write('#include "synth_lib/config.h"\n\n')
  
        # Sinewave  
        f.write("static const sound_sample_t sinewaveTable[TABLE_LENGTH] = {\n")  
        for i, val in enumerate(sinewave):  
            comma = "," if i < len(sinewave) - 1 else ""  
            f.write(f"    {val}{comma}\n")  
        f.write("};\n\n")  
  
        # Sawtooth  
        f.write("static const sound_sample_t sawtoothTable[TABLE_LENGTH] = {\n")  
        for i, val in enumerate(sawtooth):  
            comma = "," if i < len(sawtooth) - 1 else ""  
            f.write(f"    {val}{comma}\n")  
        f.write("};\n\n")  
  
        # Triangle  
        f.write("static const sound_sample_t triangleTable[TABLE_LENGTH] = {\n")  
        for i, val in enumerate(triangle):  
            comma = "," if i < len(triangle) - 1 else ""  
            f.write(f"    {val}{comma}\n")  
        f.write("};\n\n")  
  
        f.write("#endif\n")  
  
def main():  
    args = parse_args()  
  
    if args.table_length < 1:  
        raise ValueError("Table length must be at least 1.")  
  
    sinewave, sawtooth, triangle = generate_table_data(args.table_length, args.max_sample_value)  
  
    write_header(args.output_path, sinewave, sawtooth, triangle)  
  
    print(f"Generated {args.output_path} for size {args.table_length}.")  
  
if __name__ == "__main__":  
    main()  
