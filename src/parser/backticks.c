/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** backticks.c
*/

#include "shell.h"
#include "my.h"

void replace_newline(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        str[i] = str[i] == '\n' ? ' ' : str[i];
    str[my_strlen(str) - 1] = '\0';
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
    int status = 0;

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
    wait(&status);
    close(fd[1]);
    read(fd[0], buffer, message_size);
    close(fd[0]);
    close(STDOUT_FILENO);
    dup2(old_out, STDOUT_FILENO);
    close(old_out);
    return (my_strdup(buffer));
}

void handle_backtick(sh_data_t *data)
{
    char *res;
    char **oldlines = dup_array(data->line);

    for (int i = 0; data->line[i]; i++) {
        if (data->line[i][0] == '`') {
            res = get_backticks_value(data, my_strdup(data->line[i]));
            free(oldlines[i]);
            replace_newline(res);
            oldlines[i] = my_strdup(res);
        }
    }
    data->line = oldlines;
}
