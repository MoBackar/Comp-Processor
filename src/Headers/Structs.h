#ifndef Structs_H_INCLUDED
#define Structs_H_INCLUDED

/* ^^ these are the include guards */

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Represents an instruction in the processor.
 */
typedef struct {
    uint8_t opcode :4;       /**< The opcode of the instruction. */
    uint8_t operand1 : 6;     /**< The first operand of the instruction. */
    int8_t value2 : 6;       /**< The second operand or immediate value or address. */
    char type;          /**< The type of the instruction. */
} Instruction;

/**
 * @brief Represents a stage in the processor pipeline.
 */
typedef struct {
    Instruction instruction;    /**< The decoded instruction in the pipeline stage. */
    bool valid;                 /**< Indicates if the stage is valid. */
    uint8_t pcVal;                /**< The program counter value. to be able to print it out during the pipeline*/
} PipelineStage;

/**
 * @brief Represents the fetched instruction before decoding.
 */
typedef struct {
    int16_t instruction;    /**< The fetched instruction. */
    bool valid;               /**< Indicates if the fetched instruction is valid. */
    uint8_t pcVal;                /**< The program counter value. */
} FetchedInstruction;


#endif
