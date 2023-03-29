# A Simple Processor

This is verilog code of a simple processor that supports four ALU operations i.e. ADD, SUB, MULT and NAND. And supports two memory instructions load (LW) and Store (SW). Below is instruction format and hardware design on the processor.

![Processor Design](https://github.com/yasir-javed/simple_processor/blob/main/image.jpg?raw=true)


Program memory is initialized with program.hex file and data memory is intialized with data_file.txt. Currently these files implement a simple operation of


A = B + C*D


where A, B, C and D are stored in data memory locations 0 to 3. B, C and D have values 200, 10 and 2 respectively. Hence at the last SW instruction 220 is written at memory address 0.

# Assembler
assembler.cpp is C++ code that can be used as assmebler. It can take mulitple command line arguments as input but most common use case is

.\assembler.exe \<asm file> \<hex file>

e.g. to create program.hex from program.asm, write

.\assembler.exe program.asm program.hex

# Design video
Design is explained in following video


[![A simple processor from scratch](https://img.youtube.com/vi/HCzIK322Pzw/0.jpg)](https://www.youtube.com/watch?v=HCzIK322Pzw)
