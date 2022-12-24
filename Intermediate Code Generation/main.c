#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void main()
{
    // trial input = a-b*c/d+e*k+x
    static char operating_string[20];
    printf("\nEnter Your Expression W = ");
    scanf("%s", &operating_string);
    strcpy(operating_string, operating_string);
    static int number_of_operators = 0;
    static char opertor_precedence[10];
    static char sorted_opertor_precedence[10];
    static char current_character = 65;
    static int counter = 0;
    for (int i = 0; i < strlen(operating_string); i++)
    {
        if (isalnum(operating_string[i]))
        {
            continue;
        }
        else
        {
            opertor_precedence[counter++] = operating_string[i];
            number_of_operators++;
        }
    }
    counter = 0;
    for (int j = 0; j < number_of_operators; j++)
    {
        if (opertor_precedence[j] == '/')
        {
            sorted_opertor_precedence[counter++] = opertor_precedence[j];
        }
    }
    for (int j = 0; j < number_of_operators; j++)
    {
        if (opertor_precedence[j] == '*')
        {
            sorted_opertor_precedence[counter++] = opertor_precedence[j];
        }
    }
    for (int j = 0; j < number_of_operators; j++)
    {
        if (opertor_precedence[j] == '+')
        {
            sorted_opertor_precedence[counter++] = opertor_precedence[j];
        }
    }
    for (int j = 0; j < number_of_operators; j++)
    {
        if (opertor_precedence[j] == '-')
        {
            sorted_opertor_precedence[counter++] = opertor_precedence[j];
        }
    }
    printf("\ninput string : %s\n", operating_string);
    printf("\nnumber of operators in Expression : %d\n", number_of_operators);
    printf("\nsorted Opearators by precedence : %s\n", sorted_opertor_precedence);
    static char temporary_string[20];
    printf("\nOpearating Expression\t\t Intermediate Code");
    for (int i = 0; i < number_of_operators; i++)
    {
        printf("\n%20s\t\t\t", operating_string);
        for (int j = 0; j < strlen(operating_string); j++)
        {
            if (sorted_opertor_precedence[i] == operating_string[j])
            {
                printf("%c = %c%c%c\t", current_character++, operating_string[j - 1], operating_string[j], operating_string[j + 1]);
                counter = 0;
                for (int k = 0; k < j - 1; k++)
                {
                    operating_string[counter++] = operating_string[k];
                }
                operating_string[counter++] = current_character - 1;
                for (int k = j + 2; k < strlen(operating_string); k++)
                {
                    operating_string[counter++] = operating_string[k];
                }
                strcpy(operating_string, operating_string);
                for (int l = counter; l < strlen(operating_string); l++)
                {
                    operating_string[l] = '\0';
                }
                break;
            }
        }
    }
    printf("\n%20c\t\t\t", current_character - 1);
    printf("W = %c\n\n", current_character - 1);
}