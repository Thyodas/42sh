/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** builtin_utils
*/

#include "shell.h"
#include "my.h"

builtin_t search_builtin(sh_data_t *data)
{
    for (long unsigned int i = 0 ; i < BUILTIN_NB ; ++i) {
        if (my_strcmp(BUILTIN_JUMP_TABLE[i].name,
            data->current_command->argv[0]) == 0)
            return (BUILTIN_JUMP_TABLE[i]);
    }
    return ((builtin_t) {0});
}
