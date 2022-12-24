#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    FILE *INPUTFILEPointer = NULL;
    FILE *OUTPUTFILEPointer = NULL;
    char *result, *word, codeline[100], operator, * variable_1, *variable_2, *variable_3;
    INPUTFILEPointer = fopen("./Files/INPUT.txt", "r");
    OUTPUTFILEPointer = fopen("./Files/OUTPUT.txt", "w");
    result = fgets(codeline, 100, INPUTFILEPointer);

    while (result != NULL)
    {
        word = strtok(codeline, " ");
        variable_1 = strtok(NULL, " ");
        variable_2 = strtok(NULL, " ");
        if (strcmp(word, "=") == 0)
        {
            if (variable_2[strlen(variable_2) - 1] == '\n')
            {
                variable_2[strlen(variable_2) - 1] = '\0';
            }
            fputs("MOV ", OUTPUTFILEPointer);
            fputs(variable_2, OUTPUTFILEPointer);
            fputs(",", OUTPUTFILEPointer);
            fputs(variable_1, OUTPUTFILEPointer);
            fputs("\n", OUTPUTFILEPointer);
        }
        else
        {
            variable_3 = strtok(NULL, " ");
            if (variable_3[strlen(variable_3) - 1] == '\n')
            {
                variable_3[strlen(variable_3) - 1] = '\0';
            }
            fputs("MOV AX,", OUTPUTFILEPointer);
            fputs(variable_1, OUTPUTFILEPointer);
            fputs("\n", OUTPUTFILEPointer);
            if (strcmp(word, "+") == 0)
            {
                fputs("ADD AX,", OUTPUTFILEPointer);
                fputs(variable_2, OUTPUTFILEPointer);
            }
            else if (strcmp(word, "-") == 0)
            {
                fputs("SUB AX,", OUTPUTFILEPointer);
                fputs(variable_2, OUTPUTFILEPointer);
            }
            else if (strcmp(word, "*") == 0)
            {
                fputs("MUL AX,", OUTPUTFILEPointer);
                fputs(variable_2, OUTPUTFILEPointer);
            }
            else if (strcmp(word, "/") == 0)
            {
                fputs("DIV AX,", OUTPUTFILEPointer);
                fputs(variable_2, OUTPUTFILEPointer);
            }
            fputs("\n", OUTPUTFILEPointer);
            fputs("MOV ", OUTPUTFILEPointer);
            fputs(variable_3, OUTPUTFILEPointer);
            fputs(",AX", OUTPUTFILEPointer);
            fputs("\n\n", OUTPUTFILEPointer);
        }
        result = fgets(codeline, 100, INPUTFILEPointer);
    }
    printf("\nDONE, CODE IS GENERATED\n");
    free(result);
    fclose(INPUTFILEPointer);
    fclose(OUTPUTFILEPointer);
}