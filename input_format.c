#include "headers.h"
void input_format(char* input)
{
    // char input[4096];
    // fgets(input, 4096, stdin);
    // int extras = 0;
    char edit[4096];
    strcpy(edit, input);
    int k = strlen(edit);
    for (int i = 0; i < strlen(edit); i++)
    {
        if (edit[i + 1] == '&')
        {
            if (edit[i] != ' ')
            {
                for (int j = strlen(edit)-1; j >= i; j--)
                {
                    edit[j + 1] = edit[j];
                }
                edit[i + 1] = ' ';
            }
        }
    }
    // printf("%s", edit);
    int edit_index = 0;
    for (int i = 0; i <= strlen(edit); i++)
    {
        if ((i != 0 && edit[i - 1] == ' ' && edit[i] == ' ' && input[edit_index - 1] == ' ') ||edit[i]=='\t')
            continue;
        else
        {
            input[edit_index++] = edit[i];
        }
    }
    input[edit_index] = '\0';
    // printf("%s", input);
    for (int i = 0; i <= strlen(input); i++)
    {
        if (input[i] == ';' && input[i-1] == ' ')
        {
            for (int j = i; j <= strlen(input); j++)
            {
                input[j - 1] = input[j];
            }
        }
    }
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == ';' && input[i+1] == ' ')
        {
            for (int j = i+2; j <= strlen(input); j++)
            {
                input[j - 1] = input[j];
            }
        }
    }
    if(input[0]==' ')
    strcpy(input,input+1);
    // printf("%s",input);
}