#include "headers.h"
void write_file(int *ind, char **pastevents, direc *Dir, char *input)
{
    if (*ind != 0)
    {
        if (strcmp(pastevents[(*ind) <= 14 ? (*ind) - 1 : 14], input) != 0)
        {
            pasteve(Dir, input, pastevents, ind);
        }
        pasteve_write(Dir, pastevents, ind);
    }
    else
    {
        pasteve(Dir, input, pastevents, ind);
        pasteve_write(Dir, pastevents, ind);
    }
}
int executeuser(direc *Dir, char **pastevents, char *input, int *time, int *backgroundp, int *back_ind)
{
    if (input[0] == 'w' && input[1] == 'a' && input[2] == 'r' && input[3] == 'p')
    {
        char *args[32];
        int arg_count = 0;
        char *token = strtok(input, " ");
        while (token != NULL)
        {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " ");
        }
        char temp[256];
        for (int i = 1; i < arg_count; i++)
        {
            strcpy(temp, "warp ");
            strncat(temp, args[i], 256);
            warp_changedir(temp, Dir);
        }
    }
    else if (input[0] == 'p' && input[1] == 'e' && input[2] == 'e' && input[3] == 'k')
    {
        // input[strlen(input) - 1] = '\0';
        peek_call(Dir, input);
    }
    else if (input[0] == 'p' && input[1] == 'r' && input[2] == 'o' && input[3] == 'c' && input[4] == 'l' && input[5] == 'o' && input[6] == 'r' && input[7] == 'e')
    {
        if (strlen(input) == 8)
        { // code for shell info
            shell_info(Dir);
            input[8] = '\0';
        }
        else
        {
            int pid = 0;
            for (int i = 9; i < strlen(input); i++)
            {
                pid += ((int)input[i] - 48) * pow(10, strlen(input) - 1 - i);
            }
            process_info(pid, Dir);
            // input[strlen(input) - 1] = '\0';
        }
    }
    else if (input[0] == 's' && input[1] == 'e' && input[2] == 'e' && input[3] == 'k')
    {
        seek_call(Dir, input);
    }
    else
    {
        // input[strlen(input)-1] = '\0';
        // printf("%s\n",input);
        syscalls(input, backgroundp, back_ind);
    }
}
int main()
{
    // Keep accepting commands
    direc *Dir = (direc *)malloc(sizeof(direc));
    init_direc(Dir);
    char **pastevents = (char **)malloc(sizeof(char *) * 16);
    for (int i = 0; i < 15; i++)
    {
        pastevents[i] = (char *)malloc(sizeof(char) * 256);
    }
    int ind = pasteve_read(Dir, pastevents);
    if (ind != 0 && strcmp(pastevents[ind - 1], "exit") != 0)
    {
        if (ind <= 14)
        {
            strcpy(pastevents[ind], "exit");
            ind++;
        }
    }
    char **backgroundp = (char **)malloc(sizeof(char *) * 100);
    for (int i = 0; i < 100; i++)
    {
        backgroundp[i] = (char *)malloc(sizeof(char) * 256);
    }
    int back_ind = 0;
    int back_ids[99];
    int time = 0;
    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        for (int i = 0; i < back_ind; i++)
        {
            int status;
            pid_t result = waitpid(back_ids[i], &status, WNOHANG);
            // printf("%d\n",result);
            if (result == back_ids[i])
            {
                if (WIFEXITED(status))
                {
                    printf("%s exited normally [%d]\n", backgroundp[i], back_ids[i]);
                    for (int j = i; j < back_ind - 1; j++)
                    {
                        strcpy(backgroundp[i], backgroundp[i + 1]);
                        back_ids[i] = back_ids[i + 1];
                    }
                    back_ind--;
                }
                else
                {
                    if (WIFSIGNALED(status))
                    {
                        printf("%s exited with signal : %d [%d]\n", backgroundp[i], WTERMSIG(status), back_ids[i]);
                        for (int j = i; j < back_ind - 1; j++)
                        {
                            strcpy(backgroundp[i], backgroundp[i + 1]);
                            back_ids[i] = back_ids[i + 1];
                        }
                        back_ind--;
                    }
                }
            }
            else if (result == -1)
            {
                perror("waitpid");
            }
        }
        prompt(Dir, &time, pastevents, &ind);
        char input[4096];
        fgets(input, 4096, stdin);
        // input[strlen(input) - 1] = '\0';
        input_format(input);
        struct timeval start, end;
        gettimeofday(&start, NULL);
        char temp[19];
        for (int i = 0; i < strlen(input) && i < 18; i++)
        {
            temp[i] = input[i];
        }
        temp[18] = '\0';
        if (strcmp("pastevents\n", input) == 0)
        {
            for (int i = 0; i < 15 && i < ind; i++)
            {
                printf("%s\n", pastevents[i]);
            }
        }
        else if (strcmp("pastevents purge\n", input) == 0)
        {
            for (int i = 0; i < 15 && i < ind; i++)
            {
                pastevents[i][0] = '\0';
            }
            pasteve_write(Dir, pastevents, &ind);
            ind = 0;
        }
        else if (strcmp("pastevents execute", temp) == 0)
        {
            input[strlen(input) - 1] = '\0';
            if (strlen(input) > 21)
            {
                printf("Event number should lie between 1 and 15\n");
            }
            else
            {
                int ex = 0;
                for (int i = 19; i < strlen(input); i++)
                {
                    ex += ((int)input[i] - 48) * pow(10, strlen(input) - i - 1);
                }
                // printf("%d\n", ex);
                if (ex > 15 || ex > ind || ex == 0)
                    printf("Incorrect arguments!\n");
                else
                {
                    char *execomm = (char *)malloc(sizeof(char) * 256);
                    strcpy(execomm, pastevents[ind - ex]);
                    // printf("%s\n", pastevents[ind - ex]);
                    // printf("%s\n", execomm);
                    int index = 0;
                    int flag;
                    if (index >= strlen(execomm))
                        flag = 1;
                    else
                        flag = 0;
                    int k = strlen(execomm);
                    // printf("%d\n", k);
                    while (1)
                    {
                        if (flag == 1)
                            break;
                        char *temp = (char *)malloc(sizeof(char) * 256);
                        strcpy(temp, "");
                        for (int i = index; i < k; i++)
                        {
                            if (i == k - 1)
                                flag = 1;
                            if (execomm[i] != ';' && execomm[i] != '\0')
                            {
                                temp[i - index] = execomm[i];
                                if (i == k - 1)
                                {
                                    temp[i - index + 1] = '\0';
                                    break;
                                }
                            }
                            else
                            {
                                if (flag != 1)
                                    temp[i - index] = '\0';
                                else
                                {
                                    temp[i - index + 1] = '\0';
                                    temp[i - index] = input[i];
                                }
                                index = i + 1;
                                break;
                            }
                        }
                        // printf("%s\n", temp);
                        if (strlen(temp) > 0 && temp[strlen(temp) - 1] == '&')
                        {
                            strcpy(backgroundp[back_ind], temp);
                        }
                        // if(strlen(temp)!=0)
                        executeuser(Dir, pastevents, temp, &time, back_ids, &back_ind);
                        free(temp);
                    }
                    write_file(&ind, pastevents, Dir, execomm);
                    free(execomm);
                }
            }
        }
        else
        {
            input[strlen(input) - 1] = '\0';
            write_file(&ind, pastevents, Dir, input);
            // input[strlen(input) - 1] = '\n';
            // printf("%ld\n", strlen(input));
            int index = 0;
            int flag;
            if (index >= strlen(input))
                flag = 1;
            else
                flag = 0;
            while (1)
            {
                if (flag == 1)
                    break;
                char *temp = (char *)malloc(sizeof(char) * 256);
                strcpy(temp, "");
                for (int i = index; i < strlen(input); i++)
                {
                    if (i == strlen(input) - 1)
                        flag = 1;
                    if (input[i] != ';' && input[i] != '\0' && flag != 1)
                        temp[i - index] = input[i];
                    else
                    {
                        if (flag != 1)
                            temp[i - index] = '\0';
                        else
                        {
                            temp[i - index + 1] = '\0';
                            temp[i - index] = input[i];
                        }
                        index = i + 1;
                        break;
                    }
                }
                // printf("%ld\n",strlen(temp));
                if (strlen(temp) > 0 && temp[strlen(temp) - 1] == '&')
                {
                    strcpy(backgroundp[back_ind], temp);
                }
                // if(strlen(temp)!=0)
                executeuser(Dir, pastevents, temp, &time, back_ids, &back_ind);
                free(temp);
            }
        }
        gettimeofday(&end, NULL);
        time += (end.tv_sec - start.tv_sec);
    }
}
