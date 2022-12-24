#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

void main()
{
    FILE *inputPointer = NULL;
    FILE *MOTPointer = NULL;
    FILE *OUTPUTPointer = NULL;
    char codeline[50], *inputresult, *word, MOTline[50], *motresult, *motword;
    inputPointer = fopen("./files/INPUT.txt", "r");
    inputresult = fgets(codeline, 100, inputPointer);

    while (inputresult != NULL)
    {
        printf("%s", codeline);
        word = strtok(codeline, " ");

        if (word != NULL)
        {
            // printf("%s",word);

            MOTPointer = fopen("./files/MOT.txt", "r");
            motresult = fgets(MOTline, 50, MOTPointer);

            if (motresult != NULL)
            {
                motword = strtok(MOTline, " ");

                if (motword != NULL)
                {
                    if (strcmp(word, motword) == 0)
                    {
                        printf("\nThe LINE CONTAINS Mnemonics\n");
                    }
                    else
                    {
                        printf("\nThe LINE not CONTAINS Mnemonics\n");
                    }
                }
            }
            else
            {
            }
        }
        inputresult = fgets(codeline, 100, inputPointer);
    }

    fclose(inputPointer);
    fclose(MOTPointer);
    fclose(OUTPUTPointer);
    free(inputresult);
    free(word);
    free(motresult);
    free(motword);
}