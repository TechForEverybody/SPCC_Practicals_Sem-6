#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

void main()
{
    char string[10]="2000";
    char value[10]="2";
    int intValue=atoi(value);
    int instruction=atoi(string);
    printf("\nint value = %d\n",intValue);
    printf("\ninstruction value = %d\n",instruction);
    int result=instruction+intValue;
    printf("\ninstruction incremented = %d\n",result);
    char string_instruction[10];
    // string_instruction=atoa(result);
    sprintf(string_instruction,"%d",result);
    printf("\nstring instruction values : %s\n",string_instruction);
}