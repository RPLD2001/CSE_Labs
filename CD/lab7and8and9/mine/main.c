#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define false 0
#define true 1
#include "lexicalanalyser.h"
#include "parser.h"

void get()
{
    tkn = prev_flag == true ? tkn : NULL;
    while (tkn == NULL)
    {
        tkn = getNextToken(finp, &row, &col_global, data_type_buffer, &c);
    }
    if (strcmp(tkn->lexeme, "EOF") == 0)
    {
        failure("End of file encountered!");
    }
    // prev_flag ?: printf("token : %s\n", tkn->lexeme);
    prev_flag = false;
}

int main()
{
    char filename[100];
    printf("Enter filename:");
    scanf("%s",filename);
    removeExcess(filename);
    row = removePreprocess();
    enum TYPE type;
    for (int i = 0; i < MAX_SIZE; i++)
        hashTable[i] = NULL;
    finp = fopen("space_output.c", "r");
    if (finp == NULL)
    {
        printf("Cannot Find file, exiting ... ");
        return 0;
    }
    int temp_row = --row;
    while (temp_row > 0)
    {
        c = fgetc(finp);
        if (c == '\n')
            temp_row--;
    }
    row;
    col_global = 1;
    get();
    prev_flag = true;
    if (search_first(PROGRAM, tkn->lexeme, tkn->type) == 1)
    {
        Program();
    }
    else
    {
        failure("No Return type found!");
    }
    //printf("\nSymbol Table : \n\n");
    //display_st();
    printf("\n");
    return 0;
}
