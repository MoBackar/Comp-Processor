/**
 * @file Main.c
 * @brief This file contains the main function and related functions for the computer processor simulation.
 */

#include "../Headers/InstructionMemory.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MaxClockCycles;                      // Global variable in main.c gets init in load program function after the while loop
int clockcycles = 1;                     // global var to track the current clock cycle for the program
extern int16_t instruction_memory[1024]; /**< External array representing the instruction memory. */
extern FetchedInstruction pipeline1;     /**< External variable representing the first pipeline stage. */
extern PipelineStage pipeline2;          /**< External variable representing the second pipeline stage. */
extern PipelineStage pipeline3;          /**< External variable representing the third pipeline stage. */
extern PipelineStage pipeline4;          /**< External variable representing the fourth pipeline stage. */
extern int8_t data_memory[2048];         /**< External array representing the data memory. */
extern int8_t generalRegisters[64];      /**< External array representing the registers. */
extern uint8_t SREG;                     /**< External array representing the status register. SREG[0] = C, SREG[1] = V, SREG[2] = N, SREG[3] = S, SREG[4] = Z */
extern uint16_t pc;                      /**< External variable representing the program counter. */

// Function to convert opcode string to corresponding opcode value
uint8_t incodeOpcode(char *opcode)
{
    if (strcmp(opcode, "ADD") == 0)
    {
        return 0;
    }
    else if (strcmp(opcode, "SUB") == 0)
    {
        return 1;
    }
    else if (strcmp(opcode, "MUL") == 0)
    {
        return 2;
    }
    else if (strcmp(opcode, "MOVI") == 0)
    {
        return 3;
    }
    else if (strcmp(opcode, "BEQZ") == 0)
    {
        return 4;
    }
    else if (strcmp(opcode, "ANDI") == 0)
    {
        return 5;
    }
    else if (strcmp(opcode, "EOR") == 0)
    {
        return 6;
    }
    else if (strcmp(opcode, "BR") == 0)
    {
        return 7;
    }
    else if (strcmp(opcode, "SAL") == 0)
    {
        return 8;
    }
    else if (strcmp(opcode, "SAR") == 0)
    {
        return 9;
    }
    else if (strcmp(opcode, "LDR") == 0)
    {
        return 10;
    }
    else if (strcmp(opcode, "STR") == 0)
    {
        return 11;
    }
    else
    {
        return -1;
    }
}

/**
 * @brief Loads the program from the given file into the instruction memory.
 *
 * @param file_name The name of the assembly file to load.
 */
void LoadProgram(char *file_name)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("Error: Assembly file not found\n");
        printf("Please make sure the file exists\n");
        printf("Exiting...\n");
        exit(1);
    }
    int address = 0;
    /**
     * This while loop continues until the end of the file is reached.
     * It checks if the end-of-file indicator for the given file stream is set.
     * The feof() function returns a non-zero value if the end-of-file indicator is set,
     * and 0 otherwise.
     */
    while (!feof(file))
    {

        char opcode[5];
        char operand1[4];
        char operand2[4];
        /**
         * Reads three strings from the file using the specified format and stores them in the given variables.
         *
         * @param file The file to read from.
         * @param opcode The variable to store the first string.
         * @param operand1 The variable to store the second string.
         * @param operand2 The variable to store the third string.
         *
         * @return The number of items successfully read and assigned, or EOF if an error occurred.
         */
        fscanf(file, "%4s %3s %3s", opcode, operand1, operand2);
        // Convert the opcode string to an integer
        uint8_t opcode_int = incodeOpcode(opcode); // encodes the opcode string to a 4-bit integer
        // Convert the operand strings to integers
        uint8_t operand1_int = atoi(operand1 + 1);
        int8_t operand2_int;
        switch (opcode_int)
        {
            case 0:
            case 1:
            case 2:
            case 6:
            case 7:
                operand2_int = atoi(operand2 + 1);
                break;
            case 3:
            case 4:
            case 5:
            case 8:
            case 9:
            case 10:
            case 11:
                operand2_int = atoi(operand2);
                break;
        }
        // Print the opcode and operands
        // printf("Opcode: %04b, Operand1: %06b, Operand2: %06b\n", opcode_int, operand1_int, operand2_int&0b111111);

        // Combine the opcode and operands into a 16-bit instruction
        uint16_t instruction = ((opcode_int & 0b1111) << 12) | ((operand1_int & 0b111111) << 6) | (operand2_int & 0b111111);
        // printf("Instruction: %016b\n", instruction);
        // Write the instruction to the instruction memory
        WriteInstructionMemory(address, instruction);
        address++;
    }
    fclose(file);
}

/**
 * @brief Resets the processor by resetting the data memory, instruction memory, and registers.
 */
void ResetProcessor()
{
    ResetDataMemory();
    ResetInstructionMemory();
    ResetRegisters();
}

/**
 * @brief The main function that simulates the computer processor.
 *
 * @return 0 indicating successful execution.
 */
int main()
{
    ResetProcessor();
    // Only works with absolute path of the txt file
    LoadProgram("/home/ashmxwy/Desktop/University/Work/CA/c-computer-processor/src/Test/ALL_test.txt");

    /**
     * This function represents the main loop of the processor. It executes the pipeline stages
     * (fetch, decode, execute) until certain conditions are met.
     *
     * Conditions for loop termination:
     *  - The instruction pointer is not NULL (needed for the first instruction and to check if there are instructions left to fetch)
     *  - The second pipeline stage (pipeline2) is valid, indicating that the last decode operation is still in progress
     *  - The fourth pipeline stage (pipeline4) is valid, indicating that the last execute operation is still in progress
     *  - The number of clock cycles is less than the maximum allowed clock cycles (MaxClockCycles)
     *
     * Inside the loop, the current clock cycle is printed, and the fetch, decode, and execute pipeline stages are executed.
     * After each iteration, the clock cycle is incremented, and a separator line is printed.
     * Finally, the instruction pointer is updated by reading the instruction memory at the current program counter (PC).
     */
    printf("Cycle: %i \n", clockcycles);
    fetchPipeline();
    while (pipeline1.valid == true || pipeline2.valid == true || pipeline3.valid == true || pipeline4.valid == true)
    {

        if (clockcycles != 1)
        {
            printf("Cycle: %i \n", clockcycles);
            fetchPipeline();
        }
        decodePipeline();

        executePipeline();

        clockcycles++;
        printf("-------------------------------------------------- \n");
    }

    /**
     * Prints the final state of registers and memory.
     * Calls the functions to print the final state of registers, data memory, and instruction memory.
     */

    PrintAllRegisters();
    PrintAllDataMemory();
    PrintAllInstructionMemory();

    return 0;
}