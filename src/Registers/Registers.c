/**
 * @file Registers.c
 * @brief Implementation of register-related functions.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#define BitVal(data,y) ( (data>>y) & 1)      /** Return Data.Y value   **/
#define SetBit(data,y)    data |= (1 << y)    /** Set Data.Y   to 1    **/
#define ClearBit(data,y)  data &= ~(1 << y)   /** Clear Data.Y to 0    **/
#define TogleBit(data,y)     (data ^=BitVal(y))     /** Togle Data.Y  value  **/
#define Togle(data)   (data =~data )         /** Togle Data value     **/


int8_t generalRegisters[64]; // Array to store general purpose registers
uint8_t SREG = 0;              // status register flags: C, V, N, S, Z ,0,0,0
uint16_t pc = 0;               // Program counter

/**
 * @brief Reads the value of a register.
 * @param reg The register number.
 * @return The value of the register.
 */
int8_t ReadRegister(uint8_t reg)
{
    return generalRegisters[reg];
}

/**
 * @brief Writes a value to a register.
 * @param address The register number.
 * @param value The value to be written.
 */
void WriteRegister(uint8_t address, int8_t value)
{
    generalRegisters[address] = value;
    printf("Updated: R%d: %d\n", address, value);
}

/**
 * @brief Increments the program counter by 1.
 */
void IncrementPC()
{
    pc++;
}

/**
 * @brief Sets the value of the program counter.
 * @param value The value to be set.
 */
void SetPC(uint16_t value)
{
    pc = value;
    printf("Updated: PC: %d\n", pc);
}

/**
 * @brief Gets the value of the program counter.
 * @return The value of the program counter.
 */
uint8_t GetPC()
{
    return pc;
}

/**
 * @brief Updates the carry flag based on the result of an operation.
 * @param operand1 The first operand.
 * @param operand2 The second operand.
 * @param result The result of the operation.
 */
void updateCarryFlag(uint8_t operand1, uint8_t operand2)
{
    if ((operand1 + operand2) > 255)
    {
        SetBit(SREG, 0);
    }
    else
    {
        ClearBit(SREG, 0);
    }
        printf("Carry Flag Updated: %d\n", BitVal(SREG, 0));
    
}

/**
 * @brief Updates the overflow flag based on the result of an operation.
 * @param operand1 The first operand.
 * @param operand2 The second operand.
 * @param result The result of the operation.
 */
void updateOverflowFlag(int8_t operand1, int8_t operand2, int8_t result, bool operation)
{
    if(operation == 0){
        if ((operand1 > 0 && operand2 > 0 && result < 0) || (operand1 < 0 && operand2 < 0 && result > 0))
        {
            SetBit(SREG, 1);
        }
        else
        {
            ClearBit(SREG, 1);
        }
    }
    else{
        if ((operand1 < 0 && operand2 > 0 && result > 0) || (operand1 > 0 && operand2 < 0 && result < 0))
        {
            SetBit(SREG, 1);
        }
        else
        {
           ClearBit(SREG, 1);
        }
    }
    printf("Overflow Flag Updated: %d\n", BitVal(SREG, 1));
    
}

/**
 * @brief Updates the negative flag based on the result of an operation.
 * @param result The result of the operation.
 */
void updateNegativeFlag(int8_t result)
{
    if (result < 0)
    {
        SetBit(SREG, 2);
    }
    else
    {
        ClearBit(SREG, 2);
    }
    printf("Negative Flag Updated: %d\n", BitVal(SREG, 2));

}

/**
 * @brief Updates the sign flag based on the result of an operation.
 * @param result The result of the operation.
 */
void updateSignFlag(int8_t result)
{

    if (result == 0)
    {
        SetBit(SREG, 3);
    }
    else
    {
        ClearBit(SREG, 3);
    }

    printf("Sign Flag Updated: %d\n", BitVal(SREG, 3));
    
}

/**
 * @brief Updates the zero flag based on the result of an operation.
 * @param result The result of the operation.
 */
void updateZeroFlag(int8_t result)
{
    if (result == 0)
    {
        SetBit(SREG, 4);
    }
    else
    {
        ClearBit(SREG, 4);
    }
    printf("Zero Flag Updated: %d\n", BitVal(SREG, 4));
}

/**
 * @brief Resets all registers and the program counter to zero.
 */
void ResetRegisters()
{
    for (int i = 0; i < 64; i++)
    {
        generalRegisters[i] = 0;
    }
    for (int i = 0; i < 8; i++)
    {
        ClearBit(SREG, i);
    }
    pc = 0;
}

/**
 * @brief Prints the status register flags.
 */
void PrintStatusRegister()
{
    printf("Status Register:\n");
    printf("C: %d\n", BitVal(SREG, 0));
    printf("V: %d\n", BitVal(SREG, 1));
    printf("N: %d\n", BitVal(SREG, 2));
    printf("S: %d\n", BitVal(SREG, 3));
    printf("Z: %d\n", BitVal(SREG, 4));
    printf("6: %d\n", BitVal(SREG, 5));
    printf("7: %d\n", BitVal(SREG, 6));
    printf("8: %d\n", BitVal(SREG, 7));
}

/**
 * @brief Prints the values of all non-zero registers.
 */
void PrintAllRegisters()
{
    printf("Final State of Registers:\n");
    printf("-------------------------------------------------- \n");
    printf("General Registers:\n");
    for (int i = 0; i < 64; i++)
    {
    
            printf("Register %d: %d\n", i, generalRegisters[i]);
            printf("-------------------------------------------------- \n");
    
    }
    printf("-------------------------------------------------- \n");
    PrintStatusRegister();
}