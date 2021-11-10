#include <stdio.h>
#include <stdlib.h>

#define HALT_OPCODE 0x19

//Function Declarations
void fetchNextInstruciton(void);
void executeInstruction(void);
unsigned char domath(int in, int out, char op);
unsigned int get16oprand(void);
unsigned char get8oprand(void);

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
    unsigned int mathin;
    unsigned int mathout;
    unsigned char mempos;
    unsigned char reg;
    unsigned char method;
    //Math section
    if ((IR & 0x80) == 0x80) {
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
        case 0x2: // Constant 
            if (destination == 0x1) {
                mathin = get8oprand();
            }
            else {
                mathin = get16oprand();
            }
            break;
        case 0x3: // Direct memory address
            mathin = get16oprand();
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
        case 0x2: // MAR destination
            mathout = MAR;
            MAR = domath(mathin, mathout, function);
            break;
        case 0x3: // Direct memory address
            mathout = get16oprand();
            memory[PC + 1] = (domath(mathin, mathout, function) & 0x00FF);
            memory[PC + 2] = ((domath(mathin, mathout, function) & 0xFF00) >> 8);
            break;
        }
            
    }
    // Memory operations section
    if (((IR & 0xF0) == 0x00) && IR > 0x00) {   //This function was written by Sean Huber, created on 11/9/2021 Edited by: No one so far :)
        function = IR & 0x08;
        reg = IR & 0x04;
        method = IR & 0x03;

        switch (function) {
        case 0x0: // Store
            switch (method) {
            case 0x0: // Oprand is used as address
                if (reg == 0x0) {
                    memeory[get16oprand()] = ACC;
                }
                if (reg == 0x1) {
                    memory[get16oprand()] = (MAR & 0x0F);
                    memory[get16oprand()+1] = ((MAR & 0xF0)>>8);
                }
                break;
            case 0x1: // Operand is used as a constant
                if (reg == 0x0) {
                    memeory[get16oprand()] = ACC;
                }
                if (reg == 0x1) {
                    memory[get16oprand()] = (MAR & 0x0F);
                    memory[get16oprand() + 1] = ((MAR & 0xF0) >> 8);
                }
                break;
            case 0x2: // Indirect (MAR used as pointer)
                if (reg == 0x0) {
                    memeory[MAR] = ACC;
                }
                if (reg == 0x1) {
                    memory[MAR] = MAR;
                }
                break;
            }
            break;
        case 0x1: // Load
            switch (method){
            case 0x0: // Oprand is used as address
                if (reg == 0x0) {
                    ACC = memory[get16oprand()];
                }
                if (reg == 0x1) {
                    MAR = memory[get16oprand()];
                }
                break;
            case 0x1: // Operand is used as a constant
                if (reg == 0x0) {
                    ACC = memory[get16oprand()];
                }
                if (reg == 0x1) {
                    MAR = memory[get16oprand()];
                }
                break;
            case 0x2: // Indirect (MAR used as pointer)
                if (reg == 0x0) {
                    ACC = memory[MAR];
                }
                if (reg == 0x1) {
                    MAR = memory[MAR];
                }
                break;
            }
            break;
        }

    }

    return 0;
}

unsigned int get16oprand(void) {
    return ((memory[PC + 1] & (memory[PC + 2] << 8)));
}
unsigned char get8oprand(void) {
    return (memory[PC + 1]);
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