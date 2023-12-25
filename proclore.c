#include "headers.h"
void format_size(off_t size, char *formatted)
{
    const char *units[] = {"B", "KB", "MB", "GB"};
    int unit = 0;

    while (size >= 1024 && unit < sizeof(units) / sizeof(units[0]))
    {
        size /= 1024;
        unit++;
    }

    sprintf(formatted, "%lld %s", (long long)size, units[unit]);
}
void shell_info(direc *Dir)
{
    int shell_id = getpid();
    printf("pid : %d\n", shell_id);
    int status;
    waitpid(shell_id, &status, 0);
    // printf("%d\n",status);
    char proc_status_path[256];
    snprintf(proc_status_path, sizeof(proc_status_path), "/proc/%d/status", shell_id);

    FILE *status_file = fopen(proc_status_path, "r");
    if (status_file == NULL)
    {
        perror("fopen");
        return;
    }
    char stat_path[256];
    snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", shell_id);
    FILE *stat_file = fopen(stat_path, "r");
    char tgpid[100];
    if (stat_file == NULL)
    {
        perror("fopen");
        return;
    }
    int count = 0;
    while (count < 8 && fscanf(stat_file, "%s", tgpid) == 1)
        count++;
    int ch = 0;
    for (int i = 0; i < strlen(tgpid); i++)
    {
        ch += ((int)tgpid[i] - 48) * pow(10, strlen(tgpid) - 1 - i);
    }
    fclose(stat_file);
    char line[256];
    while (fgets(line, sizeof(line), status_file))
    {
        if (strncmp(line, "State:", 6) == 0)
        {
            if (strstr(line, "R (running)"))
            {
                if (ch == shell_id)
                    printf("Process Status : R+\n");
                else
                    printf("Process Status : R\n");
            }
            else if (strstr(line, "S (sleeping)"))
            {
                if (ch == shell_id)
                    printf("Process Status : S+\n");
                else
                    printf("Process Status : S\n");
            }
            else if (strstr(line, "Z (zombie)"))
            {
                if (ch == shell_id)
                    printf("Process Status : Z+\n");
                else
                    printf("Process Status : Z\n");
            }
            else
            {
                printf("Unknown State\n");
            }
            break;
        }
    }
    fclose(status_file);
    int pgid = getpgid(shell_id);
    printf("Process Group : %d\n", pgid);
    char vm_contents[64];
    char vm_formatted[20];
    sprintf(vm_contents, "/proc/%d/statm", shell_id);

    FILE *vm_file = fopen(vm_contents, "r");
    if (vm_file == NULL)
    {
        perror("Failed to open statm file");
        return;
    }

    off_t virtual_memory;
    fscanf(vm_file, "%ld", &virtual_memory);
    fclose(vm_file);

    format_size(virtual_memory * getpagesize(), vm_formatted);
    printf("Virtual Memory : %s\n", vm_formatted);
    char exe_path[1024];
    char exe_realpath[1024];
    sprintf(exe_path, "/proc/%d/exe", shell_id);
    ssize_t exe_length = readlink(exe_path, exe_realpath, sizeof(exe_realpath) - 1);
    if (exe_length == -1)
    {
        perror("Failed to read executable path");
        return;
    }
    exe_realpath[exe_length] = '\0';
    int index = strlen(Dir->homed);
    for (int i = 0; i < strlen(Dir->homed); i++)
    {
        if (exe_realpath[i] != Dir->homed[i])
        {
            index = i;
            break;
        }
    }
    if (index < strlen(Dir->homed))
        printf("Executable path : %s\n", exe_realpath);
    else
    {
        char tobepri[1024];
        tobepri[0] = '~';
        for (int i = strlen(Dir->homed); i < strlen(exe_realpath); i++)
        {
            tobepri[i - strlen(Dir->homed) + 1] = exe_realpath[i];
        }
        tobepri[strlen(exe_realpath) - strlen(Dir->homed) + 1] = '\0';
        printf("Executable Path : %s\n", tobepri);
    }
}
void process_info(int pid, direc *Dir)
{
    int shell_id = pid;
    // printf("%d\n",shell_id);
    printf("pid : %d\n", shell_id);
    int status;
    waitpid(shell_id, &status, 0);
    // printf("%d\n",status);
    char proc_status_path[256];
    snprintf(proc_status_path, sizeof(proc_status_path), "/proc/%d/status", shell_id);

    FILE *status_file = fopen(proc_status_path, "r");
    if (status_file == NULL)
    {
        perror("fopen");
        return;
    }
    char stat_path[256];
    snprintf(stat_path, sizeof(stat_path), "/proc/%d/stat", shell_id);
    FILE *stat_file = fopen(stat_path, "r");
    char tgpid[100];
    if (stat_file == NULL)
    {
        perror("fopen");
        return;
    }
    int count = 0;
    while (count < 8 && fscanf(stat_file, "%s", tgpid) == 1)
        count++;
    int ch = 0;
    for (int i = 0; i < strlen(tgpid); i++)
    {
        ch += ((int)tgpid[i] - 48) * pow(10, strlen(tgpid) - 1 - i);
    }
    fclose(stat_file);
    char line[256];
    while (fgets(line, sizeof(line), status_file))
    {
        if (strncmp(line, "State:", 6) == 0)
        {
            if (strstr(line, "R (running)"))
            {
                if (ch == shell_id)
                    printf("Process Status : R+\n");
                else
                    printf("Process Status : R\n");
            }
            else if (strstr(line, "S (sleeping)"))
            {
                if (ch == shell_id)
                    printf("Process Status : S+\n");
                else
                    printf("Process Status : S\n");
            }
            else if (strstr(line, "Z (zombie)"))
            {
                if (ch == shell_id)
                    printf("Process Status : Z+\n");
                else
                    printf("Process Status : Z\n");
            }
            else
            {
                printf("Unknown State\n");
            }
            break;
        }
    }
    fclose(status_file);
    int pgid = getpgid(shell_id);
    printf("Process Group : %d\n", pgid);
    char vm_contents[64];
    char vm_formatted[20];
    sprintf(vm_contents, "/proc/%d/statm", shell_id);

    FILE *vm_file = fopen(vm_contents, "r");
    if (vm_file == NULL)
    {
        perror("Failed to open statm file");
        return;
    }

    off_t virtual_memory;
    fscanf(vm_file, "%ld", &virtual_memory);
    fclose(vm_file);

    format_size(virtual_memory * getpagesize(), vm_formatted);
    printf("Virtual Memory : %s\n", vm_formatted);
    char exe_path[1024];
    char exe_realpath[1024];
    sprintf(exe_path, "/proc/%d/exe", shell_id);
    ssize_t exe_length = readlink(exe_path, exe_realpath, sizeof(exe_realpath) - 1);
    if (exe_length == -1)
    {
        perror("Failed to read executable path");
        return;
    }
    exe_realpath[exe_length] = '\0';
    int index = strlen(Dir->homed);
    for (int i = 0; i < strlen(Dir->homed); i++)
    {
        if (exe_realpath[i] != Dir->homed[i])
        {
            index = i;
            break;
        }
    }
    if (index < strlen(Dir->homed))
        printf("Executable path : %s\n", exe_realpath);
    else
    {
        char tobepri[1024];
        tobepri[0] = '~';
        for (int i = strlen(Dir->homed); i < strlen(exe_realpath); i++)
        {
            tobepri[i - strlen(Dir->homed) + 1] = exe_realpath[i];
        }
        tobepri[strlen(exe_realpath) - strlen(Dir->homed) + 1] = '\0';
        printf("Executable Path : %s\n", tobepri);
    }
}