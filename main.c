#include <stdio.h>
#include <stdlib.h>

#define HALT_OPCODE 0x19

//Function Declarations
void fetchNextInstruciton(void);
void executeInstruction(void);

//Global Variables
unsigned int MAR = 0;
unsigned int PC = 0;
unsigned char memory[65536];
unsigned char ACC = 0;
unsigned char IR = 0;

int main (int argc, char* argv[])
{
    while(memory[PC] != HALT_OPCODE)
    {
        fetchNextInstruciton();
        executeInstruction();
    }
    return 0;
}
