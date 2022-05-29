/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** backticks.c
*/

#include "shell.h"
#include "my.h"
#include <sys/stat.h>
#include <fcntl.h>

char *clean_str(char *str);
char *reformat(char *str);
char **dup_array(char **array);
void close_dup(int a, int b);

static char *read_fd(int fd)
{
    char buf[1024] = {0};
    int size;
    int total_size = 0;
    char *previous = NULL;
    char *str = my_strdup("");

    while ((size = read(fd, buf, 1024))) {
        previous = str;
        str = malloc(total_size + size + 1);
        my_strncpy(str, previous, total_size);
        my_strncpy(str + total_size, buf, size);
        total_size += size;
        str[total_size] = '\0';
        free(previous);
    }
    return (str);
}

static char *sheitan_part(sh_data_t *data, char *cmd, int old_out, int fd[2])
{
    char *buffer;

    int pid = fork();
    if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], 1);
        parse_current_line(data, cmd);
        close(fd[1]);
        exit(0);
    } else {
        close(fd[1]);
        buffer = read_fd(fd[0]);
        close(fd[0]);
    }
    return (buffer);
}

char *get_backticks_value(sh_data_t *data, char *cmd)
{
    int fd[2];
    int old_out = dup(STDOUT_FILENO);
    char *out;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }
    out = sheitan_part(data, cmd, old_out, fd);
    return (out);
}

static char *getbline(sh_data_t *data, char *cmd, char *first, char *second)
{
    char *str;
    int len;
    char *res;

    str = get_backticks_value(data, my_strdup(cmd));
    str = reformat(str);
    len = my_strlen(str) + my_strlen(first) + my_strlen(second);
    res = malloc(sizeof(char) * (len + 1));
    for (int j = 0; j <= len; res[j] = 0, j++);
    res = my_strcat(my_strcat(my_strcat(res, first), str), second);
    return (my_strdup(res));
}

static int find_backticks(sh_data_t *data, char **oldlines, int i)
{
    char *cmd;
    char *cmd_end;
    char *first;
    char *second;

    first = my_strdup(oldlines[i]);
    if ((cmd = my_strstr(first, "`"))) {
        cmd[0] = '\0';
        cmd = my_strdup(&cmd[1]);
        if ((cmd_end = my_strstr(cmd, "`"))) {
            second = my_strlen(cmd_end) > 1 ? &cmd_end[1] : my_strdup("");
            cmd_end[0] = '\0';
        }
        free(oldlines[i]);
        oldlines[i] = getbline(data, cmd, first, second);
        return (data->last_exit_status);
    }
    return (0);
}

int handle_backtick(sh_data_t *data)
{
    char **oldlines = dup_array(data->line);
    int exit_status = 0;

    for (int i = 0; oldlines[i]; i++)
        exit_status = find_backticks(data, oldlines, i);
    data->line = oldlines;
    return (exit_status);
}
