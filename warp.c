#include "headers.h"

void warp_changedir(char *newd, direc *Dir)
{
    if (newd[5] == '~')
    { // case for home and then inside
        char *temp = (char *)malloc(sizeof(char) * 256);
        for (int i = 6; i < strlen(newd); i++)
        {
            temp[i - 6] = newd[i];
        }
        temp[strlen(newd) - 6] = '\0';
        char path[256];
        strcpy(path, Dir->homed);
        strncat(path, temp, 256);
        char buff[256];
        if (chdir(path) == 0)
        {
            getcwd(buff,256);
            strcpy(Dir->prev, Dir->present);
            strcpy(Dir->present, Dir->homed);
            strncat(Dir->present, temp, 256);
            printf("Changed Directory to : %s\n", buff);
            strcpy(Dir->present,buff);
        }
        else
            perror("chdir");
        free(temp);
    }
    else if (newd[5] == '/') // case for address given
    {
        char *temp = (char *)malloc(sizeof(char) * 256);
        for (int i = 5; i < strlen(newd); i++)
        {
            temp[i - 5] = newd[i];
        }
        temp[strlen(newd) - 5] = '\0';
        char path[256];
        strcpy(path, "");
        strncat(path, temp, 256);
        char buff[256];
        if (chdir(path) == 0)
        {
            getcwd(buff,256);
            strcpy(Dir->prev, Dir->present);
            strcpy(Dir->present, temp);
            printf("Changed Directory to : %s\n", buff);
            strcpy(Dir->present,buff);
        }
        else
            perror("chdir");
        free(temp);
    }
    else if (newd[5] == '-') // case for previous directory
    {
        char *prevt = (char *)malloc(sizeof(char) * 256);
        char *temp = (char *)malloc(sizeof(char) * 256);
        for (int i = 6; i < strlen(newd); i++)
        {
            temp[i - 6] = newd[i];
        }
        temp[strlen(newd) - 6] = '\0';
        char path[256];
        strcpy(path, Dir->prev);
        strncat(path, temp, 256);
        char buff[256];
        if (chdir(path) == 0)
        {
            getcwd(buff,256);
            strcpy(prevt, Dir->prev);
            strcpy(Dir->prev, Dir->present);
            strcpy(Dir->present, prevt);
            strncat(Dir->present, temp, 256);
            printf("Changed Directory to : %s\n", buff);
            strcpy(Dir->present,buff);
        }
        else
            perror("chdir");
        free(temp);
        free(prevt);
    }
    else if (newd[5] == '.' && newd[6] != '.') // case for same directory
    {
        if (strlen(newd) == 6)
            printf("Changed Directory to : %s\n", Dir->present);
        else
        {
            char *temp = (char *)malloc(sizeof(char) * 256);
            for (int i = 6; i < strlen(newd); i++)
            {
                temp[i - 6] = newd[i];
            }
            temp[strlen(newd) - 6] = '\0';
            char path[256];
            strcpy(path, Dir->present);
            strncat(path, temp, 256);
            char buff[256];
            if (chdir(path) == 0)
            {
                getcwd(buff,256);
                strcpy(Dir->prev, Dir->present);
                strncat(Dir->present, temp, 256);
                printf("Changed Directory to : %s\n", buff);
                strcpy(Dir->present,buff);
            }
            else
                perror("chdir");
            free(temp);
        }
    }
    else if (newd[5] == '.' && newd[6] == '.') // case for going to prev dir
    {
        if (strlen(newd) == 7)
        {
            strcpy(Dir->prev, Dir->present);
            int index;
            // char buff[256];
            for (int i = strlen(Dir->present) - 1; i >= 0; i--)
            {
                if (Dir->present[i] == '/')
                {
                    index = i;
                    break;
                }
                Dir->present[i] = '\0';
            }
            Dir->present[index] = '\0';
            chdir(Dir->present);
            printf("Changed Directory to : %s\n", Dir->present);
        }
        else
        {
            strcpy(Dir->prev, Dir->present);
            int index;
            for (int i = strlen(Dir->present) - 1; i >= 0; i--)
            {
                if (Dir->present[i] == '/')
                {
                    index = i;
                    break;
                }
                Dir->present[i] = '\0';
            }
            Dir->present[index] = '\0';
            char *temp = (char *)malloc(sizeof(char) * 256);
            for (int i = 7; i < strlen(newd); i++)
            {
                temp[i - 7] = newd[i];
            }
            temp[strlen(newd) - 7] = '\0';
            char path[256];
            strcpy(path, Dir->present);
            strncat(path, temp, 256);
            char buff[256];
            // getcwd(buff,256);
            if (chdir(path) == 0)
            {
                getcwd(buff,256);
                strncat(Dir->present, temp, 256);
                printf("Changed Directory to : %s\n", buff);
                strcpy(Dir->present,buff);
            }
            else
            perror("chdir");
            free(temp);
        }
    }
    else
    { // case for simply entering directory
        char *temp = (char *)malloc(sizeof(char) * 256);
        for (int i = 5; i < strlen(newd); i++)
        {
            temp[i - 5] = newd[i];
        }
        temp[strlen(newd) - 5] = '\0';
        char path[256];
        strcpy(path, temp);
        char buff[256];
        // getcwd(buff,256);
        if (chdir(path) == 0)
        {
            getcwd(buff,256);
            strcpy(Dir->prev, Dir->present);
            strncat(Dir->present, "/", 10);
            strncat(Dir->present, temp, 256);
            // printf("%s\n", Dir->present);
            printf("Changed Directory to : %s\n",buff);
            strcpy(Dir->present,buff);
        }
        else
            perror("chdir");
        free(temp);
    }
}