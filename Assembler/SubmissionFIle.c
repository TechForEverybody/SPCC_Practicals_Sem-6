#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
static char instruction_address[10] = "0";
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

void update_instruction_address(char string[])
{
    int intValue = atoi(string);
    int instruction = atoi(instruction_address);
    int result = instruction + intValue;
    char string_instruction[10];
    sprintf(string_instruction, "%d", result);
    strcpy(instruction_address, string_instruction);
}

void main()
{
    printf("\nCoded By : Shivkumar Chauhan\n");
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
    int word_count = 0;
    static char *ALPword, *MOTword, *POTword, *STword;
    struct traversing_array *node = NULL;
    int not_match_counter = 0;
    char is_started = 0;
    int line_number = 0, is_data_section_activated = 0, skip = 0;

    IMCPointer = fopen("./Files/IMC.txt", "w");
    ALPPointer = fopen("./Files/ALP.txt", "r");

    result = fgets(codeline, 100, ALPPointer);
    while (result != NULL)
    {
        skip = 0;
        ALPword = strtok(codeline, " ");
        int counter = 0;
        while (ALPword != NULL)
        {
            strcpy(tempString, strupr(ALPword));
            if (tempString[strlen(tempString) - 1] == '\n')
            {
                tempString[strlen(tempString) - 1] = '\0';
            }
            insert_in_link_list(tempString);
            ALPword = strtok(NULL, " ");
            counter++;
        }
        node = NULL;
        node = head;
        if (strcmp(node->word, "END") == 0)
        {
            skip = 1;
            goto check_end;
        }
        if (strcmp(node->word, "ENDP") == 0)
        {
            skip = 1;
            is_data_section_activated = 1;
        }
        if (is_started == 1 && skip != 1)
        {
            fputs(instruction_address, IMCPointer);
        }
        while (node != NULL)
        {
            int matchwith_mot_table = 0;
            int matchwith_pot_table = 0;
            int matchwith_st_table = 0;
            if (strcmp(node->word, "START") == 0)
            {
                if (is_started == 0 && line_number == 0)
                {
                    is_started = 1;
                    if (node->next == NULL)
                    {
                    }
                    else
                    {
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
            fputs(" ", IMCPointer);
            MOTPointer = fopen("./Files/MOT.txt", "r");
            motresult = fgets(MOTcodeline, 100, MOTPointer);
            while (motresult != NULL)
            {
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
                    MOTword = strtok(NULL, " ");
                    counter++;
                }
                motresult = fgets(MOTcodeline, 100, MOTPointer);
                if (strcmp(node->word, new_mot_line.mneumonics) == 0)
                {
                    fputs(new_mot_line.op_code, IMCPointer);
                    update_instruction_address(new_mot_line.length_of_instruction);
                    matchwith_mot_table = 1;
                }
            }
            fclose(MOTPointer);
            POTPointer = fopen("./Files/POT.txt", "r");
            potresult = fgets(POTcodeline, 100, POTPointer);
            while (potresult != NULL)
            {
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
                    POTword = strtok(NULL, " ");
                    counter++;
                }
                potresult = fgets(POTcodeline, 100, POTPointer);
                if (strcmp(node->word, new_pot_line.psudo_op_code) == 0)
                {
                    matchwith_pot_table = 1;
                    if (strcmp(node->word, "DB") == 0)
                    {
                        update_instruction_address("1");
                        fputs("_", IMCPointer);
                    }
                    if (strcmp(node->word, "DD") == 0)
                    {
                        update_instruction_address("2");
                        fputs("_", IMCPointer);
                    }
                    if (strcmp(node->word, "DW") == 0)
                    {
                        update_instruction_address("2");
                        fputs("_", IMCPointer);
                    }
                    if (strcmp(node->word, "CONST") == 0)
                    {
                        update_instruction_address("1");
                        fputs("_", IMCPointer);
                    }
                }
            }
            fclose(POTPointer);
            int is_colon_comes = 0;
            STPointer = fopen("./Files/ST.txt", "r");
            stresult = fgets(STcodeline, 100, STPointer);
            while (stresult != NULL)
            {
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
                    STword = strtok(NULL, " ");
                    counter++;
                }

                stresult = fgets(STcodeline, 100, STPointer);
                char colon_removed_string[50];
                strcpy(colon_removed_string, node->word);
                if (node->word[strlen(node->word) - 1] == ':')
                {
                    is_colon_comes = 1;
                    colon_removed_string[strlen(colon_removed_string) - 1] = '\0';
                }
                if (strcmp(colon_removed_string, new_st_line.symbol_name) == 0)
                {
                    matchwith_st_table = 1;
                    if (strcmp(new_st_line.definition_address, "____") == 0)
                    {
                    }
                    else
                    {
                        if (is_colon_comes != 1)
                        {
                            if (is_data_section_activated != 1)
                            {
                                fputs(new_st_line.definition_address, IMCPointer);
                            }
                        }
                    }
                }
            }
            fclose(STPointer);
            if (is_colon_comes == 1)
            {
                is_colon_comes = 0;
                TEMPPointer = fopen("./Files/TempFile.txt", "w");
                STPointer = fopen("./Files/ST.txt", "r");
                stresult = fgets(STcodeline, 100, STPointer);
                while (stresult != NULL)
                {
                    char copying_string[50];
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
                        STword = strtok(NULL, " ");
                        counter++;
                    }
                    char colon_removed_string[50];
                    strcpy(colon_removed_string, node->word);
                    if (node->word[strlen(node->word) - 1] == ':')
                    {
                        is_colon_comes = 1;
                        colon_removed_string[strlen(colon_removed_string) - 1] = '\0';
                    }
                    if (strcmp(colon_removed_string, new_st_line.symbol_name) == 0)
                    {
                        fputs(new_st_line.symbol_name, TEMPPointer);
                        fputs(" LABEL ", TEMPPointer);
                        fputs(instruction_address, TEMPPointer);
                        fputs("\n", TEMPPointer);
                    }
                    else
                    {
                        fputs(copying_string, TEMPPointer);
                    }
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
            if (matchwith_mot_table != 1 && matchwith_pot_table != 1 && matchwith_st_table != 1)
            {
                char label_handaling_array[50];
                not_match_counter += 1;
                STPointer = fopen("./Files/ST.txt", "a");
                if (strcmp(node->word, "?") == 0)
                {
                    fputs(node->word, IMCPointer);
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
                            skip = 1;
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
                    TEMPPointer = fopen("./Files/TempFile.txt", "w");
                    STPointer = fopen("./Files/ST.txt", "r");
                    stresult = fgets(STcodeline, 100, STPointer);
                    while (stresult != NULL)
                    {
                        char copying_string[50];
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
                            STword = strtok(NULL, " ");
                            counter++;
                        }
                        if (strcmp(node->word, new_st_line.symbol_name) == 0)
                        {
                            fputs(new_st_line.symbol_name, TEMPPointer);
                            fputs(" ", TEMPPointer);
                            if (strcmp(node->next->word, "CONST") == 0)
                            {
                                fputs("CONST", TEMPPointer);
                            }
                            else
                            {
                                fputs(new_st_line.type, TEMPPointer);
                            }
                            fputs(" ", TEMPPointer);
                            fputs(instruction_address, TEMPPointer);
                            fputs("\n", TEMPPointer);
                        }
                        else
                        {
                            fputs(copying_string, TEMPPointer);
                        }
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
                    if (node->next != NULL)
                    {
                        fputs("  ", IMCPointer);
                    }
                    fputs(node->next->word, IMCPointer);
                    break;
                }
            }
            node = node->next;
        }
        delete_link_list();
        result = fgets(codeline, 100, ALPPointer);
        fputs("\n", IMCPointer);
        line_number++;
    }

check_end:
    STPointer = fopen("./Files/ST.txt", "r");
    stresult = fgets(STcodeline, 100, STPointer);
    int data_undefined_flag = 0;
    while (stresult != NULL)
    {
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
            STword = strtok(NULL, " ");
            counter++;
        }
        stresult = fgets(STcodeline, 100, STPointer);
        if (strcmp(new_st_line.definition_address, "____") == 0)
        {
            printf("\nERROR: '%s' is Not Defined\n", new_st_line.symbol_name);
            goto clean_up;
        }
    }
    if (data_undefined_flag == 0)
    {
        printf("\n########     No ERRORS, YOU CAN PROCED AHEAD     ########\n");
    }
    fclose(STPointer);

clean_up:
    printf("\nCLEANING EVERYTHING ......\n");
    delete_link_list();
    fclose(STPointer);
    fclose(MOTPointer);
    fclose(POTPointer);
    fclose(ALPPointer);
    fclose(IMCPointer);
    fclose(TEMPPointer);
    free(node);
    free(result);
    free(motresult);
    free(potresult);
    free(stresult);
    free(ALPword);
    free(MOTword);
    free(POTword);
    free(STword);
}