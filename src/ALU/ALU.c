#include "../Headers/Registers.h"
#include "../Headers/DataMemory.h"
#include "../Headers/InstructionMemory.h"
#include <stdint.h>

/**
 * Performs addition of two registers and stores the result in the first register.
 * Updates the carry, negative, sign, zero, and overflow flags accordingly.
 *
 * @param R1 The first register.
 * @param R2 The second register.
 */
void ADD(uint8_t R1, uint8_t R2)
{
    uint8_t result = ReadRegister(R1) + ReadRegister(R2);
    uint8_t r1 = ReadRegister(R1);
    uint8_t r2 = ReadRegister(R2);
    updateCarryFlag(r1, r2);
    updateNegativeFlag(result);
    updateSignFlag(result);
    updateZeroFlag(result);
    updateOverflowFlag(r1, r2, result,0);
    WriteRegister(R1, result);
}

/**
 * Performs subtraction of two registers and stores the result in the first register.
 * Updates the negative, sign, zero, and overflow flags accordingly.
 *
 * @param R1 The first register.
 * @param R2 The second register.
 */
void SUB(uint8_t R1, uint8_t R2)
{
    int8_t result = ReadRegister(R1) - ReadRegister(R2);
    int8_t r1 = ReadRegister(R1);
    int8_t r2 = ReadRegister(R2);
    updateNegativeFlag(result);
    updateSignFlag(result);
    updateZeroFlag(result);
    updateOverflowFlag(r1, r2, result,1);
    WriteRegister(R1, result);
}

/**
 * Performs multiplication of two registers and stores the result in the first register.
 * Updates the negative and zero flags accordingly.
 *
 * @param R1 The first register.
 * @param R2 The second register.
 */
void MUL(uint8_t R1, uint8_t R2)
{
    int8_t result = ReadRegister(R1) * ReadRegister(R2);
    int8_t r1 = ReadRegister(R1);
    int8_t r2 = ReadRegister(R2);

    updateNegativeFlag(result);
    updateZeroFlag(result);
    WriteRegister(R1, result);
}

/**
 * Moves an immediate value to a register.
 *
 * @param R1 The register to store the immediate value in.
 * @param IMM The immediate value.
 */
void MOVI(uint8_t R1, int8_t IMM)
{
    WriteRegister(R1, IMM);
}

/**
 * Branches to a specified instruction address if the value in the register is zero.
 *
 * @param R1 The register to check.
 * @param IMM The instruction address to branch to.
 */
void BEQZ(uint8_t R1, int8_t IMM)
{
    if (ReadRegister(R1) == 0)
    {
        SetPC(GetPC() + IMM - 1);
        ResetPipeline();
    }
}

/**
 * Performs bitwise AND operation between a register and an immediate value.
 * Updates the negative and zero flags accordingly.
 *
 * @param R1 The register.
 * @param IMM The immediate value.
 */
void ANDI(uint8_t R1, int8_t IMM)
{
    updateNegativeFlag(ReadRegister(R1) & IMM);
    updateZeroFlag(ReadRegister(R1) & IMM);
    WriteRegister(R1, ReadRegister(R1) & IMM);
}

/**
 * Performs bitwise exclusive OR (XOR) operation between two registers and stores the result in the first register.
 * Updates the negative and zero flags accordingly.
 *
 * @param R1 The first register.
 * @param R2 The second register.
 */
void EOR(uint8_t R1, uint8_t R2)
{
    int8_t result = ReadRegister(R1) ^ ReadRegister(R2);
    int8_t r1 = ReadRegister(R1);
    int8_t r2 = ReadRegister(R2);
    updateNegativeFlag(result);
    updateZeroFlag(result);
    WriteRegister(R1, result);
}

/**
 * Branches to a specified instruction address based on the values in two registers.
 *
 * @param R1 The first register.
 * @param R2 The second register.
 */
void BR(uint8_t R1, uint8_t R2)
{
    SetPC((ReadRegister(R1) << 8) | ReadRegister(R2));
    ResetPipeline();
}

/**
 * Performs left shift operation on a register by a specified number of bits.
 * Updates the negative and zero flags accordingly.
 *
 * @param R1 The register.
 * @param IMM The number of bits to shift by.
 */
void SAL(uint8_t R1, int8_t IMM)
{
    int8_t result = ReadRegister(R1) << IMM;
    int8_t r1 = ReadRegister(R1);
    updateNegativeFlag(result);
    updateZeroFlag(result);
    WriteRegister(R1, result);
}

/**
 * Performs right shift operation on a register by a specified number of bits.
 * Updates the negative and zero flags accordingly.
 *
 * @param R1 The register.
 * @param IMM The number of bits to shift by.
 */
void SAR(uint8_t R1, int8_t IMM)
{
    int8_t result = ReadRegister(R1) >> IMM;
    int8_t r1 = ReadRegister(R1);
    updateNegativeFlag(result);
    updateZeroFlag(result);
    WriteRegister(R1, result);
}

/**
 * Loads the value from the specified memory address into a register.
 *
 * @param R1 The register to store the loaded value in.
 * @param address The memory address to load from.
 */
void LDR(uint8_t R1, uint8_t address)
{
    WriteRegister(R1, ReadDataMemory(address));
}

/**
 * Stores the value from a register into the specified memory address.
 *
 * @param R1 The register containing the value to store.
 * @param address The memory address to store the value in.
 */
void STR(uint8_t R1, uint8_t address)
{
    WriteDataMemory(address, ReadRegister(R1));
}
