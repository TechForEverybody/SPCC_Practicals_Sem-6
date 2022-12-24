#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// struct ALPLine
// {
//     char word1[50];
//     char word2[50];
//     char word3[50];
//     char word4[50];
// };

struct MOTLine
{
    char mneumonics[10];
    char op_code[10];
    char no_of_operands[10];
    char length_of_instruction[10];
};

struct POTLine
{
    char psudo_op_code[10];
    char no_of_operands[10];
};

struct STLine
{
    char symbol_name[10];
    char type[10];
    char definition_address[10];
};

struct traversing_array
{
    char word[50];
    struct traversing_array *next;
};
struct traversing_array *head = NULL;

void insert_in_link_list(char word[])
{
    struct traversing_array *ptr = NULL;
    ptr = (struct traversing_array *)malloc(sizeof(struct traversing_array));
    ptr->next = NULL;
    strcpy(ptr->word, word);
    if (head == NULL)
    {
        head = ptr;
    }
    else
    {
        struct traversing_array *node = NULL;
        node = head;
        while (node->next != NULL)
        {
            node = node->next;
        }
        node->next = ptr;
    }
}
void delete_link_list()
{
    struct traversing_array *node = NULL;
    while (head != NULL)
    {
        node = head;
        free(node);
        head = head->next;
    }
}

void main()
{
    FILE *ALPPointer = NULL;
    FILE *MOTPointer = NULL;
    FILE *POTPointer = NULL;
    FILE *STPointer = NULL;
    FILE *LTPointer = NULL;
    FILE *IMCPointer = NULL;
    FILE *FMCPointer = NULL;
    FILE *TEMPPointer = NULL;
    char *result, *motresult, *potresult, *stresult, codeline[100], MOTcodeline[100], POTcodeline[100], STcodeline[100], toBeSearchedALPword[50];
    char tempString[50];
    // char *ALP_word_array[10];
    int word_count = 0;
    static char *ALPword, *MOTword, *POTword, *STword;
    int not_match_counter = 0;
    char is_started = 0;
    int line_number = 0, is_data_section_activated = 0;
    static char instruction_address[10] = "0000";
    // STPointer = fopen("./Files/ST.txt", "w");
    // fclose(STPointer);
    IMCPointer = fopen("./Files/IMC.txt", "w");
    ALPPointer = fopen("./Files/ALP.txt", "r");
    result = fgets(codeline, 100, ALPPointer);
    while (result != NULL)
    {
        // printf("\nlength of Line : %d\n", strlen(codeline));

        ALPword = strtok(codeline, " ");
        // struct ALPLine new_alp_line;
        // strcpy(new_alp_line.word1, " ");
        // strcpy(new_alp_line.word2, " ");
        // strcpy(new_alp_line.word3, " ");
        // strcpy(new_alp_line.word4, " ");
        int counter = 0;
        while (ALPword != NULL)
        {
            strcpy(tempString, strupr(ALPword));
            if (tempString[strlen(tempString) - 1] == '\n')
            {
                // printf("\n Ends with newline character \n");
                tempString[strlen(tempString) - 1] = '\0';
            }
            insert_in_link_list(tempString);
            // strcpy(ALP_word_array[counter], tempString);
            // if (counter == 0)
            // {
            //     strcpy(new_alp_line.word1, strupr(tempString));
            //     // printf("\nString : %s and length : %d", new_alp_line.word1, strlen(new_alp_line.word1));
            //     // printf("\nlast character : %s and length of string : %d", tempString, strlen(tempString));
            // }
            // else if (counter == 1)
            // {
            //     strcpy(new_alp_line.word2, strupr(tempString));
            // }
            // else if (counter == 2)
            // {
            //     strcpy(new_alp_line.word3, strupr(tempString));
            // }
            // else if (counter == 3)
            // {
            //     strcpy(new_alp_line.word4, strupr(tempString));
            // }
            // else
            // {
            //     printf("\nERROR PLEASE ADD NEW INSTRUCTION ON NEW LINE\n");
            //     exit(0);
            // }
            // printf("%s ", tempString);
            ALPword = strtok(NULL, " ");
            counter++;
        }
        printf("\n");
        struct traversing_array *node = NULL;
        node = head;
        while (node != NULL)
        {
            int matchwith_mot_table = 0;
            int matchwith_pot_table = 0;
            int matchwith_st_table = 0;
            // printf("%s ", node->word);
            if (strcmp(node->word, "START") == 0)
            {
                if (is_started == 0 && line_number == 0)
                {
                    printf("\n--------- Started --------\n");
                    is_started = 1;
                    if (node->next == NULL)
                    {
                        // fputs(instruction_address, IMCPointer);
                    }
                    else
                    {
                        // fputs(node->next->word, IMCPointer);
                        strcpy(instruction_address, node->next->word);
                    }

                    break;
                }
                else
                {
                    printf("\nERROR: AGAIN START STATEMENT IS OCCURED\n");
                    goto clean_up;
                }
            }
            else
            {
                if (line_number == 0)
                {
                    printf("\nERROR: FIRST STATEMENT MUST BE START\n");
                    goto clean_up;
                }
            }
            // for (int i = 0; i < counter-1; i++)
            // {
            // }

            // printf("%s -> %d\n", new_alp_line.word1, strlen(new_alp_line.word1));
            // printf("%s -> %d\n", new_alp_line.word2, strlen(new_alp_line.word2));
            // printf("%s -> %d\n", new_alp_line.word3, strlen(new_alp_line.word3));
            // printf("%s -> %d\n", new_alp_line.word4, strlen(new_alp_line.word4));
            fputs(" ", IMCPointer);
            MOTPointer = fopen("./Files/MOT.txt", "r");
            motresult = fgets(MOTcodeline, 100, MOTPointer);
            while (motresult != NULL)
            {
                // printf("\nlength of Line : %d\n", strlen(codeline));
                MOTword = strtok(MOTcodeline, " ");
                struct MOTLine new_mot_line;
                int counter = 0;
                while (MOTword != NULL)
                {
                    if (counter == 0)
                    {
                        strcpy(new_mot_line.mneumonics, strupr(MOTword));
                    }
                    else if (counter == 1)
                    {
                        strcpy(new_mot_line.op_code, MOTword);
                    }
                    else if (counter == 2)
                    {
                        strcpy(new_mot_line.no_of_operands, MOTword);
                    }
                    else if (counter == 3)
                    {
                        char newline_removed_string[50];
                        strcpy(newline_removed_string, MOTword);
                        if (newline_removed_string[strlen(newline_removed_string) - 1] == '\n')
                        {
                            newline_removed_string[strlen(newline_removed_string) - 1] = '\0';
                        }

                        strcpy(new_mot_line.length_of_instruction, newline_removed_string);
                    }
                    else
                    {
                        printf("\nERROR PLEASE ADD NEW INSTRUCTION ON NEW LINE\n");
                        goto clean_up;
                    }
                    // printf("%s ", MOTword);
                    MOTword = strtok(NULL, " ");
                    counter++;
                }
                motresult = fgets(MOTcodeline, 100, MOTPointer);

                if (strcmp(node->word, new_mot_line.mneumonics) == 0)
                {
                    // printf("\nMatched with MOT table : %s\n", node->word);
                    fputs(new_mot_line.op_code, IMCPointer);
                    matchwith_mot_table = 1;
                }
            }
            fclose(MOTPointer);
            POTPointer = fopen("./Files/POT.txt", "r");
            potresult = fgets(POTcodeline, 100, POTPointer);
            while (potresult != NULL)
            {
                // printf("\nlength of Line : %d\n", strlen(codeline));
                POTword = strtok(POTcodeline, " ");
                struct POTLine new_pot_line;
                int counter = 0;
                while (POTword != NULL)
                {
                    if (counter == 0)
                    {
                        strcpy(new_pot_line.psudo_op_code, strupr(POTword));
                    }
                    else if (counter == 1)
                    {
                        char newline_removed_string[50];
                        strcpy(newline_removed_string, POTword);
                        if (newline_removed_string[strlen(newline_removed_string) - 1] == '\n')
                        {
                            newline_removed_string[strlen(newline_removed_string) - 1] = '\0';
                        }
                        strcpy(new_pot_line.no_of_operands, newline_removed_string);
                    }
                    else
                    {
                        printf("\nERROR PLEASE ADD NEW INSTRUCTION ON NEW LINE\n");
                        goto clean_up;
                    }
                    // printf("%s ", POTword);
                    POTword = strtok(NULL, " ");
                    counter++;
                }
                potresult = fgets(POTcodeline, 100, POTPointer);

                if (strcmp(node->word, new_pot_line.psudo_op_code) == 0)
                {
                    // printf("\nMatched with POT table : %s\n", node->word);
                    // fputs(new_pot_line, IMCPointer);
                    matchwith_pot_table = 1;
                    if (strcmp(node->word, "END") == 0)
                    {
                        goto check_end;
                    }
                    if (strcmp(node->word, "ENDP") == 0)
                    {
                        is_data_section_activated = 1;
                    }
                }
            }
            fclose(POTPointer);
            STPointer = fopen("./Files/ST.txt", "r");
            stresult = fgets(STcodeline, 100, STPointer);
            while (stresult != NULL)
            {
                // printf("\nlength of Line : %d\n", strlen(codeline));
                // printf("%s ", STcodeline);

                STword = strtok(STcodeline, " ");
                struct STLine new_st_line;
                int counter = 0;
                while (STword != NULL)
                {
                    if (counter == 0)
                    {
                        strcpy(new_st_line.symbol_name, strupr(STword));
                    }
                    else if (counter == 1)
                    {
                        strcpy(new_st_line.type, STword);
                    }
                    else if (counter == 2)
                    {
                        char newline_removed_string[50];
                        strcpy(newline_removed_string, STword);
                        if (newline_removed_string[strlen(newline_removed_string) - 1] == '\n')
                        {
                            newline_removed_string[strlen(newline_removed_string) - 1] = '\0';
                        }
                        strcpy(new_st_line.definition_address, newline_removed_string);
                    }
                    else
                    {
                        printf("\nERROR PLEASE ADD NEW INSTRUCTION ON NEW LINE\n");
                        goto clean_up;
                    }
                    // printf("%s ", STword);
                    STword = strtok(NULL, " ");
                    counter++;
                }

                stresult = fgets(STcodeline, 100, STPointer);
                char colon_removed_string[50];
                strcpy(colon_removed_string, node->word);
                if (node->word[strlen(node->word) - 1] == ':')
                {
                    colon_removed_string[strlen(colon_removed_string) - 1] = '\0';
                }
                if (strcmp(colon_removed_string, new_st_line.symbol_name) == 0)
                {
                    printf("\nMatched with ST table : %s\n", node->word);
                    matchwith_st_table = 1;
                    // if (is_data_section_activated=1)
                    // {

                    // }
                    // printf("\nMatched LINE : %s    %s    %s\n", new_st_line.symbol_name,new_st_line.type,new_st_line.definition_address);
                    // printf("\ncomparision : %d\n",strcmp(new_st_line.definition_address, "____"));
                    if (strcmp(new_st_line.definition_address, "____") == 0)
                    {
                        printf("\ndefinition address is not found\n");
                    }
                    else
                    {
                        fputs(new_st_line.definition_address, IMCPointer);
                    }
                }
            }
            fclose(STPointer);
            if (matchwith_mot_table != 1 && matchwith_pot_table != 1 && matchwith_st_table != 1)
            {
                // printf("\nNot matched with any table : %s\n", node->word);
                char label_handaling_array[50];
                not_match_counter += 1;
                STPointer = fopen("./Files/ST.txt", "a");
                if (strcmp(node->word, "?") == 0)
                {
                    // continue;
                }
                else
                {
                    if (is_data_section_activated == 1)
                    {

                    }
                    else
                    {
                        if (node->word[strlen(node->word) - 1] == ':')
                        {
                            // printf("\nLABEL OCCURED at line number : %d\n", line_number);
                            strcpy(label_handaling_array, node->word);
                            label_handaling_array[strlen(label_handaling_array) - 1] = '\0';
                            fputs(label_handaling_array, STPointer);
                            fputs(" LABEL ", STPointer);
                            fputs(instruction_address, STPointer);
                        }
                        else
                        {
                            fputs(node->word, STPointer);
                            fputs(" VAR ", STPointer);
                            fputs("____", STPointer);
                        }
                        fputs("\n", STPointer);
                        fclose(STPointer);
                    }
                }
            }

            if (is_data_section_activated == 1)
            {
                if (matchwith_st_table == 1)
                {
                    // printf("\nHERE in the data section\n");
                    // TEMPPointer = fopen("./Files/TempFile.txt", "w");
                    // fclose(TEMPPointer);
                    TEMPPointer = fopen("./Files/TempFile.txt", "w");
                    STPointer = fopen("./Files/ST.txt", "r");
                    stresult = fgets(STcodeline, 100, STPointer);
                    while (stresult != NULL)
                    {
                        // printf("\nlength of Line : %d\n", strlen(codeline));
                        char copying_string[50];
                        // printf("%s ", STcodeline);
                        strcpy(copying_string, STcodeline);
                        STword = strtok(STcodeline, " ");
                        struct STLine new_st_line;
                        int counter = 0;
                        while (STword != NULL)
                        {
                            if (counter == 0)
                            {
                                strcpy(new_st_line.symbol_name, strupr(STword));
                            }
                            else if (counter == 1)
                            {
                                strcpy(new_st_line.type, STword);
                            }
                            else if (counter == 2)
                            {
                                strcpy(new_st_line.definition_address, STword);
                            }
                            else
                            {
                                printf("\nERROR PLEASE ADD NEW INSTRUCTION ON NEW LINE\n");
                                goto clean_up;
                            }
                            // printf("%s ", STword);
                            STword = strtok(NULL, " ");
                            counter++;
                        }
                        if (strcmp(node->word, new_st_line.symbol_name) == 0)
                        {
                            // printf("\nMATCHED LINE : %s \n", STcodeline);

                            fputs(new_st_line.symbol_name, TEMPPointer);
                            fputs(" ", TEMPPointer);
                            fputs(new_st_line.type, TEMPPointer);
                            fputs(" ", TEMPPointer);
                            fputs(instruction_address, TEMPPointer);
                            fputs("\n", TEMPPointer);
                        }
                        else
                        {
                            fputs(copying_string, TEMPPointer);
                            // printf("\nNOT MATCHED LINE : %s \n", copying_string);
                        }
                        // fputs(STcodeline, TEMPPointer);
                        stresult = fgets(STcodeline, 100, STPointer);
                    }
                    fclose(TEMPPointer);
                    fclose(STPointer);
                    STPointer = fopen("./Files/ST.txt", "w");
                    TEMPPointer = fopen("./Files/TempFile.txt", "r");
                    stresult = fgets(STcodeline, 100, TEMPPointer);
                    while (stresult != NULL)
                    {
                        fputs(STcodeline, STPointer);
                        stresult = fgets(STcodeline, 100, TEMPPointer);
                    }
                    fclose(TEMPPointer);
                    fclose(STPointer);
                }
                else
                {
                    if (matchwith_mot_table != 1 && matchwith_pot_table != 1 && matchwith_st_table != 1)
                    {
                        STPointer = fopen("./Files/ST.txt", "a");
                        fputs(node->word, STPointer);
                        fputs(" VAR ", STPointer);
                        fputs(instruction_address, STPointer);
                        fputs("\n", STPointer);
                        fclose(STPointer);
                    }
                    break;
                }
            }

            node = node->next;
        }
        printf("\n");
        free(node);
        delete_link_list();

        result = fgets(codeline, 100, ALPPointer);
        fputs("\n", IMCPointer);
        if (is_started == 1)
        {
            fputs(instruction_address, IMCPointer);
        }
        line_number++;
    }

    printf("\n%d words are not match with any tables\n", not_match_counter);
check_end:
    printf("\nREACHED TO END\n");

clean_up:
    delete_link_list();

    fclose(STPointer);
    fclose(MOTPointer);
    fclose(POTPointer);
    fclose(ALPPointer);
    fclose(IMCPointer);

    free(result);
    free(motresult);
    free(potresult);
    free(stresult);
    free(ALPword);
    free(MOTword);
    free(POTword);
    free(STword);
}