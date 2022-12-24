#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define MAX_KEYWORDS 11

char keywords[MAX_KEYWORDS][50] = {
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
    "include",
};

void main()
{
    FILE *FilePointer = NULL;
    FilePointer = fopen("./Files/input.c", "r");
    char *result, codeline[100];
    static char comparing_string[20];
    int counter = 0;
    result = fgets(codeline, 100, FilePointer);
    while (result != NULL)
    {
        // printf("\n%s", codeline);
        for (int i = 0; i < strlen(codeline); i++)
        {
            // printf("\n%c",codeline[i]);
            if (codeline[i] == '\0' || codeline[i] == '\n' || codeline[i] == ' ')
            {
                continue;
            }

            if (isdigit(codeline[i]))
            {
                // printf("\nit is an digit\n");
                counter = 0;
                comparing_string[counter++] = codeline[i];
                for (int j = 0; j < strlen(codeline); j++)
                {
                    if (isdigit(codeline[i + 1]))
                    {
                        i++;
                        comparing_string[counter++] = codeline[i];
                    }
                    else
                    {
                        break;
                    }
                }
                printf("\n%s\t --> Literal", comparing_string);
                for (int l = 0; l < counter; l++)
                {
                    comparing_string[l] = '\0';
                }
            }
            else if (isalnum(codeline[i]))
            {
                // printf("\nit is an word\n");
                counter = 0;
                comparing_string[counter++] = codeline[i];
                for (int j = 0; j < strlen(codeline); j++)
                {
                    if (isalnum(codeline[i + 1]) != 0 || codeline[i + 1] == '.')
                    {
                        i++;
                        comparing_string[counter++] = codeline[i];
                    }
                    else
                    {
                        break;
                    }
                }
                int isfound = 0;
                for (int m = 0; m < MAX_KEYWORDS; m++)
                {
                    // printf("\ncomparision of %s and %s is %d\n",keywords[m],comparing_string,strcmp(keywords[i], comparing_string));
                    if (strcmp(keywords[m], comparing_string) == 0)
                    {
                        isfound = 1;
                        break;
                    }
                }
                if (isfound == 1)
                {
                    printf("\n%s\t --> Keyword", comparing_string);
                }
                else
                {
                    printf("\n%s\t --> Identifier", comparing_string);
                }
                for (int l = 0; l < counter; l++)
                {
                    comparing_string[l] = '\0';
                }
            }
            else
            {
                printf("\n%c\t --> terminal", codeline[i]);
            }
        }

        result = fgets(codeline, 100, FilePointer);
    }
    free(result);
    fclose(FilePointer);
}