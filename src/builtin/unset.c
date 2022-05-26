/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** unsetvar
*/

#include "shell.h"
#include "my.h"

void unset_var_value(sh_data_t *data, char *name)
{
    int pos = get_var_line_pos(data, name);
    if (pos == -1)
        return;
    int size = get_var_size(data);
    int new_pos = 0;
    char **new_var_array = malloc(sizeof(char *) * size);
    for (int i = 0 ; i < pos ; ++i)
        new_var_array[new_pos++] = data->vars[i];
    for (int j = pos + 1 ; j < size ; ++j)
        new_var_array[new_pos++] = data->vars[j];
    new_var_array[new_pos] = NULL;
    free(data->vars[pos]);
    free(data->vars);
    data->vars = new_var_array;
}

int builtin_unset(sh_data_t *data)
{
    if (data->current_command->argc == 1) {
        my_fprintf(2, "unset: Too few arguments.\n");
        return (1);
    }
    for (int i = 1 ; i < data->current_command->argc ; ++i) {
        if (my_strcmp(data->current_command->argv[i], "PATH") == 0) {
            free(data->old_path);
            data->old_path = my_strdup(get_var_value(data, "PATH"));
        }
        unset_var_value(data, data->current_command->argv[i]);
    }
    return (0);
}
