/*=============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Vigenere cipher
|
| Author: Dylan Money
| Language: c
|
| To Compile: gcc -o pa02 pa02.c
|
| To Execute: c -> ./pa02 inputFile.txt 8 
| where inputFile.txt is an ASCII input file
| and the number 8 could also be 16 or 32
| which are the valid checksum sizes, all
| other values are rejected with an error message
| and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Fall 2022
| Instructor: McAlpin
| Due Date: 11/ 27/ 22
|
+=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inFileCheck(char *fileName, int size);
void checkSum(int size, char *inString, unsigned int long *check);
unsigned int long bitMask(char *inString, int checkSize);

//===========================================================================================================================================================================================================

int main(int argc, char *argv[])
{
    //file name
    char *fileNameIn = malloc(sizeof(char) * 30);

    int checkBits;

    //if argc less than 2 you did it wrong
    if (argc < 2)
    {
        printf("Error! Insufficient arguments are provided at command line.\n");
        printf("At the command line pass the input file name followed by the checksum size\n");
    }
    //check if arg and vaild bit size
    else
    {
        strcpy(fileNameIn, argv[1]);

        checkBits = atoi(argv[2]);

        if (checkBits != 8 && checkBits != 16 && checkBits != 32)
        {
            printf( "Valid checksum sizes are 8, 16, or 32\n");
        }
        //do code next
        inFileCheck(fileNameIn, checkBits);
    }

    return 0;
}

// ==========================================================================================================================================================================================================

void inFileCheck(char *fileName, int checkSize)
{
    FILE *fileIn;

    int charVal = 0;
    int charCount = 0;
    int wordSize = checkSize / 8 + 1;
    unsigned int long *checksum = calloc(1, sizeof(unsigned int long));
    char *inputChar = malloc(sizeof(char) * wordSize);

    int i = 0, j = 0, k = 0;

    //open file
    fileIn = fopen(fileName, "r");
    //if nothing in file you did it wrong 
    if (fileIn == NULL)
    {
        printf("ERROR! Unable to open the file.\n");
        return;
    }

    printf("\n");

    //game loop
    while (charVal != EOF)
    {
        //check word size
        if (wordSize - i == 1)
        {
            inputChar[i] = '\0';
            printf("%s", inputChar);
            checkSum(checkSize, inputChar, checksum);

            j++;
            i = 0;

            if (j * (wordSize - 1) == 80)
            {
                printf("\n");
            }
        }
        //do more 
        else
        {
            charVal = fgetc(fileIn);
            //if end of file
            if (charVal == EOF)
            {
                //if the size is 16 or 32
                if (checkSize == 16 || checkSize == 32)
                {
                    if (wordSize - i != 1 && wordSize - i != wordSize)
                    {
                        k = 0;
                        //pass through X
                        while (wordSize - i != 1 && wordSize - i != wordSize)
                        {
                            inputChar[i] = 'X';
                            i++;
                            k++;
                        }

                        //set null
                        inputChar[i] = '\0';

                        printf("%s", inputChar);
                        checkSum(checkSize, inputChar, checksum);

                        j++;
                        charCount += k;
                        i = 0;

                        if (j * (wordSize - 1) == 80)
                        {
                            printf("\n");
                        }
                    }

                    else
                    {
                        break;
                    }
                }

                else
                {
                break;
                }
            }

            else
            {
            inputChar[i] = charVal;
            charCount++;
            i++;
            }
        }
    }
    //print work
    fclose(fileIn);
    printf("\n");
    printf("%2d bit checksum is %8lx for all %4d chars\n", checkSize, *checksum, charCount);
}

//======================================================================================================================================================================================================

void checkSum(int checkSize, char *inString, unsigned int long *checksum)
{
    unsigned int long maskBit;

    maskBit = bitMask(inString, checkSize);

    *checksum = maskBit + *checksum;
    *checksum = *checksum << (64 - checkSize);
    *checksum = *checksum >> (64 - checkSize);
}

unsigned int long bitMask(char *inString, int checkSize)
{
    int i = 0;

    unsigned int long maskedBits;

    maskedBits = inString[i];
    checkSize -= 8;

    while (checkSize != 0)
    {
        maskedBits = (maskedBits << 8) + inString[i + 1];
        checkSize -= 8;
        i++;
    }

    return maskedBits;
}

/*=============================================================================
| I Dylan Money DY383308 affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+============================================================================*/