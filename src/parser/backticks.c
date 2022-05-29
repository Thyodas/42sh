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

static char *sheitan_part(sh_data_t *data, char *cmd, int old_out, int fd[2])
{
    int message_size = 1024;
    char buffer[message_size];
    ssize_t size;

    close_dup(fd[1], STDOUT_FILENO);
    parse_current_line(data, cmd);
    close(fd[1]);
    if (data->last_exit_status == 0) {
        size = read(fd[0], buffer, message_size);
        buffer[size] = '\0';
    } else
        buffer[0] = '\0';
    close(fd[0]);
    close_dup(old_out, STDOUT_FILENO);
    return (my_strdup(buffer));
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
