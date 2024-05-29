#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

/* ^^ these are the include guards */

/* 
 * Prototypes for the functions
 */

#include "Structs.h"


/**
 * @brief Resets the pipeline.
 *
 * This function is responsible for resetting the pipeline in the computer processor.
 * It clears any stored instructions and prepares the pipeline for the execution of new instructions.
 */
void ResetPipeline();


/**
 * @brief get the opcode of the instruction
 * 
 * @param instruction The instruction to get the opcode from.
 * @return The opcode of the instruction.
*/
uint8_t GetOpcode(int16_t instruction);

/**
 * @brief get the first operand of the instruction
 * 
 * @param instruction The instruction to get the first operand from.
 * @return The first operand of the instruction.
*/
uint8_t GetOperand1(int16_t instruction);

/**
 * @brief get the second operand of the instruction
 * 
 * @param instruction The instruction to get the second operand/Immediate value from.
 * @return The second operand/Immediate value of the instruction.
*/
int8_t GetValue2(int16_t instruction);

/**
 * @brief get the type of the instruction
 * 
 * @param instruction The instruction to get the type from.
 * @return The type of the instruction.
*/
char GetOpcodeType(uint8_t opcode);

/**
 * @brief Writes an instruction to the instruction memory at the specified address.
 * 
 * @param address The address in the instruction memory where the instruction will be written.
 * @param instruction The instruction to be written.
 */
void WriteInstructionMemory(uint16_t  address, uint16_t instruction);

/**
 * @brief Reads an instruction from the instruction memory at the specified address.
 * 
 * @param address The address in the instruction memory from where the instruction will be read.
 * @return The instruction read from the instruction memory.
 */
int16_t ReadInstructionMemory(uint16_t address);

/**
 * @brief Fetches the next instruction from the instruction memory and updates the pipeline.
 */
void fetchPipeline();

/**
 * @brief Decodes the instruction in the pipeline and prepares the necessary data for execution.
 */
void decodePipeline();

/**
 * @brief Executes the instruction in the pipeline.
 */
void executePipeline();

/**
 * @brief Decodes the given instruction.
 * 
 * @param instruction The instruction to be decoded.
 * @return The decoded instruction.
 */
Instruction decode(uint16_t  instruction);

/**
 * @brief Executes the given instruction.
 * 
 * @param ins The instruction to be executed.
 */
void execute(Instruction ins);

/**
 * @brief Resets the instruction memory, clearing all instructions.
 */
void ResetInstructionMemory();

/**
 * @brief Prints all instructions in the instruction memory.
 */
void PrintAllInstructionMemory();

#endif
