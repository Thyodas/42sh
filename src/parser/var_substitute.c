/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** var_substitute.c
*/

#include "my.h"
#include "shell.h"

static char *get_value(sh_data_t *data, char *var)
{
    char *value;

    value = get_var_value(data, &var[1]);
    if (!value)
        value = get_env_value(data, &var[1]);
    if (!value) {
        my_fprintf(2, "%s: Undefined variable.\n", &var[1]);
        return (NULL);
    }
    return (value);
}

void var_substitute(sh_data_t *data)
{
    char *variable;
    char *value;
    char *new_cmd;
    int len;

    for (int i = 0; data->line[i] != NULL; i++) {
        if ((variable = my_strstr(data->line[i], "$")) != NULL) {
            value = get_value(data, variable);
            len = (my_strlen(data->line[i]) - my_strlen(variable) +
                my_strlen(value));
            new_cmd = malloc(sizeof(char) * (len + 1));
            for (int j = 0; j < len + 1; new_cmd[j] = 0, j++);
            my_strncpy(new_cmd, data->line[i], len - my_strlen(value));
            my_strcat(new_cmd, value);
            free(data->line[i]);
            data->line[i] = my_strdup(new_cmd);
            free(new_cmd);
        }
    }
}