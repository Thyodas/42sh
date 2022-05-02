/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** env
*/

#include "shell.h"
#include "my.h"

int builtin_env(sh_data_t *data)
{
    if (data->current_command->argc != 1) {
        my_fprintf(2, "env: Too many arguments.\n");
        return (1);
    }
    for (int i = 0 ; data->envp[i] != NULL ; ++i)
        my_printf("%s\n", data->envp[i]);
    return (0);
}
