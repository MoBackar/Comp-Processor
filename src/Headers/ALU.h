#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED


#include <stdint.h>
/**
 * Adds the values of two registers and stores the result in the first register.
 * 
 * @param R1 The first register.
 * @param R2 The second register.
 */
void ADD(uint8_t R1, uint8_t R2);

/**
 * Subtracts the value of the second register from the first register and stores the result in the first register.
 * 
 * @param R1 The first register.
 * @param R2 The second register.
 */
void SUB(uint8_t R1, uint8_t R2);

/**
 * Multiplies the values of two registers and stores the result in the first register.
 * 
 * @param R1 The first register.
 * @param R2 The second register.
 */
void MUL(uint8_t R1, uint8_t R2);

/**
 * Moves the Immediate value to the first register.
 * 
 * @param R1 The first register.
 * @param IMM The Immediate Value.
 */
void MOVI(uint8_t R1, int8_t IMM);

/**
 * Branches to the specified address if the value of the first register is zero.
 * 
 * @param R1 The first register.
 * @param IMM The address to branch to.
 */
void BEQZ(uint8_t R1, int8_t IMM);

/**
 * Performs a bitwise AND operation between the values of the first register and the Immediate value and stores the result in the first register.
 * 
 * @param R1 The first register.
 * @param IMM The Immediate Value.
 */
void ANDI(uint8_t R1, int8_t IMM);

/**
 * Performs a bitwise exclusive OR (XOR) operation between the values of the first and second registers and stores the result in the first register.
 * 
 * @param R1 The first register.
 * @param R2 The second register.
 */
void EOR(uint8_t R1, uint8_t R2);

/**
 * Branches to the specified address unconditionally.
 * 
 * @param R1 The first register.
 * @param R2 The address to branch to.
 */
void BR(uint8_t R1, uint8_t R2);

/**
 * Shifts the value of the first register to the left by the number of bits specified.
 * 
 * @param R1 The first register.
 * @param IMM The number of bits to shift by.
 */
void SAL(uint8_t R1, int8_t IMM);

/**
 * Shifts the value of the first register to the right by the number of bits specified .
 * 
 * @param R1 The first register.
 * @param IMM The number of bits to shift by.
 */
void SAR(uint8_t R1, int8_t IMM);

/**
 * Loads the value from memory at the address specified in the second register and stores it in the first register.
 * 
 * @param R1 The first register.
 * @param R2 The address to load from.
 */
void LDR(uint8_t R1, uint8_t address);

/**
 * Stores the value from the first register into memory at the address specified in the second register.
 * 
 * @param R1 The first register.
 * @param R2 The address to store to.
 */
void STR(uint8_t R1, uint8_t address);

#endif