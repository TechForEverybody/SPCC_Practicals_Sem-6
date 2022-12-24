#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
char terminals[][50]={
    "=",
    "{",
    "}",
    ">",
    "<",
    "!",
    "(",
    ")"
    };

char keyword[][50]={
    "void",
    "int",
    "float",
    "char",
    "include",
    "while",
    "if",
    "else",
    "switch",
    "void",
};



void main()
{
    // printf("\nResult -> %d\n",(isalnum('+')));
    printf("\nResult %s -> %d\n",terminals[0],(isdigit('8')));
}