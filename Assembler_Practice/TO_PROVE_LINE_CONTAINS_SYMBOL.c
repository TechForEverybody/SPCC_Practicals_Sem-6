#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>





/*




*/



void main()
{
    FILE *inputPointer = NULL;
    FILE *MOTPointer = NULL;
    FILE *POTPointer = NULL;
    FILE *OUTPUTPointer = NULL;
    char codeline[50], *inputresult, *word, MOTline[50], *motresult, *motword,*potresult,*potword,POTline[50];
    inputPointer = fopen("./files/INPUT.txt", "r");
    inputresult = fgets(codeline, 100, inputPointer);
    int isSymbol=0;
    
    while (inputresult != NULL)
    {
        printf("%s", codeline);
        word = strtok(codeline, " ");
        word = strtok(NULL, " ");
        // word = strtok(NULL, " ");
        
        if (word != NULL)
        {
            isSymbol=0;
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
                        isSymbol=1;
                    }
                    else
                    {
                        // printf("\nThe LINE not CONTAINS Mnemonics\n");
                    }
                }
            }
            POTPointer = fopen("./files/POT.txt", "r");
            potresult = fgets(POTline, 50, POTPointer);
            if (potresult != NULL)
            {
                potword = strtok(POTline, " ");
                if (potword != NULL)
                {
                    if (strcmp(word, potword) == 0)
                    {
                        printf("\nThe LINE CONTAINS psudoopcode\n");
                        isSymbol=1;
                    }
                    else
                    {
                        // printf("\nThe LINE not CONTAINS Mnemonics\n");
                    }
                }
            }




            if (isSymbol==0)
            {
                printf("\nIT IS A SYMBOL\n");
                OUTPUTPointer=fopen("./files/OUTPUT.txt","w");
                fputs(word,OUTPUTPointer);
                fputs(" VAR ",OUTPUTPointer);
                fputs("____",OUTPUTPointer);
                fclose(OUTPUTPointer);

            }
            else
            {
                printf("\nIT IS NOT A SYMBOL\n");
            }
            
        }
        inputresult = fgets(codeline, 100, inputPointer);
    }

    fclose(inputPointer);
    fclose(MOTPointer);
    fclose(POTPointer);
    fclose(OUTPUTPointer);
    free(inputresult);
    free(word);
    free(motresult);
    free(motword);
    free(potresult);
    free(potword);
}