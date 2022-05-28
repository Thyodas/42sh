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

char *clean_str(char *str)
{
    char *res = malloc(sizeof(char) * (my_strlen(str) + 1));
    int a = 0;

    for (int i = 0; i < my_strlen(str); res[i++] = 0);
    while (str[0] == '\t' || str[0] == ' ')
        str++;
    for (int i = 0; str[i] != '\0'; i++) {
        (str[i] == ' ' || str[i] == '\t') ?
        (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0') ?
        0 : (1 == 1) ? res[a++] = ' ' : 0 : (1 == 1) ? res[a++] = str[i] : 0;
    }
    res[a] = '\0';
    return (res);
}

char *reformat(char *str)
{
    char *res;

    for (int i = 0; str[i] != '\0'; i++)
        str[i] = str[i] == '\n' ? ' ' : str[i];
    str[my_strlen(str) - 1] = '\0';
    res = clean_str(str);
    return (res);
}

char **dup_array(char **array)
{
    char **res;
    int i = 0;

    while (array[i] != NULL)
        i++;
    res = malloc(sizeof(char *) * i);
    for(int j = 0; j < i; j++)
        res[j] = strdup(array[j]);
    res[i] = NULL;
    return (res);
}

char *get_backticks_value(sh_data_t *data, char *cmd)
{
    int fd[2];
    int message_size = 1024;
    char buffer[message_size];
    int old_out = dup(STDOUT_FILENO);
    ssize_t size;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }
    cmd[my_strlen(cmd) - 1] = '\0';
    cmd = &cmd[1];
    close(STDOUT_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    parse_current_line(data, cmd);
    close(fd[1]);
    if (data->last_exit_status == 0) {
        size = read(fd[0], buffer, message_size);
        buffer[size] = '\0';
    } else
        buffer[0] = '\0';
    close(fd[0]);
    close(STDOUT_FILENO);
    dup2(old_out, STDOUT_FILENO);
    close(old_out);
    return (my_strdup(buffer));
}

void handle_backtick(sh_data_t *data)
{
    char *str;
    char **oldlines = dup_array(data->line);

    for (int i = 0; data->line[i]; i++) {
        if (data->line[i][0] == '`') {
            str = get_backticks_value(data, my_strdup(data->line[i]));
            free(oldlines[i]);
            str = reformat(str);
            oldlines[i] = my_strdup(str);
        }
    }
    data->line = oldlines;
}
