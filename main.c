<<<<<<< Updated upstream
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void fetchNextInstruction(void);
int readFile(void);
char * getBinary(char * hexValue);
char * valueOf(char digit);

unsigned char memory[65536];
unsigned char ACC = 0;
unsigned char IR = 0;
unsigned int MAR = 0;
unsigned int PC = 0;

int main(int argc, char *argv[])
{
    

    //readFile();
    //printf("%c", memory[0]);
    return 0;
}

void fetchNextInstruction(void)
{
/*
Use the program counter (PC) as an index to retrieve an instruction from the array 
memory[].

Store the retrieved instruction to the instruction register (IR).

Determine from the instruction how much to increment PC so that it points to the 
next instruction in memory[] and perform the increment.
*/
    //printf("%c", &memory[PC]);
    //IR = &memory[PC];
}

int readFile()
{ 
    //Read file
	char * filename = "mem_in.txt"; 
	FILE * fp = fopen(filename, "r"); 
	if (fp == NULL) 
        return 1; 
	unsigned char c; 
    int i = 0;
    //Iterate through file and grab info
	while((c = fgetc(fp)) != EOF) 
	{
		if(c != ' ' || c != '\n') 
		{ 
            memory[i] = c;
            //printf("%c", memory[i]);
		} 
        i++;
	} 
	fclose(fp);
}

char * valueOf(char digit)
{
    switch(digit)
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A':
        case 'a': return "1010";
        case 'B':
        case 'b': return "1011";
        case 'C':
        case 'c': return "1100";
        case 'D':
        case 'd': return "1101";
        case 'E':
        case 'e': return "1110";
        case 'F':
        case 'f': return "1111";
        default:
        {
            printf("Cannot decode that symbol: %c", digit);
            return 0;
        }
    }
}

char * getBinary(char * hexValue)
{
    char *hexOne;
    char *hexTwo;
    hexOne = valueOf(hexValue[0]);
    hexTwo = valueOf(hexValue[1]);
    char *result = malloc(strlen(hexOne) + strlen(hexTwo) + 1);
    strcpy(result,hexOne);
    strcat(result,hexTwo);

    return result;
}

=======
#include <stdio.h>
#include <stdlib.h>

#define HALT_OPCODE 0x19

//Function Declarations
void fetchNextInstruciton(void);
unsigned char executeInstruction(void);
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
                    memory[get16oprand()] = ACC;
                }
                if (reg == 0x1) {
                    memory[get16oprand()] = (MAR & 0x0F);
                    memory[get16oprand()+1] = ((MAR & 0xF0)>>8);
                }
                break;
            case 0x1: // Operand is used as a constant
                if (reg == 0x0) {
                    memory[get16oprand()] = ACC;
                }
                if (reg == 0x1) {
                    memory[get16oprand()] = (MAR & 0x0F);
                    memory[get16oprand() + 1] = ((MAR & 0xF0) >> 8);
                }
                break;
            case 0x2: // Indirect (MAR used as pointer)
                if (reg == 0x0) {
                    memory[MAR] = ACC;
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
>>>>>>> Stashed changes
