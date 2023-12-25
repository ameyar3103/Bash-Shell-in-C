#include "headers.h"
int minimum(int a,int b)
{
    if(a<b)
    return a;
    else
    return b;
}
int pasteve_read(direc* Dir,char **past)
{
    char* path=(char*)malloc(sizeof(char)*256);
    strcpy(path,"/home/");
    strncat(path,getlogin(),100);
    strcat(path,"/Documents/");
    strncat(path,"pastevents.txt",50);
    int fd = open(path, O_RDONLY | O_CREAT, 0666);
    char string[20000];
    read(fd, string, 20000);
    // char *token = (char *)malloc(sizeof(char) * 20000);
    char *token = strtok(string, "?");
    int index = 0;
    while (token != NULL)
    {
        // printf("%s\n",token);
        past[index]=token;
        index++;
        token = strtok(NULL, "?");
    }
    close(fd);
    // free(token);
    free(path);
    return index;
}
void pasteve_write(direc* Dir,char **past, int *index)
{
    char *strtowrite = (char *)malloc(sizeof(char) * 20000);
    strcpy(strtowrite, "");
    for (int i = 0; i < 15 && i < *index; i++)
    {
        strncat(strtowrite, past[i], 257);
        if ((i != 14 || i != *index - 1) && past[i][0]!='\0')
            strncat(strtowrite, "?", 10);
    }
    strtowrite[strlen(strtowrite)]='\0';
    char* path=(char*)malloc(sizeof(char)*256);
    strcpy(path,"/home/");
    strncat(path,getlogin(),100);
    strcat(path,"/Documents/");
    strncat(path,"pastevents.txt",50);
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    write(fd, strtowrite, strlen(strtowrite));
    close(fd);
    free(strtowrite);
    free(path);
}
void pasteve(direc *Dir, char *comm, char **past, int *index)
{
    if ((*index) >= 15)
    {
        for (int i = 0; i < 14; i++)
        {
            strcpy(past[i], past[i + 1]);
        }
        strcpy(past[14], comm);
    }
    else
    {
        strcpy(past[*index], comm);
        (*index)++;
    }
}