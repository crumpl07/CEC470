#include <stdio.h>
#include <stdlib.h>

#define HALT_OPCODE 0x19

//Function Declarations
void fetchNextInstruciton(void);
void executeInstruction(void);
unsigned char domath(char in, char out, char op);

//Global Variables
unsigned int MAR = 0;
unsigned int PC = 0;
unsigned char memory[65536];
unsigned char ACC = 0;
unsigned char IR = 0;

int main(int argc, char* argv[])
{
    while (memory[PC] != HALT_OPCODE)
    {
        fetchNextInstruciton();
        executeInstruction(); 
    }
    return 0;
}

unsigned char executeInstruction(void) //This function was written by Sean Huber, created on 11/5/2021 Edited by: No one so far :)
{   
    //local variables
    unsigned char function;
    unsigned char destination;
    unsigned char source;
    unsigned char mathin;
    unsigned char mathout;
    unsigned char mempos;
    //Math section
    if (IR & 0x80) {
        // creating easier to work with variables based on the call for mathmatical operations
        function = (IR & 0xF0) >> 4;
        destination = (IR & 0x0C) >> 2;
        source = (IR & 0x03);
        // Accuiring the in data
        switch (source) { // This pulls the value required for mathmatical operations becuase i suck at pointers and adressing
        case 0x0: // MAR as memory pointer requires memory call
            
            break;
        case 0x1: // ACC i got that here
            mathin = ACC;
            break;
        case 0x2: // Address register MAR address is in mar

            break;
        case 0x3: // Direct memory address

            break;
        }
        switch (destination) { // This pulls the vlaue for the destination for mathmatical operations because i suck at pointers and addressing
        case 0x0: // MAR as memory pointer requires memory call
            
            break;
        case 0x1: // ACC i got that here
            mathout = ACC;
            break;
        case 0x2: // Constant look for the next 

            break;
        case 0x3: // Direct memory address

            break;
        }
        


         
    }



    return 0;
}

unsigned char domath(char in, char out, char op)
{
    unsigned int temp;
    switch (op) {
    case 0x0: // AND

        break;
    case 0x1: // OR

        break;
    case 0x2:  // XOR

        break;
    case 0x3: // ADD
        temp = in + out;
        break;
    case 0x4: // SUB

        break;
    case 0x5: // INC

        break;
    case 0x6: // DEC

        break;
    case 0x7: // NOT

        break;
    }
    return temp;

}

