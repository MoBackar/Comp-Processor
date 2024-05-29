
#include <stdint.h>

int8_t data_memory[2048];


/**
 * Read data from the data memory at the specified address.
 *
 * @param address The memory address to read from.
 * @return The data stored at the specified address.
 */
int8_t ReadDataMemory(uint16_t address)
{
    return data_memory[address];
}

/**
 * Write data to the data memory at the specified address.
 *
 * @param address The memory address to write to.
 * @param value The data to be written.
 */
void WriteDataMemory(uint16_t address, int8_t value)
{
    data_memory[address] = value;
    printf("Update DataMemory Address:%d DataMemory Data: %d\n", address, value);
}

/**
 * Print all non-zero data stored in the data memory.
 */
void PrintAllDataMemory()
{

    printf("Final State of Data Memory: \n");
    printf("-------------------------------------------------- \n");
    for (int i = 0; i < 2048; i++)
    {
        if (data_memory[i] != 0)
        {
            printf("Address:%d DataMemory Data: %d\n", i, data_memory[i]);
        }
    }
    printf("-------------------------------------------------- \n");
}

/**
 * Reset the data memory by setting all values to zero.
 */
void ResetDataMemory()
{
    for (int i = 0; i < 2048; i++)
    {
        data_memory[i] = 0;
    }
}