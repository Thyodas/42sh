/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** env
*/

#include "shell.h"
#include "my.h"

int get_env_size(sh_data_t *data)
{
    int i = 0;

    for (; data->envp[i] != NULL ; ++i);
    return (i);
}

int get_env_line_pos(sh_data_t *data, char *name)
{
    int len = my_strlen(name);
    for (int i = 0 ; data->envp[i] != NULL ; ++i) {
        if (my_strncmp(data->envp[i], name, len) == 0
        && data->envp[i][len] == '=')
            return (i);
    }
    return (-1);
}

char *get_env_value(sh_data_t *data, char *name)
{
    int pos = get_env_line_pos(data, name);
    if (pos == -1)
        return (NULL);
    char *line = data->envp[pos];
    line = my_strstr(line, "=");
    if (line == NULL)
        return (NULL);
    else
        return (line + 1);
}

char *create_env_line(char *name, char *value)
{
    int len = my_strlen(name) + my_strlen(value) + 1;
    int pos = 0;
    char *new_str = malloc(sizeof(char) * (len + 1));

    for (int i = 0 ; name[i] != '\0' ; ++i)
        new_str[pos++] = name[i];
    new_str[pos++] = '=';
    for (int j = 0 ; value[j] != '\0' ; ++j)
        new_str[pos++] = value[j];
    new_str[pos] = '\0';
    return (new_str);
}
