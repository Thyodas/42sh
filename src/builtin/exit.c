/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** exit
*/

#include "my.h"
#include "shell.h"

void default_shell_exit(void)
{
    my_printf("exit\n");
    exit(0);
}

int builtin_exit(sh_data_t *data)
{
    if (data->current_command->argc > 2
        && !my_str_isnum(data->current_command->argv[1])) {
        my_fprintf(2, "exit: Expression Syntax.");
        return (1);
    }
    if (data->last_exit_status != 0) {
        if (data->is_prompt_mode)
            my_printf("exit\n");
        exit(data->last_exit_status);
    }
    if (data->current_command->argc == 1) {
        if (data->is_prompt_mode)
            my_printf("exit\n");
        exit(0);
    }
    if (data->is_prompt_mode)
        my_printf("exit\n");
    int exit_code = my_getnbr(data->current_command->argv[1]);
    exit(exit_code);
    return (0);
}
