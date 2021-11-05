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

