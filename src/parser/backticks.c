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

static void close_dup(int a, int b)
{
    close(b);
    dup2(a, b);
    close(a);
}

static char *sheitan_part(sh_data_t *data, char *cmd, int old_out, int fd[2])
{
    int message_size = 1024;
    char buffer[message_size];
    ssize_t size;

    cmd[my_strlen(cmd) - 1] = '\0';
    cmd = &cmd[1];
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

int handle_backtick(sh_data_t *data)
{
    char *str;
    char **oldlines = dup_array(data->line);
    int exit_status = 0;

    for (int i = 0; oldlines[i]; i++) {
        if (oldlines[i][0] == '`') {
            str = get_backticks_value(data, my_strdup(oldlines[i]));
            free(oldlines[i]);
            str = reformat(str);
            oldlines[i] = my_strdup(str);
            exit_status = data->last_exit_status;
        }
    }
    data->line = oldlines;
    return (exit_status);
}
