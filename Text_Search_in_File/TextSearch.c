#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    // system("cls");
    FILE *FilePointer = NULL;
    char String[200], Character, *result, tempChar[50] = "hello";
    // FilePointer=fopen("./Files/main.txt","a");
    FilePointer = fopen("./Files/main.txt", "r");
    // printf("\nEnter The text To be inserted : ");
    // gets(String);
    // // scanf("%s",&String);
    // printf("\n %s",String);
    // fputs(String,FilePointer);
    // fputs("\n",FilePointer);
    // Character=fgetc(FilePointer);
    // while (Character!=-1)
    // {
    //     putchar(Character);
    //     Character=fgetc(FilePointer);
    // }

    // printf("\nCharacter Readed from File : %c",Character);

    result = fgets(String, 1000, FilePointer);
    int linecount = 0;
    while (result != NULL)
    {
        linecount++;
        // printf("\nline Number is : %d", linecount);
        printf("\nText From File : %s", String);
        // putchar(String[4]);
        // printf("\nLength of Line : %d", strlen(String));
        if (strlen(String) >= strlen(tempChar))
        {
            // printf("\nto be chacked for word in line\n");
            short int not_found = 0;
            short int checkatstart = 0;
            for (int i = 0; i < strlen(String) - strlen(tempChar) + 1; i++)
            {
                int match = 1;
                int j = 0;
                for (j = 0; j < strlen(tempChar) - 1; j++)
                {
                    if (String[i + j] != tempChar[j])
                    {
                        break;
                    }

                    match = match + 1;
                }
                // printf("\nmatch length : %d", match);
                if (match == strlen(tempChar))
                {
                    int lastpositionchecked = 0;
                    // printf("\nlast index position : %d", (i + j + 1));
                    if ((i + j + 1) == strlen(String) || String[i + j + 1] == '\n')
                    {
                        // printf("\nIt is the last string");
                        lastpositionchecked = 1;
                    }
                    else
                    {
                        // printf("\nIt is not at last string");
                        if (String[i + j + 1] == ' ')
                        {
                            lastpositionchecked = 1;
                        }
                    }
                    if (lastpositionchecked == 1)
                    {
                        if (checkatstart == 0)
                        {
                            // printf("\nIt is the start string");
                            not_found = 1;
                            printf("\nPattern Found at index = %d", i);
                        }
                        else
                        {
                            // printf("\nIt is the not start string");
                            if (String[i - 1] == ' ')
                            {
                                not_found = 1;
                                printf("\nPattern Found at index = %d", i);
                            }
                        }
                    }
                }
                checkatstart = 1;
            }
            if (not_found == 0)
            {
                printf("\nmatch not found");
            }
        }
        else
        {
            // printf("\nno need to be chacked for word in line\n");
        }

        result = fgets(String, 1000, FilePointer);
        printf("\n\n\n");
    }

    // printf("\nText From File :  %s", String);
    // fgets(String, 1000, FilePointer);
    // printf("\nText From File :  %s", String);
    // fgets(String, 1000, FilePointer);
    // printf("\nText From File :  %s", String);
    // fgets(String, 1000, FilePointer);
    // printf("\nText From File :  %s", String);

    fclose(FilePointer);
    getch();
}