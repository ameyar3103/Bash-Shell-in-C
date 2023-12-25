#include "headers.h"
void syscalls(char *comm,int* back,int* index)
{
    char *args[256];
    char *token = strtok(comm, " ");
    int arg_count = 0;

    while (token != NULL)
    {
        args[arg_count] = token;
        token = strtok(NULL, " ");
        arg_count++;
    }
    args[arg_count] = NULL;
    int flag=0;
    if(arg_count > 0 && strcmp(args[arg_count-1],"&")==0)
    {   
        flag=1;
        args[arg_count-1]=NULL;
    }
    if (arg_count > 0)
    {
        if (strcmp(args[0], "exit") == 0)
        {
            // Exit the shell
            exit(0);
        }
        else
        {
            // Fork a child process
            pid_t child_pid = fork();
            if (child_pid == 0)
            {
                // Child process
                execvp(args[0], args);
                perror("execvp"); // This will be printed if execvp fails
                exit(1);
            }
            else if (child_pid > 0)
            {
                // Parent process
                if (flag==0)
                {
                    wait(NULL);
                } // Wait for the child process to complete
                else
                {
                    back[(*index)++]=child_pid;
                    printf("%d\n",child_pid);
                }
            }
            else
            {
                // Fork failed
                perror("fork");
            }
        }
    }
}