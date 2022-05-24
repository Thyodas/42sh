/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** setvars
*/

#include "shell.h"
#include "my.h"

void set_var_value(sh_data_t *data, char *name, char *value)
{
    int pos = get_var_line_pos(data, name);
    char *new_line = create_var_line(name, value);
    if (pos == -1) {
        int size = get_var_size(data);
        char **new_var_array = malloc(sizeof(char *) * (size + 2));
        for (int i = 0 ; data->vars[i] != NULL ; ++i)
            new_var_array[i] = data->vars[i];
        new_var_array[size] = new_line;
        new_var_array[size + 1] = NULL;
        data->vars = new_var_array;
    } else {
        free(data->vars[pos]);
        data->vars[pos] = new_line;
    }
}

int check_set(sh_data_t *data)
{
    int error = 0;

    for (int i = 1; data->current_command->argv[i] != NULL ; i++) {
        char *str = data->current_command->argv[i];
        if (('a' > str[0] || str[0] > 'z')
        && ('A' > str[0] || str[0] > 'Z') && str[0] != '_') {
            error == 0 ? my_fprintf(2, "set: Variable name must begin \
with a letter.\n") : 0;
            error = 1;
            data->current_command->argv[i] = "";
        }
        if (my_strstr(str, "\t") != NULL) {
            error == 0 ? my_fprintf(2, "set: Variable name must contain \
alphanumeric characters.\n") : 0;
            error = 1;
            data->current_command->argv[i] = "";
        }
    }
    return (0);
}

int builtin_set(sh_data_t *data)
{
    char *val;

    if (data->current_command->argc == 1) {
        for (int i = 0 ; data->vars[i] != NULL ; ++i)
            my_printf("%s\n", data->vars[i]);
        return (0);
    }
    int check = check_set(data);
    if (check)
        return (check);
    for (int i = 1; data->current_command->argv[i] != NULL ; i++) {
        if ((val = my_strstr(data->current_command->argv[i], "=")) != NULL) {
            val[0] = '\0';
            set_var_value(data, data->current_command->argv[i], &val[1]);
        } else
            set_var_value(data, data->current_command->argv[i], "");
    }

    return (0);
}
