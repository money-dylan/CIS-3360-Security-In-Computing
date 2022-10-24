/*=============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Vigenere cipher
|
| Author: Dylan Money
| Language: c
|
| To Compile: gcc -o pa01 pa01.c
|
| To Execute: c -> ./pa01 kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Fall 2022
| Instructor: McAlpin
| Due Date: 10/ 16/ 22
|
+=============================================================================*/

//include things
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc,char* argv[])
{
  FILE *kptr,*fptr;
  
//vars
  char key[513],plain[513];
  int nextChar;
  
//This is the key

  kptr = fopen(argv[1], "r");
  
  if (kptr == NULL)
  {
    printf("Cannot open key file \n");
    exit(0);
  }
  
  int i=1,j,k=0,y=0;
  nextChar = fgetc(kptr);

//Key------------------------------------------------------------------------------------
  printf("\n");
  printf("\n");
  printf("Vigenere Key:\n");
  printf("\n");
  
//Keep going till file ends
int line = 0;

  while (nextChar != EOF)
  {
    nextChar = tolower(nextChar);
    
    i++;
    
    if(y>512)
    {
      break;
    }

    if(nextChar>='a'&&nextChar<='z')
    {
      printf ("%c", nextChar);
      key[k++]=toupper(nextChar);
      line++;
    }
    if(nextChar>='A'&&nextChar<='Z')
    {
      key[k++]=nextChar;
    }
    
    if(line == 80)
    {
      printf("\n");
      line = 0;
    }
 
      nextChar = fgetc(kptr);

  }
  
  key[k]='\0';
  
  printf("\n");
  
  fclose(kptr);
//open input

  fptr = fopen(argv[2], "r");
  
  if (fptr == NULL)
  {
    printf("Cannot open file \n");
    exit(0);
  }
  
  k=0,i=1,line=0;
  
  nextChar = fgetc(fptr);
  
//Plaintext-----------------------------------------------------------------------------------------------
  printf("\n");
  printf("\n");
  printf("Plaintext:\n");
  printf("\n"); 
  
  
  while (nextChar != EOF)
  { 
    nextChar = tolower(nextChar);
    
    i++;
    
    if(y>512)
    {
      break;
    }

    if(nextChar>='a'&&nextChar<='z')
    {
      printf ("%c", nextChar);
      plain[k++]=toupper(nextChar);
      y++;
      line++;
    }
    if(nextChar>='A'&&nextChar<='Z')
    {
      plain[k++]=nextChar;
    }
    
    if(y == 485)
    { 
      plain[485] = nextChar;
    }
    
    if(line == 80)
    {
      printf("\n");
      line = 0;
    }
    
      nextChar = fgetc(fptr);
  }
  
  
  while(y < 512)
  {
    printf("x");
    plain[k++]='X';
    y++;
    line++;
    if(line == 80)
    {
      printf("\n");
      line = 0;
    }
    
    if(y == 485)
    { 
      plain[485] = 'X';
    }
  }
  
//Cypher--------------------------------------------------------------------------------------------------------
  printf("\n");
  plain[k]='\0';

  fclose(fptr);

//more vars
  int length=strlen(plain),keylen=strlen(key);
  char newkey[length],cypher[length];
    
    length=strlen(plain);

  for(i=0,j=0;i<512;++i, ++j)
  {
//check if restart key
    if(j >= strlen(key))
    {
      j=0;
    }
    cypher[i]=( (plain[i]+key[j])%26)+'A';
    
  
  }
  
  cypher[i]='\0';
  printf("\n");
  printf("\n");
  printf("Ciphertext:\n");
  printf("\n");

//print cypher
  line = 0;
  
  for(i=0;i<=512;i++)
    {
      printf("%c",tolower(cypher[i]));
      
      line++;
      
      if(line == 80)
      {
        printf("\n");
          line = 0;
      }
    }
  printf("\n"); 
  return 0;
}

/*=============================================================================
| I Dylan Money (5216338) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/