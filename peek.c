#include "headers.h"
// #include <sys/stat.h>

int compare_entries(const struct dirent **a, const struct dirent **b)
{
    return alphasort(a, b);
}
void printPermissions(mode_t mode)
{
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

void printFileInfo(const char *path, const struct stat *sb)
{
    struct passwd *pw = getpwuid(sb->st_uid);
    struct group *gr = getgrgid(sb->st_gid);
    struct tm *timeinfo = localtime(&(sb->st_mtime));

    printf("%10s ", pw->pw_name);
    printf("%10s ", gr->gr_name);
    printf("%8lld ", (long long)sb->st_size);
    printf("%.12s ", ctime(&(sb->st_mtime)) + 4);
}
void peek_call(direc *Dir, char *peekd)
{
    if (peekd[5] == '-' && peekd[6] == 'a' && peekd[8] != '-' && peekd[7] != 'l')
    {
        char *peek_dir = (char *)malloc(sizeof(char) * 256);
        strcpy(peek_dir, Dir->present);
        char *temp = (char *)malloc(sizeof(char) * 256);
        for (int i = 8; i < strlen(peekd); i++)
        {
            temp[i - 8] = peekd[i];
        }
        int len = strlen(peekd);
        if (len - 8 <= 0)
        {
            temp[0] = '\0';
        }
        else if (len - 8 > 0)
        {
            temp[strlen(peekd) - 8] = '\0';
            strncat(peek_dir, "/", 10);
            if (peekd[8] != '/')
                strncat(peek_dir, temp, 256);
            else
                strcpy(peek_dir, temp);
        }
        struct dirent **entry_list;
        int num_entries;

        num_entries = scandir(peek_dir, &entry_list, NULL, compare_entries);
        if (num_entries == -1)
        {
            perror("scandir");
            return;
        }

        for (int i = 0; i < num_entries; i++)
        {
            char full_path[257];
            snprintf(full_path, sizeof(full_path), "%s/%s", peek_dir, entry_list[i]->d_name);

            struct stat sb;
            if (stat(full_path, &sb) == 0)
            {
                if (S_ISDIR(sb.st_mode))
                    printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, entry_list[i]->d_name);
                else if ((sb.st_mode & S_IXUSR) || (sb.st_mode & S_IXGRP) || (sb.st_mode & S_IXOTH))
                    printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, entry_list[i]->d_name);
                else
                    printf("%s\n", entry_list[i]->d_name);
            }
            free(entry_list[i]);
        }

        free(entry_list);
    }
    else if (peekd[5] == '-' && peekd[6] == 'l' && peekd[8] != '-' && peekd[7] != 'a')
    {
        char *peek_dir = (char *)malloc(sizeof(char) * 256);
        strcpy(peek_dir, Dir->present);
        char *temp = (char *)malloc(sizeof(char) * 256);
        for (int i = 8; i < strlen(peekd); i++)
        {
            temp[i - 8] = peekd[i];
        }
        int len = strlen(peekd);
        if (len - 8 <= 0)
        {
            temp[0] = '\0';
        }
        else if (len - 8 > 0)
        {
            temp[strlen(peekd) - 8] = '\0';
            strncat(peek_dir, "/", 10);
            if (peekd[8] != '/')
                strncat(peek_dir, temp, 256);
            else
                strcpy(peek_dir, temp);
        }
        struct dirent **entry_list;
        int num_entries;

        num_entries = scandir(peek_dir, &entry_list, NULL, compare_entries);
        if (num_entries == -1)
        {
            perror("scandir");
            return;
        }

        // printf("Permissions  Links  Owner      Group      Size       Modified Time  Name\n");
        for (int i = 0; i < num_entries; i++)
        {
            if (entry_list[i]->d_name[0] != '.')
            {
                char full_path[257];
                snprintf(full_path, sizeof(full_path), "%s/%s", peek_dir, entry_list[i]->d_name);

                struct stat sb;
                if (stat(full_path, &sb) == 0)
                {
                    printPermissions(sb.st_mode);
                    printf("%4ld ", (long)sb.st_nlink);
                    printFileInfo(full_path, &sb);
                    if (S_ISDIR(sb.st_mode))
                        printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, entry_list[i]->d_name);
                    else if ((sb.st_mode & S_IXUSR) || (sb.st_mode & S_IXGRP) || (sb.st_mode & S_IXOTH))
                        printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, entry_list[i]->d_name);
                    else
                        printf("%s\n", entry_list[i]->d_name);
                }
            }
            free(entry_list[i]);
        }

        free(entry_list);
    }
    else if (peekd[5] == '-')
    {
        char *peek_dir = (char *)malloc(sizeof(char) * 256);
        strcpy(peek_dir, Dir->present);
        char *temp = (char *)malloc(sizeof(char) * 256);
        if (peekd[5] == '-' && peekd[8] == '-')
        {
            for (int i = 11; i < strlen(peekd); i++)
            {
                temp[i - 11] = peekd[i];
            }
            int len = strlen(peekd);
            if (len - 11 <= 0)
            {
                temp[0] = '\0';
            }
            else if (len - 11 > 0)
            {
                temp[strlen(peekd) - 11] = '\0';
                strncat(peek_dir, "/", 10);
                if (peekd[11] != '/')
                    strncat(peek_dir, temp, 256);
                else
                    strcpy(peek_dir, temp);
            }
        }
        else
        {
            for (int i = 9; i < strlen(peekd); i++)
            {
                temp[i - 9] = peekd[i];
            }
            int len = strlen(peekd);
            if (len - 9 <= 0)
            {
                temp[0] = '\0';
            }
            else if (len - 9 > 0)
            {
                temp[strlen(peekd) - 9] = '\0';
                strncat(peek_dir, "/", 10);
                if (peekd[9] != '/')
                    strncat(peek_dir, temp, 256);
                else
                    strcpy(peek_dir, temp);
            }
        }
        struct dirent **entry_list;
        int num_entries;

        num_entries = scandir(peek_dir, &entry_list, NULL, compare_entries);
        if (num_entries == -1)
        {
            perror("scandir");
            return;
        }

        // printf("Permissions  Links  Owner      Group      Size       Modified Time  Name\n");
        for (int i = 0; i < num_entries; i++)
        {
            // if (entry_list[i]->d_name[0] != '.')
            {
                char full_path[257];
                snprintf(full_path, sizeof(full_path), "%s/%s", peek_dir, entry_list[i]->d_name);

                struct stat sb;
                if (stat(full_path, &sb) == 0)
                {
                    printPermissions(sb.st_mode);
                    printf("%4ld ", (long)sb.st_nlink);
                    printFileInfo(full_path, &sb);
                    if (S_ISDIR(sb.st_mode))
                        printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, entry_list[i]->d_name);
                    else if ((sb.st_mode & S_IXUSR) || (sb.st_mode & S_IXGRP) || (sb.st_mode & S_IXOTH))
                        printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, entry_list[i]->d_name);
                    else
                        printf("%s\n", entry_list[i]->d_name);
                }
            }
            free(entry_list[i]);
        }

        free(entry_list);
    }
    else
    {
        char *peek_dir = (char *)malloc(sizeof(char) * 256);
        strcpy(peek_dir, Dir->present);
        char *temp = (char *)malloc(sizeof(char) * 256);
        for (int i = 5; i < strlen(peekd); i++)
        {
            temp[i - 5] = peekd[i];
        }
        temp[strlen(peekd) - 5] = '\0';
        strncat(peek_dir, "/", 10);
        if (peekd[5] != '/')
            strncat(peek_dir, temp, 256);
        else
            strcpy(peek_dir, temp);
        struct dirent **entry_list;
        int num_entries;

        num_entries = scandir(peek_dir, &entry_list, NULL, compare_entries);
        if (num_entries == -1)
        {
            perror("scandir");
            return;
        }

        // printf("Permissions  Links  Owner      Group      Size       Modified Time  Name\n");
        for (int i = 0; i < num_entries; i++)
        {
            if (entry_list[i]->d_name[0] != '.')
            {
                char full_path[257];
                snprintf(full_path, sizeof(full_path), "%s/%s", peek_dir, entry_list[i]->d_name);

                struct stat sb;
                if (stat(full_path, &sb) == 0)
                {
                    // printPermissions(sb.st_mode);
                    // printf("%4ld ", (long)sb.st_nlink);
                    // printFileInfo(full_path, &sb);
                    if (S_ISDIR(sb.st_mode))
                        printf(ANSI_COLOR_BLUE "%s\n" ANSI_COLOR_RESET, entry_list[i]->d_name);
                    else if ((sb.st_mode & S_IXUSR) || (sb.st_mode & S_IXGRP) || (sb.st_mode & S_IXOTH))
                        printf(ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, entry_list[i]->d_name);
                    else
                        printf("%s\n", entry_list[i]->d_name);
                }
            }
            free(entry_list[i]);
        }

        free(entry_list);
    }
}