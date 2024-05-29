cmake_minimum_required(VERSION 3.12)
project(processor)

# Enable C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Assuming your header files are in a folder named "headers"
include_directories(Headers)


# Add source files
set(SOURCES
    src/Main/Main.c
    src/ALU/ALU.c
    src/DataMemory/DataMemory.c
    src/InstructionMemory/InstructionMemory.c
    src/Registers/Registers.c
    # Add more source files here if needed
)

# Add executable target
add_executable(processor  ${SOURCES})

# Add include directories
target_include_directories(processor PUBLIC include)


