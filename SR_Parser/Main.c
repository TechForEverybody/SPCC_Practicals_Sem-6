#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10
void main()
{
    char grammer[MAX][MAX], stack[MAX], temp_stack[MAX];
    char input_string[MAX];
    // char string_to_be_checked[MAX];
    int number_of_grammer, STACK_TOP = -1, index;
    int started=0;
    printf("Enter Number Of Productions in Grammer : ");
    scanf("%d", &number_of_grammer);

    for (int i = 0; i < number_of_grammer; i++)
    {
        printf("Enter Production %d : ", i + 1);
        scanf("%s", &grammer[i]);
    }
    printf("\nEnter Your String : ");
    scanf("%s", &input_string);

    printf("\nSize of input string is %d", strlen(input_string));
    printf("\nYour Productions are : \n");
    for (int i = 0; i < number_of_grammer; i++)
    {
        printf("Production %d --> %s\n", i + 1, grammer[i]);
    }

    printf("\n\nSTACK ");
    for (int y = 0; y <= strlen(input_string); y++)
    {
        if (y > 3)
        {
            printf("  ");
        }
    }
    printf("\t");
    printf(" INPUT ");
    for (int z = 0; z <= strlen(input_string); z++)
    {
        if (z > 3)
        {
            printf("  ");
        }
    }
    printf("\t");
    printf(" ACTION\n");
    printf("$");
    for (int y = 0; y <= strlen(input_string); y++)
    {
        if (y > 0)
        {
            printf("  ");
        }
    }
    printf("\t");
    // printf(" ");
    for (int z = 0; z < strlen(input_string); z++)
    {
        printf("%2c", input_string[z]);
    }
    printf(" $\n");

    for (int i = 0; i < strlen(input_string); i++)
    {
        stack[++STACK_TOP] = input_string[i];
    check_again:
        // printf("\nStack is : %s length : %d and stack top : %d\n", stack, strlen(stack), STACK_TOP);
        // printf("\nStack is : ");
        printf("$");
        for (int y = 0; y < strlen(input_string); y++)
        {
            if (y <= STACK_TOP)
            {
                printf("%2c", stack[y]);
            }
            else
            {
                printf("  ");
            }
            
        }
        printf("\t");
        for (int z = 0; z <= strlen(input_string); z++)
        {
            if (z > i)
            {

                printf("%2c", input_string[z]);
            }
            else
            {

                printf("  ");
            }
        }
        printf("$");
        strcpy(temp_stack, stack);
        // printf("\ntemp Stack is : %s length : %d and stact top : %d\n", temp_stack, strlen(temp_stack), STACK_TOP);
        for (int j = STACK_TOP; j >= 0; j--)
        {
            char string_to_be_checked[MAX];
            index = 0;
            for (int k = j; k <= STACK_TOP; k++)
            {

                string_to_be_checked[index++] = temp_stack[k];
            }
            for (int m = 0; m < number_of_grammer; m++)
            {
                if (strcmp(string_to_be_checked, grammer[m]) == 0)
                {
                    // printf("\nMatched in Production\n");
                    int len_to_be_reduced = strlen(string_to_be_checked);
                    // printf("\nString to be checked is : %s with length : %d and index position is  : %d\n", string_to_be_checked, strlen(string_to_be_checked), index);
                    // printf("\nTop: %d and length to be reduced : %d\n", STACK_TOP, len_to_be_reduced);
                    int pre_position = STACK_TOP;
                    STACK_TOP = STACK_TOP - (len_to_be_reduced - 1);
                    for (int x = STACK_TOP + 1; x <= strlen(temp_stack); x++)
                    {
                        stack[x] = '\0';
                    }
                    stack[STACK_TOP] = 'E';
                    // printf("\n%s\n", stack);

                    printf("\t Reduce %s using E -> %s\n", string_to_be_checked, grammer[m]);
                    for (int l = 0; l < index; l++)
                    {
                        string_to_be_checked[l] = '\0';
                    }

                    // printf("\n");
                    goto check_again;
                    // exit(1);
                }
            }

            for (int l = 0; l < index; l++)
            {
                string_to_be_checked[l] = '\0';
            }
        }
        printf("\t Shift %c\n", input_string[i]);
    }

    printf("\nFinal Stack Content : ");
    for (int y = 0; y <= STACK_TOP; y++)
    {
        printf("%c", stack[y]);
    }
    printf("\n");
    if (STACK_TOP == 0 && stack[STACK_TOP] == 'E')
    {
        printf("\n STRING IS ACCEPTED");
    }
    else
    {
        printf("\n STRING IS REJECTED");
    }
}