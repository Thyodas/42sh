/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** env
*/

#include "shell.h"
#include "my.h"

int cmp(const void *str_a, const void *str_b)
{
    return (my_strcmp(*((char**) str_a), *((char**) str_b)));
}

int get_var_size(sh_data_t *data)
{
    int i = 0;

    for (; data->vars[i] != NULL ; ++i);
    return (i);
}

int get_var_line_pos(sh_data_t *data, char *name)
{
    int len = my_strlen(name);
    for (int i = 0 ; data->vars[i] != NULL ; ++i) {
        if (my_strncmp(data->vars[i], name, len) == 0
        && data->vars[i][len] == '\t')
            return (i);
    }
    return (-1);
}

char *get_var_value(sh_data_t *data, char *name)
{
    int pos = get_var_line_pos(data, name);
    if (pos == -1)
        return (NULL);
    char *line = data->vars[pos];
    line = my_strstr(line, "\t");
    if (line == NULL)
        return (NULL);
    else
        return (line + 1);
}

char *create_var_line(char *name, char *value)
{
    int len = my_strlen(name) + my_strlen(value) + 1;
    int pos = 0;
    char *new_str = malloc(sizeof(char) * (len + 1));

    for (int i = 0 ; name[i] != '\0' ; ++i)
        new_str[pos++] = name[i];
    new_str[pos++] = '\t';
    for (int j = 0 ; value[j] != '\0' ; ++j)
        new_str[pos++] = value[j];
    new_str[pos] = '\0';
    return (new_str);
}
