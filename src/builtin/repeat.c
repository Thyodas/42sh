/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** repeat
*/

#include "shell.h"
#include "my.h"

void execute_command(sh_data_t *data);

int builtin_repeat(sh_data_t *data)
{
    if (data->current_command->argc <= 2) {
        my_fprintf(2, "%s: Too few arguments.\n",
            data->current_command->argv[0]);
        return (1);
    }
    if (!my_str_isnum(data->current_command->argv[1])) {
        my_fprintf(2, "%s: Badly formed number.\n",
            data->current_command->argv[0]);
        return (1);
    }
    int count = my_getnbr(data->current_command->argv[1]);
    data->current_command->argc -= 2;
    data->current_command->argv += 2;
    if (data->current_command->input_type != -1)
        count = 1;
    for (int i = 0 ; i < count ; ++i)
        execute_command(data);
    return (data->last_exit_status);
}
