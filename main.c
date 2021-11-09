#include <stdio.h>
#include <stdlib.h>

#define HALT_OPCODE 0x19

//Function Declarations
void fetchNextInstruciton(void);
void executeInstruction(void);
unsigned char domath(int in, int out, char op);

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

/*
This section is for anyone reading the code while under construction.
Here I will detail the order of operations that entail the support of other sections.
So far there are no requests.
*/





unsigned char executeInstruction(void) //This function was written by Sean Huber, created on 11/5/2021 Edited by: No one so far :)
{   
    //local variables
    unsigned char function;
    unsigned char destination;
    unsigned char source;
    unsigned int mathin;
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
            mathin = memory[MAR];
            break;
        case 0x1: // ACC i got that here
            mathin = ACC;
            break;
        case 0x2: // Address register MAR address is in mar
            mathin = (memory[PC + 1] & (memory[PC + 2] << 8));
            break;
        case 0x3: // Direct memory address
            mathin = (memory[PC + 1] & (memory[PC + 2] << 8));
            break;
        }
        switch (destination) { // This pulls the vlaue for the destination for mathmatical operations because i suck at pointers and addressing
        case 0x0: // MAR as memory pointer requires memory call
            mathout = memory[MAR];
            memory[MAR] = domath(mathin, mathout, function);
            break;
        case 0x1: // ACC i got that here
            mathout = ACC;
            ACC = domath(mathin, mathout, function);
            break;
        case 0x2: // Constant look for the next 
            mathout = MAR;
            MAR = domath(mathin, mathout, function);
            break;
        case 0x3: // Direct memory address
            mathout = (memory[PC + 1] & (memory[PC + 2] << 8));
            memory[PC + 1] = (domath(mathin, mathout, function) & 0x00FF);
            memory[PC + 2] = ((domath(mathin, mathout, function) & 0xFF00) >> 8);
            break;
        }
            
    }
    return 0;
}

unsigned char domath(int in, int out, char op) //This function was written by Sean Huber, created on 11/5/2021 Edited by: No one so far :)
{
    unsigned int temp;
    switch (op) {
    case 0x0: // AND
        temp = in & out;
        break;
    case 0x1: // OR
        temp = in | out;
        break;
    case 0x2:  // XOR
        temp = in ^ out;
        break;
    case 0x3: // ADD
        temp = in + out;
        break;
    case 0x4: // SUB
        temp = in - out;
        break;
    case 0x5: // INC
        temp = in++;
        break;
    case 0x6: // DEC
        temp = in--;
        break;
    case 0x7: // NOT
        temp = ~in;
        break;
    }
    return temp;

}

