#include "headers.h"
int compare_entriy(const struct dirent **a, const struct dirent **b)
{
    return alphasort(a, b);
}
int checking(char *home, char *present)
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
void seek_change(direc *Dir, char *name, char *checker, char *target, char *storage, int *flag)
{
    if (strcmp(checker, "de") == 0)
    {
        struct dirent **entry_list;
        int num_entries;
        // printf("%s\n%s\n",name,target);
        num_entries = scandir(target, &entry_list, NULL, compare_entriy);
        if (num_entries == -1)
        {
            perror("scandir");
            return;
        }

        for (int i = 0; i < num_entries; i++)
        {
            char full_path[257];
            snprintf(full_path, sizeof(full_path), "%s/%s", target, entry_list[i]->d_name);

            struct stat sb;
            if (stat(full_path, &sb) == 0)
            {
                if (S_ISDIR(sb.st_mode) && entry_list[i]->d_name[0] != '.')
                {
                    if (strncmp(entry_list[i]->d_name, name,strlen(name)) == 0)
                    {
                        *flag = 1;
                        int check = checking(Dir->present, target);
                        for (int j = 0; j < strlen(target); j++)
                        {
                            if (j >= strlen(Dir->present) - 1)
                            {
                                if (j == strlen(Dir->present) - 1)
                                    printf(ANSI_COLOR_BLUE "." ANSI_COLOR_RESET);
                                else
                                    printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, target[j]);
                            }
                        }
                        if (check != 1)
                        {
                            check = checking(Dir->homed, target);
                            for (int j = 0; j < strlen(target); j++)
                            {
                                if (j >= strlen(Dir->homed) - 1)
                                {
                                    if (j == strlen(Dir->homed) - 1)
                                        printf(ANSI_COLOR_BLUE "." ANSI_COLOR_RESET);
                                    else
                                        printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, target[j]);
                                }
                            }
                        }
                        printf(ANSI_COLOR_BLUE "/%s\n" ANSI_COLOR_RESET, entry_list[i]->d_name);
                        strcpy(storage, target);
                        strcat(storage, "/");
                        strcat(storage, entry_list[i]->d_name);
                    }
                    char path[4096];
                    strcpy(path, target);
                    strcat(path, "/");
                    strcat(path, entry_list[i]->d_name);
                    seek_change(Dir, name, checker, path, storage, flag);
                    // free(path);
                }
            }
            free(entry_list[i]);
        }
    }
    else if (strcmp(checker, "fe") == 0)
    {
        struct dirent **entry_list;
        int num_entries;
        // printf("%s\n%s\n",name,target);
        num_entries = scandir(target, &entry_list, NULL, compare_entriy);
        if (num_entries == -1)
        {
            perror("scandir");
            return;
        }

        for (int i = 0; i < num_entries; i++)
        {
            char full_path[257];
            snprintf(full_path, sizeof(full_path), "%s/%s", target, entry_list[i]->d_name);

            struct stat sb;
            if (stat(full_path, &sb) == 0)
            {
                if (S_ISDIR(sb.st_mode) && entry_list[i]->d_name[0] != '.')
                {
                    char path[4096];
                    strcpy(path, target);
                    strcat(path, "/");
                    strcat(path, entry_list[i]->d_name);
                    seek_change(Dir, name, checker, path, storage, flag);
                }
                else if (S_ISREG(sb.st_mode))
                {
                    char *first[2];
                    char *token = strtok(entry_list[i]->d_name, ".");
                    int index = 0;
                    while (token != NULL)
                    {
                        first[index++] = token;
                        token = strtok(NULL, ".");
                    }
                    if (strncmp(first[0], name,strlen(name)) == 0)
                    {
                        *flag = 1;
                        int check = checking(Dir->present, target);
                        for (int j = 0; j < strlen(target); j++)
                        {
                            if (j >= strlen(Dir->present) - 1)
                            {
                                if (j == strlen(Dir->present) - 1)
                                    printf(ANSI_COLOR_GREEN "." ANSI_COLOR_RESET);
                                else
                                    printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, target[j]);
                            }
                        }
                        if (check != 1)
                        {
                            check = checking(Dir->homed, target);
                            for (int j = 0; j < strlen(target); j++)
                            {
                                if (j >= strlen(Dir->homed) - 1)
                                {
                                    if (j == strlen(Dir->homed) - 1)
                                        printf(ANSI_COLOR_GREEN "." ANSI_COLOR_RESET);
                                    else
                                        printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, target[j]);
                                }
                            }
                        }
                        printf(ANSI_COLOR_GREEN "/%s.%s\n" ANSI_COLOR_RESET, first[0], first[1]);
                        strcpy(storage, target);
                        strcat(storage, "/");
                        strcat(storage, first[0]);
                        strcat(storage, ".");
                        strcat(storage, first[1]);
                    }
                }
            }
            free(entry_list[i]);
        }
    }
}
void main_seek(direc *Dir, char *name, char *checker, char *target, int both, int *flag)
{
    if (strcmp(checker, "d_") == 0)
    {
        struct dirent **entry_list;
        int num_entries;
        // printf("%s\n%s\n",name,target);
        num_entries = scandir(target, &entry_list, NULL, compare_entriy);
        if (num_entries == -1)
        {
            perror("scandir");
            return;
        }

        for (int i = 0; i < num_entries; i++)
        {
            char full_path[257];
            snprintf(full_path, sizeof(full_path), "%s/%s", target, entry_list[i]->d_name);

            struct stat sb;
            if (stat(full_path, &sb) == 0)
            {
                if (S_ISDIR(sb.st_mode) && entry_list[i]->d_name[0] != '.')
                {
                    if (strncmp(entry_list[i]->d_name, name,strlen(name)) == 0)
                    {
                        *flag = 1;
                        int check = checking(Dir->present, target);
                        for (int j = 0; j < strlen(target); j++)
                        {
                            if (j >= strlen(Dir->present) - 1)
                            {
                                if (j == strlen(Dir->present) - 1)
                                    printf(ANSI_COLOR_BLUE "." ANSI_COLOR_RESET);
                                else
                                    printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, target[j]);
                            }
                        }
                        if (check != 1)
                        {
                            check = checking(Dir->homed, target);
                            for (int j = 0; j < strlen(target); j++)
                            {
                                if (j >= strlen(Dir->homed) - 1)
                                {
                                    if (j == strlen(Dir->homed) - 1)
                                        printf(ANSI_COLOR_BLUE "." ANSI_COLOR_RESET);
                                    else
                                        printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, target[j]);
                                }
                            }
                        }
                        printf(ANSI_COLOR_BLUE "/%s\n" ANSI_COLOR_RESET, entry_list[i]->d_name);
                    }
                    char path[4096];
                    strcpy(path, target);
                    strcat(path, "/");
                    strcat(path, entry_list[i]->d_name);
                    main_seek(Dir, name, checker, path, both, flag);
                    // free(path);
                }
            }
            free(entry_list[i]);
        }
    }
    else if (strcmp(checker, "f_") == 0)
    {
        struct dirent **entry_list;
        int num_entries;
        // printf("%s\n%s\n",name,target);
        num_entries = scandir(target, &entry_list, NULL, compare_entriy);
        if (num_entries == -1)
        {
            perror("scandir");
            return;
        }

        for (int i = 0; i < num_entries; i++)
        {
            char full_path[257];
            snprintf(full_path, sizeof(full_path), "%s/%s", target, entry_list[i]->d_name);

            struct stat sb;
            if (stat(full_path, &sb) == 0)
            {
                if (S_ISDIR(sb.st_mode) && entry_list[i]->d_name[0] != '.')
                {
                    char path[4096];
                    strcpy(path, target);
                    strcat(path, "/");
                    strcat(path, entry_list[i]->d_name);
                    main_seek(Dir, name, checker, path, both, flag);
                }
                else if (S_ISREG(sb.st_mode))
                {
                    char *first[2];
                    char *token = strtok(entry_list[i]->d_name, ".");
                    int index = 0;
                    while (token != NULL)
                    {
                        first[index++] = token;
                        token = strtok(NULL, ".");
                    }
                    if (strncmp(first[0], name,strlen(name)) == 0)
                    {
                        *flag = 1;
                        int check = checking(Dir->present, target);
                        for (int j = 0; j < strlen(target); j++)
                        {
                            if (j >= strlen(Dir->present) - 1)
                            {
                                if (j == strlen(Dir->present) - 1)
                                    printf(ANSI_COLOR_GREEN "." ANSI_COLOR_RESET);
                                else
                                    printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, target[j]);
                            }
                        }
                        if (check != 1)
                        {
                            check = checking(Dir->homed, target);
                            for (int j = 0; j < strlen(target); j++)
                            {
                                if (j >= strlen(Dir->homed) - 1)
                                {
                                    if (j == strlen(Dir->homed) - 1)
                                        printf(ANSI_COLOR_GREEN "." ANSI_COLOR_RESET);
                                    else
                                        printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, target[j]);
                                }
                            }
                        }
                        printf(ANSI_COLOR_GREEN "/%s.%s\n" ANSI_COLOR_RESET, first[0], first[1]);
                    }
                }
            }
            free(entry_list[i]);
        }
    }
    else if (both == 1)
    {
        struct dirent **entry_list;
        int num_entries;
        // printf("%s\n%s\n",name,target);
        num_entries = scandir(target, &entry_list, NULL, compare_entriy);
        if (num_entries == -1)
        {
            perror("scandir");
            return;
        }

        for (int i = 0; i < num_entries; i++)
        {
            char full_path[257];
            snprintf(full_path, sizeof(full_path), "%s/%s", target, entry_list[i]->d_name);

            struct stat sb;
            if (stat(full_path, &sb) == 0)
            {
                char *first[2];
                char *token = strtok(entry_list[i]->d_name, ".");
                int index = 0;
                while (token != NULL)
                {
                    first[index++] = token;
                    token = strtok(NULL, ".");
                }
                if (S_ISREG(sb.st_mode))
                {
                    if (strncmp(name, first[0],strlen(name)) == 0)
                    {
                        *flag = 1;
                        int check = checking(Dir->present, target);
                        for (int j = 0; j < strlen(target); j++)
                        {
                            if (j >= strlen(Dir->present) - 1)
                            {
                                if (j == strlen(Dir->present) - 1)
                                    printf(ANSI_COLOR_GREEN "." ANSI_COLOR_RESET);
                                else
                                    printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, target[j]);
                            }
                        }
                        if (check != 1)
                        {
                            check = checking(Dir->homed, target);
                            for (int j = 0; j < strlen(target); j++)
                            {
                                if (j >= strlen(Dir->homed) - 1)
                                {
                                    if (j == strlen(Dir->homed) - 1)
                                        printf(ANSI_COLOR_GREEN "." ANSI_COLOR_RESET);
                                    else
                                        printf(ANSI_COLOR_GREEN "%c" ANSI_COLOR_RESET, target[j]);
                                }
                            }
                        }
                        printf(ANSI_COLOR_GREEN "/%s.%s\n" ANSI_COLOR_RESET, first[0], first[1]);
                    }
                }
                else if (S_ISDIR(sb.st_mode) && entry_list[i]->d_name[0] != '.')
                {
                    if (strncmp(name, first[0],strlen(name)) == 0)
                    {
                        *flag = 1;
                        int check = checking(Dir->present, target);
                        for (int j = 0; j < strlen(target); j++)
                        {
                            if (j >= strlen(Dir->present) - 1)
                            {
                                if (j == strlen(Dir->present) - 1)
                                    printf(ANSI_COLOR_BLUE "." ANSI_COLOR_RESET);
                                else
                                    printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, target[j]);
                            }
                        }
                        if (check != 1)
                        {
                            check = checking(Dir->homed, target);
                            for (int j = 0; j < strlen(target); j++)
                            {
                                if (j >= strlen(Dir->homed) - 1)
                                {
                                    if (j == strlen(Dir->homed) - 1)
                                        printf(ANSI_COLOR_BLUE "." ANSI_COLOR_RESET);
                                    else
                                        printf(ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, target[j]);
                                }
                            }
                        }
                        printf(ANSI_COLOR_BLUE "/%s\n" ANSI_COLOR_RESET, entry_list[i]->d_name);
                    }
                    char path[4096];
                    strcpy(path, target);
                    strcat(path, "/");
                    strcat(path, first[0]);
                    main_seek(Dir, name, checker, path, both, flag);
                }
            }
            free(entry_list[i]);
        }
    }
}
void seek_call(direc *Dir, char *comm)
{
    char *arg[5];
    // printf("%s\n",comm);
    int arg_count = 0;
    char *token = strtok(comm, " ");
    while (token != NULL)
    {
        // printf("%s\n",token);
        arg[arg_count] = token;
        arg_count++;
        token = strtok(NULL, " ");
    }
    arg[arg_count] = NULL;
    if (arg_count > 2 && ((strcmp(arg[1], "-d") == 0 && strcmp(arg[2], "-e") == 0) || (strcmp(arg[2], "-d") == 0 && strcmp(arg[1], "-e") == 0)))
    {
        // code for -e and -d
        if (arg_count == 4)
        {
            // code for no target directory
            char checker[10];
            strcpy(checker, "de");
            char path[256];
            strcpy(path, Dir->present);
            // printf("%s\n",path);
            char storage[256];
            strcpy(storage, ".");
            int f = 0;
            seek_change(Dir, arg[3], checker, path, storage, &f);
            if (f == 1)
            {
                char final[4096];
                strcpy(final, "warp ");
                strcat(final, storage);
                warp_changedir(final, Dir);
            }
            else
            {
                printf(ANSI_COLOR_RED "No match found!\n" ANSI_COLOR_RED);
            }
        }
        else
        {
            // code for given target directory
            char checker[10];
            strcpy(checker, "de");
            char path[256];
            if (arg[4][0] == '.')
                strcpy(path, Dir->present);
            else if (arg[4][0] == '~')
                strcpy(path, Dir->homed);
            strcat(path, arg[4] + 1);
            char storage[4096];
            strcpy(storage, ".");
            int f = 0;
            seek_change(Dir, arg[3], checker, path, storage, &f);
            if (f == 1)
            {
                char final[4095];
                strcpy(final, "warp ");
                strcat(final, storage);
                warp_changedir(final, Dir);
            }
            else
            {
                printf(ANSI_COLOR_RED "No match found!\n" ANSI_COLOR_RESET);
            }
        }
    }
    else if (arg_count > 2 && ((strcmp(arg[1], "-f") == 0 && strcmp(arg[2], "-e") == 0) || (strcmp(arg[2], "-f") == 0 && strcmp(arg[1], "-e") == 0)))
    {
        // code for -e and -f
        if (arg_count == 4)
        {
            // code for no target directory
            char checker[10];
            strcpy(checker, "fe");
            char path[256];
            strcpy(path, Dir->present);
            // printf("%s\n",path);
            char storage[256];
            strcpy(storage, ".");
            int f = 0;
            seek_change(Dir, arg[3], checker, path, storage, &f);
            // printf("%s\n",storage);
            if (f == 1)
            {
                int fd = open(storage, O_RDONLY);
                char buffer[200000];
                read(fd, buffer, 200000);
                printf("%s", buffer);
            }
            else
                printf(ANSI_COLOR_RED "No match found!\n" ANSI_COLOR_RESET);
        }
        else
        {
            // code for given target directory
            char checker[10];
            strcpy(checker, "fe");
            char path[256];
            if (arg[4][0] == '.')
                strcpy(path, Dir->present);
            else if (arg[4][0] == '~')
                strcpy(path, Dir->homed);
            strcat(path, arg[4] + 1);
            char storage[4096];
            strcpy(storage, ".");
            int f = 0;
            seek_change(Dir, arg[3], checker, path, storage, &f);
            if (f == 1)
            {
                int fd = open(storage, O_RDONLY);
                char buffer[200000];
                read(fd, buffer, 200000);
                printf("%s", buffer);
            }
            else
                printf(ANSI_COLOR_RED "No match found!\n" ANSI_COLOR_RESET);
        }
    }
    else if ((strcmp(arg[1], "-d")) == 0)
    {
        // code for just -d
        if (arg_count == 3)
        {
            // code for no target directory
            char checker[10];
            strcpy(checker, "d_");
            char path[256];
            strcpy(path, Dir->present);
            // printf("%s\n",path);
            int f = 0;
            main_seek(Dir, arg[2], checker, path, 0, &f);
            if (f == 0)
            {
                printf(ANSI_COLOR_RED "No match found!\n" ANSI_COLOR_RESET);
            }
        }
        else
        {
            // code for given target directory
            char checker[10];
            strcpy(checker, "d_");
            char path[256];
            if (arg[3][0] == '.')
                strcpy(path, Dir->present);
            else if (arg[3][0] == '~')
                strcpy(path, Dir->homed);
            strcat(path, arg[3] + 1);
            int f = 0;
            main_seek(Dir, arg[2], checker, path, 0, &f);
            if (f == 0)
                printf(ANSI_COLOR_RED "No match found!\n" ANSI_COLOR_RESET);
        }
    }
    else if (strcmp(arg[1], "-f") == 0)
    {
        // code for just -f
        if (arg_count == 3)
        {
            // code for no target directory
            char checker[10];
            strcpy(checker, "f_");
            char path[256];
            strcpy(path, Dir->present);
            // printf("%s\n",path);
            int f = 0;
            main_seek(Dir, arg[2], checker, path, 0, &f);
            if (f == 0)
                printf(ANSI_COLOR_RED "No match found!\n" ANSI_COLOR_RESET);
        }
        else
        {
            // code for given target directory
            char checker[10];
            strcpy(checker, "f_");
            char path[256];
            if (arg[3][0] == '.')
            {
                strcpy(path, Dir->present);
                strcat(path, arg[3] + 1);
            }
            else if (arg[3][0] == '~')
            {
                strcpy(path, Dir->homed);
                strcat(path, arg[3] + 1);
            }
            int f = 0;
            main_seek(Dir, arg[2], checker, path, 0, &f);
            if (f == 0)
                printf(ANSI_COLOR_RED "No match found!\n" ANSI_COLOR_RESET);
        }
    }
    else if (arg[1][0] != '-')
    {
        // code for no flags
        if (arg_count == 2)
        {
            // code for no target directory
            char checker[10];
            strcpy(checker, "_");
            char path[256];
            strcpy(path, Dir->present);
            // printf("%s\n",path);
            int f = 0;
            main_seek(Dir, arg[1], checker, path, 1, &f);
            if (f == 0)
                printf(ANSI_COLOR_RED "No match found!\n" ANSI_COLOR_RESET);
        }
        else
        {
            // code for given target directory
            char checker[10];
            strcpy(checker, "_");
            char path[256];
            if (arg[2][0] == '.')
            {
                strcpy(path, Dir->present);
                strcat(path, arg[2] + 1);
            }
            else if (arg[2][0] == '~')
            {
                strcpy(path, Dir->homed);
                strcat(path, arg[2] + 1);
            }
            int f = 0;
            main_seek(Dir, arg[1], checker, path, 1, &f);
            if (f == 0)
                printf(ANSI_COLOR_RED "No match found!\n" ANSI_COLOR_RESET);
        }
    }
    else
    {
        // code for invalid flags
        printf("Invalid flags!\n");
    }
}
