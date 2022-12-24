#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void main()
{
    FILE *ALPPointer = NULL;
    FILE *MNTPointer = NULL;
    FILE *MDTPointer = NULL;
    FILE *OUTPUTPointer = NULL;
    FILE *FINALOUTPUTPointer = NULL;
    char *result, *mntresult, *mdtresult, codeline[100], current_macro_name[50], current_macro_call[50], MNTcodeline[100], MDTcodeline[100], string[100];
    static char *ALPword, *MNTword, *MDTword;
    int mdt_index_value = 0;
    char string_index[10];

    // fputs(codeline,MDTPointer);
    // fputs(codeline,OUTPUTPointer);
    // exit(1);
    int pass_number = 1;
    switch (pass_number)
    {
    case 1:
        OUTPUTPointer = fopen("./Files/OUTPUT.txt", "w");
        MNTPointer = fopen("./Files/MNT.txt", "w");
        MDTPointer = fopen("./Files/MDT.txt", "w");
        ALPPointer = fopen("./Files/ALP.txt", "r");
        result = fgets(codeline, 100, ALPPointer);
        while (result != NULL)
        {
            // printf("\n%s", codeline);
            // printf("\nlength of Line : %d\n", strlen(codeline));
            int is_macro_encountered = 0;
            strcpy(string, codeline);
            ALPword = strtok(codeline, " ");

            // while (ALPword != NULL)
            // {
            //     printf("\ncomparision of macro : %d\n", strcmp(ALPword, "MACRO"));
            if (strcmp(ALPword, "MACRO") == 0)
            {
                is_macro_encountered = 1;
                ALPword = strtok(NULL, " ");
                // strcpy(current_macro_name, ALPword);
                char newline_removed_string[50];
                strcpy(newline_removed_string, ALPword);
                if (newline_removed_string[strlen(newline_removed_string) - 1] == '\n')
                {
                    newline_removed_string[strlen(newline_removed_string) - 1] = '\0';
                }
                // strcpy(current_macro_name,ALPword);
                printf("\n%s", newline_removed_string);
                fputs(newline_removed_string, MNTPointer);
                fputs(" 0 ", MNTPointer);
                sprintf(string_index, "%d", ++mdt_index_value);
                fputs(string_index, MNTPointer);
                fputs("#\n", MNTPointer);
            }
            // }
            if (is_macro_encountered == 1)
            {
                fputs(string_index, MDTPointer);
                fputs("#\n", MDTPointer);
                ALPword = strtok(codeline, " ");
                while (strcmp(ALPword, "MEND\n") != 0)
                {
                    result = fgets(codeline, 100, ALPPointer);
                    fputs(codeline, MDTPointer);
                    printf("\n%s", codeline);
                    ALPword = strtok(codeline, " ");
                    if (strcmp(ALPword, "END") == 0 || strcmp(ALPword, "END\n") == 0)
                    {
                        printf("\nERROR: MEND NOT FOUND\n");
                        goto clean_up;
                    }
                }
            }
            else
            {
                // printf("\n%s", string);
                fputs(string, OUTPUTPointer);
            }
            // exit(1);
            result = fgets(codeline, 100, ALPPointer);
        }
        break;
    case 2:
        // printf("\nhello1\n");
        FINALOUTPUTPointer = fopen("./Files/FINALOUTPUT.txt", "w");
        OUTPUTPointer = fopen("./Files/OUTPUT.txt", "r");
        MDTPointer = fopen("./Files/MDT.txt", "r");
        result = fgets(codeline, 100, OUTPUTPointer);

        while (result != NULL)
        {
            // printf("\nhello1\n");
            strcpy(string, codeline);

            int is_macro_call_encountered = 0;
            // printf("\n%s", codeline);
            ALPword = strtok(codeline, " ");
            MNTPointer = fopen("./Files/MNT.txt", "r");
            mntresult = fgets(MNTcodeline, 100, MNTPointer);
            while (mntresult != NULL)
            {
                // printf("\n%s", MNTcodeline);
                mntresult = fgets(MNTcodeline, 100, MNTPointer);
                MNTword = strtok(MNTcodeline, " ");
                char newline_removed_string[50];
                strcpy(newline_removed_string, ALPword);
                if (newline_removed_string[strlen(newline_removed_string) - 1] == '\n')
                {
                    newline_removed_string[strlen(newline_removed_string) - 1] = '\0';
                }
                // strcpy(current_macro_name,ALPword);
                // printf("\n%s", newline_removed_string);
                if (strcmp(MNTword, newline_removed_string) == 0)
                {
                    MNTword = strtok(NULL, " ");
                    MNTword = strtok(NULL, " ");
                    strcpy(string_index, MNTword);
                    printf("\nMacro Call found\n");
                    is_macro_call_encountered = 1;
                    strcpy(current_macro_call, MNTword);
                    break;
                }
            }
            fclose(MNTPointer);
            if (is_macro_call_encountered == 1)
            {
                if (string_index[strlen(string_index) - 1] == '\n')
                {
                    string_index[strlen(string_index) - 1] = '\0';
                }
                printf("\nMDT index is : %s and its length is : %d\n", string_index, strlen(string_index));
                MDTPointer = fopen("./Files/MDT.txt", "r");
                mdtresult = fgets(MDTcodeline, 100, MDTPointer);
                while (mdtresult != NULL)
                {
                    char temp_string[50];
                    printf("\n%s", MDTcodeline);
                    MDTword = strtok(MDTcodeline, " ");
                    strcpy(temp_string, MDTword);
                    if (temp_string[strlen(temp_string) - 1] == '\n')
                    {
                        temp_string[strlen(temp_string) - 1] = '\0';
                    }
                    if (strcmp(string_index, temp_string) == 0)
                    {
                        printf("\nDefinition found\n");
                            mdtresult = fgets(MDTcodeline, 100, MDTPointer);
                        while (strcmp(MDTcodeline, "MEND")!=0 && strcmp(MDTcodeline, "MEND\n")!=0)
                        {
                            fputs(MDTcodeline, FINALOUTPUTPointer);
                            printf("\n%s", MDTcodeline);
                            mdtresult = fgets(MDTcodeline, 100, MDTPointer);
                        }
                    }

                    mdtresult = fgets(MDTcodeline, 100, MDTPointer);
                }
            }
            else
            {
                fputs(string, FINALOUTPUTPointer);
            }
            result = fgets(codeline, 100, OUTPUTPointer);
        }
        break;

    default:
        break;
    }

clean_up:
    fclose(ALPPointer);
    fclose(MDTPointer);
    fclose(MNTPointer);
    fclose(OUTPUTPointer);
    fclose(OUTPUTPointer);
    fclose(FINALOUTPUTPointer);
    free(result);
    free(mdtresult);
    free(mntresult);
    free(ALPword);
    free(MNTword);
    free(MDTword);
}