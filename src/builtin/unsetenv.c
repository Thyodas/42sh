/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** unsetenv
*/

#include "shell.h"
#include "my.h"

void unset_env_value(sh_data_t *data, char *name)
{
    int pos = get_env_line_pos(data, name);
    if (pos == -1)
        return;
    int size = get_env_size(data);
    int new_pos = 0;
    char **new_env = malloc(sizeof(char *) * size);
    for (int i = 0 ; i < pos ; ++i)
        new_env[new_pos++] = data->envp[i];
    for (int j = pos + 1 ; j < size ; ++j)
        new_env[new_pos++] = data->envp[j];
    new_env[new_pos] = NULL;
    free(data->envp[pos]);
    free(data->envp);
    data->envp = new_env;
}

int builtin_unsetenv(sh_data_t *data)
{
    if (data->current_command->argc == 1) {
        my_fprintf(2, "unsetenv: Too few arguments.\n");
        return (1);
    }
    for (int i = 1 ; i < data->current_command->argc ; ++i) {
        if (my_strcmp(data->current_command->argv[i], "PATH") == 0) {
            free(data->old_path);
            data->old_path = my_strdup(get_env_value(data, "PATH"));
        }
        unset_env_value(data, data->current_command->argv[i]);
    }
    return (0);
}
