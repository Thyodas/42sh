/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** var_substitute.c
*/

#include "my.h"
#include "shell.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

static char *get_value(sh_data_t *data, char *var)
{
    char *value;

    var = my_strlen(var) == 2 && var[1] == '?' ? "$status" : var;
    value = get_var_value(data, &var[1]);
    if (!value)
        value = get_env_value(data, &var[1]);
    if (!value) {
        my_fprintf(2, "%s: Undefined variable.\n", &var[1]);
        return (NULL);
    }
    return (value);
}

void handle_home(sh_data_t *data, int *i)
{
    char *new_cmd;
    int len;
    struct passwd *pw = getpwuid(getuid());
    char *value = pw->pw_dir;

    if (!value)
        return;
    for (int j = 0; data->line[*i][j] != '\0'; j++) {
        if (data->line[*i][j] == '~') {
            len = (my_strlen(data->line[*i]) - 1 +
            my_strlen(value));
            new_cmd = malloc(sizeof(char) * (len + 1));
            for (int j = 0; j < len + 1; new_cmd[j] = 0, j++);
            my_strncpy(new_cmd, data->line[*i], len - my_strlen(value));
            my_strcat(new_cmd, value);
            free(data->line[*i]);
            data->line[*i] = my_strdup(new_cmd);
            free(new_cmd);
        }
    }
}

int substitution(sh_data_t *data, int *i)
{
    char *variable;
    char *new_cmd;
    int len;
    handle_home(data, i);
    if ((variable = my_strstr(data->line[*i], "$")) != NULL) {
        char *value = get_value(data, variable);
        if (!value)
            return (1);
        len = (my_strlen(data->line[*i]) - my_strlen(variable) +
            my_strlen(value));
        new_cmd = malloc(sizeof(char) * (len + 1));
        for (int j = 0; j < len + 1; new_cmd[j] = 0, j++);
        my_strncpy(new_cmd, data->line[*i], len - my_strlen(value));
        my_strcat(new_cmd, value);
        free(data->line[*i]);
        data->line[*i] = my_strdup(new_cmd);
        free(new_cmd);
    }
    return (0);
}

int var_substitute(sh_data_t *data)
{
    for (int i = 0; data->line[i] != NULL; i++) {
        if (substitution(data, &i))
            return (1);
    }
    return (0);
}