#include "headers.h"
void init_direc(direc *Dir)
{
    Dir->username = (char *)malloc(sizeof(char) * 256);
    Dir->username = getlogin();
    Dir->sysname = (char *)malloc(sizeof(char) * 256);
    gethostname(Dir->sysname, 256);
    Dir->homed = (char *)malloc(sizeof(char) * 256);
    // home directory decision
    getcwd(Dir->homed, 256);
    Dir->present = (char *)malloc(sizeof(char) * 256);
    strcpy(Dir->present, Dir->homed);
    Dir->prev = (char *)malloc(sizeof(char) * 256);
}
int check(char *home, char *present)
{
    int retv = 1;
    for (int i = 0; i < strlen(home); i++)
    {
        if (home[i] != present[i])
        {
            retv = 0;
            break;
        }
    }
    return retv;
}
void prompt(direc *Dir, int *time, char **past, int *ind)
{
    // Do not hardcode the prmopt
    int substr = check(Dir->homed, Dir->present);
    if (substr == 1)
    {
        printf(ANSI_COLOR_MAGENTA"<%s@%s:"ANSI_COLOR_RESET, Dir->username, Dir->sysname);
        for (int i = 0; i < strlen(Dir->present); i++)
        {
            if (i >= strlen(Dir->homed) - 1)
            {
                if (i == strlen(Dir->homed) - 1)
                {
                    printf(ANSI_COLOR_MAGENTA"~"ANSI_COLOR_RESET);
                }
                else
                {
                    printf(ANSI_COLOR_MAGENTA "%c" ANSI_COLOR_RESET, Dir->present[i]);
                }
            }
        }
        if (*ind > 0 && *time > 2)
            printf(ANSI_COLOR_MAGENTA" %s : %ds"ANSI_COLOR_RESET, past[*ind - 1], *time);
        printf(ANSI_COLOR_MAGENTA">"ANSI_COLOR_RESET);
    }
    else
    {
        if (*ind > 0 && *time > 2)
            printf(ANSI_COLOR_MAGENTA"<%s@%s:%s %s : %ds>"ANSI_COLOR_RESET, Dir->username, Dir->sysname, Dir->present, past[*ind - 1], *time);
        else
            printf(ANSI_COLOR_MAGENTA"<%s@%s:%s>"ANSI_COLOR_RESET, Dir->username, Dir->sysname, Dir->present);
    }
    *time = 0;
}
