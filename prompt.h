#ifndef __PROMPT_H
#define __PROMPT_H
typedef struct direc{
    char* homed;
    char* present;
    char* username;
    char* sysname;
    char* prev;
}direc;
// all commands implemented using
void prompt(direc* Dir,int* time,char** past,int* ind);
void init_direc(direc* Dir);
void warp_changedir(char *newd, direc *Dir);
int check(char* home,char* present);
void peek_call(direc* Dir,char* peekd);
void pasteve(direc* Dir,char* comm,char** past,int* index);
int pasteve_read(direc* Dir,char** past);
void pasteve_write(direc* Dir,char** past,int* index);
void syscalls(char* comm,int* back,int* index);
void shell_info(direc* Dir);
void process_info(int pid,direc* Dir);
void input_format(char* input);
void seek_call(direc *Dir, char *comm);
void seek_change(direc* Dir,char* name,char* checker,char* target,char* storage,int* find);
#endif