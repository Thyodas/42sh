/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** setenv
*/

#include "shell.h"
#include "my.h"

void set_env_value(sh_data_t *data, char *name, char *value)
{
    int pos = get_env_line_pos(data, name);
    char *new_line = create_env_line(name, value);
    if (pos == -1) {
        int size = get_env_size(data);
        char **new_env = malloc(sizeof(char *) * (size + 2));
        for (int i = 0 ; data->envp[i] != NULL ; ++i)
            new_env[i] = data->envp[i];
        new_env[size] = new_line;
        new_env[size + 1] = NULL;
        data->envp = new_env;
    } else {
        free(data->envp[pos]);
        data->envp[pos] = new_line;
    }
}

int check_setenv(sh_data_t *data)
{
    if (data->current_command->argc > 3) {
        my_fprintf(2, "setenv: Too many arguments.\n");
        return (1);
    }
    char *str = data->current_command->argv[1];
    if (('a' > str[0] || str[0] > 'z')
    && ('A' > str[0] || str[0] > 'Z') && str[0] != '_') {
        my_fprintf(2, "setenv: Variable name must begin with a letter.\n");
        return (1);
    }
    if (my_strstr(str, "=") != NULL) {
        my_fprintf(2, "setenv: Variable name must contain \
alphanumeric characters.\n");
        return (1);
    }
    return (0);
}

int builtin_setenv(sh_data_t *data)
{
    if (data->current_command->argc == 1) {
        for (int i = 0 ; data->envp[i] != NULL ; ++i)
            my_printf("%s\n", data->envp[i]);
        return (0);
    }
    int check = check_setenv(data);
    if (check)
        return (check);
    if (data->current_command->argc == 2) {
        set_env_value(data, data->current_command->argv[1], "");
    } else
        set_env_value(data, data->current_command->argv[1],
            data->current_command->argv[2]);
    return (0);
}
