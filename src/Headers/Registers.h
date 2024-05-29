#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

/**
 * Updates the carry flag based on the result of an arithmetic operation.
 *
 * @param operand1 The first operand of the arithmetic operation.
 * @param operand2 The second operand of the arithmetic operation.
 * @param result The result of the arithmetic operation.
 */
void updateCarryFlag(uint8_t operand1, uint8_t operand2);

/**
 * Updates the overflow flag based on the result of an arithmetic operation.
 *
 * @param operand1 The first operand of the arithmetic operation.
 * @param operand2 The second operand of the arithmetic operation.
 * @param result The result of the arithmetic operation.
 */
void updateOverflowFlag(int8_t operand1, int8_t operand2, int8_t result, bool operation);

/**
 * Updates the negative flag based on the result of an arithmetic operation.
 *
 * @param result The result of the arithmetic operation.
 */
void updateNegativeFlag(int8_t result);

/**
 * Updates the sign flag based on the result of an arithmetic operation.
 *
 * @param result The result of the arithmetic operation.
 */
void updateSignFlag(int8_t result);

/**
 * Updates the zero flag based on the result of an arithmetic operation.
 *
 * @param result The result of the arithmetic operation.
 */
void updateZeroFlag(int8_t result);

/**
 * Reads the value stored in a register.
 *
 * @param reg The register number.
 * @return The value stored in the register.
 */
int8_t ReadRegister(uint8_t reg);

/**
 * Writes a value to a register.
 *
 * @param reg The register number.
 * @param value The value to be written to the register.
 */
void WriteRegister(uint8_t reg, int8_t value);

/**
 * Resets all registers to their initial values.
 */
void ResetRegisters();

/**
 * Prints the values of all registers.
 */
void PrintAllRegisters();

/**
 * Prints the value of the status register.
 */
void PrintStatusRegister();

/**
 * Returns the value of the program counter (PC).
 *
 * @return The value of the program counter.
 */
uint16_t GetPC();

/**
 * Sets the value of the program counter (PC).
 *
 * @param value The value to be set as the program counter.
 */
void SetPC(uint16_t value);

/**
 * Increments the value of the program counter (PC) by 1.
 */
void IncrementPC();

#endif