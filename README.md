# c-computer-processor

# How to run the Project

- Download cmake:

  1. `sudo apt update`
  1. `sudo apt install cmake`

- Running:

  1. `cd C-Computer-Processor`
  1. `cmake -B build`
     1. -B has to be capital this is the build command
     1. build: this is the directory (output) of the build command
  1. `cd build`
  1. `make`
  1. `./processor`

# Double Big Harvard combo large arithmetic shifts

## Program Flow

- You must write your program in assembly language in a text file.
- Your must read the instructions from the text file, and parse them according to their types/formats (opcode and other relevant fields).
- You must store the parsed version of the instructions in the instruction memory.
- You should start the execution of your pipelined implementation by fetching the first instruction from the instruction memory at Clock Cycle 1.
- You should continue the execution based on the example provided in the Datapath section of each package reflecting the different stages working in parallel.

## Printings

The following items must be printed in the console after each Clock Cycle:

1. The Clock Cycle number.

2. The Pipeline stages:

   - Which instruction is being executed at each stage?
   - What are the input parameters/values for each stage?

3. The updates occurring to the registers in case a register value was changed.

4. The updates occurring in the data memory in case a value was stored or updated in the memory.
5. The content of all registers after the last clock cycle.
6. The full content of the instruction and data memories after the last clock cycle.

## Data Path

a. Stages: 3

All instructions regardless of their type must pass through all 3 stages.

1. Instruction Fetch (IF):
   - Fetches the next instruction from the main memory using the address in the PC (Program Counter), and increments the PC.
2. Instruction Decode (ID):
   - Decodes the instruction and reads any operands required from the register file.
3. Execute (EX):

   - all ALU operations are done in this stage.
   - it performs any memory access required by the current instruction:
     - loads: it would load an operand from the main memory,
     - stores: it would store an operand into the main memory.
     - instructions that have a result (a destination register): it writes this result back to the register file.

b. Pipeline: 3 instructions (maximum) running in parallel

1.  Number of clock cycles:

    - 3 + ((n - 1) \* 1), where n = number of instructions

- Example a program with 7 instructions:
  - 3 + (6 \* 1) = 9 clock cycles

You are required to understand the pattern in the example and implement it.

## Instruction Memory

- Memory Size: 1024 rows
- Row : 16 bits
- Addresses: 0 to 1023
  - word addressable
- Types: 2

### Instruction Set Architecture

- Instruction Count: 12

- The opcodes are from 0 to 11 according to the instructions order in the following table:

  | Name                   | OpCode | Format         | Operation                       |
  | ---------------------- | ------ | -------------- | ------------------------------- |
  | Add                    | 0      | ADD R1 R2      | R1 = R1 + R2                    |
  | Subtract               | 1      | SUB R1 R2      | R1 = R1 - R2                    |
  | Multiply               | 2      | MUL R1 R2      | R1 = R1 \* R2                   |
  | Move Immediate         | 3      | MOVI R1 IMM    | R1 = IMM                        |
  | Branch if Equal Zero   | 4      | BEQZ R1 IMM    | if(R1 == 0){PC = PC + 1 + IMM } |
  | And IMM                | 5      | ANDI R1 IMM    | R1 = R1 & IMM                   |
  | Exclusive OR           | 6      | EOR R1 R2      | R1 = R1 ⊕ R2                    |
  | Branch Register        | 7      | BR R1 R2       | PC = R1 concat R2               |
  | Shift Arithmetic left  | 8      | SAL R1 IMM     | R1 = R1 << IMM                  |
  | Shift Arithmetic Right | 9      | SAR R1 IMM     | R1 = R1 >> IMM                  |
  | load to Register       | 10     | LDR R1 Address | R1 = MEM[Address]               |
  | Store from Register    | 11     | STR R1 Address | MEM[Address] = R1               |

## Registers

- Size: 8 bits
- General Purpose : 64 ( R0 to R63 )
- Status:

  - Carry Flag (C):
    -Check on 9th bit (bit 8) of UNSIGNED[VALUE1] OP UNSIGNED[VALUE2] == 1 or not
  - Updated every ADD

  - Overflow flag (V):

    - Indicates when the result of a signed number operation is too large, causing the high-order bit to overflow into the sign bit.

    - If 2 numbers:

      - added:both have the same sign, then overflow occurs (V = 1) if and only if the result has the opposite sign.
        Overflow never occurs when adding operands with different signs.

      - subtracted:and their signs are different, then overflow occurs (V= 1) if and only if the result has the same sign as the subtrahend.

    - updated every ADD and SUB instruction.

  - Negative flag (N):
    - N = 1 if result is negative.
    - N = 0 if result is positive or zero.
    - updated every ADD, SUB, MUL, ANDI, EOR, SAL, and SAR instruction.
  - Sign flag (S):
    - S = N ⊕ V
    - updated every ADD and SUB instruction.
  - Zero flag (Z):
    - Z = 1 if result is 0.
    - Z = 0 if result is not 0.
    - updated every ADD, SUB, MUL, ANDI, EOR, SAL, and SAR instruction.

- Program Counter
  - size : 16 bits
  - As each instruction gets fetched, the program counter is incremented to point to the next instruction to be executed

A flag value can only be updated by the instructions related to it.

## Data Memory

- Size: 2048 rows
- Row : 8 bits
- Address : 0 to 2047
  - word/byte adressable
