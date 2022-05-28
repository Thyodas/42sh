/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** setvars
*/

#include "shell.h"
#include "my.h"

void extend_array(char ***array, char *new_line);
int cmp(const void *str_a, const void *str_b);

char *remove_line_spaces(sh_data_t *data, int *i)
{
    char *cmd;
    if (data->current_command->argv[*i + 1] != NULL &&
    data->current_command->argv[*i + 2] != NULL) {
        if (my_strlen(data->current_command->argv[*i + 1]) == 1 &&
        data->current_command->argv[*i + 1][0] == '=') {
            int len = my_strlen(data->current_command->argv[*i]) +
                my_strlen(data->current_command->argv[*i + 1]) +
                my_strlen(data->current_command->argv[*i + 2]);
            cmd = malloc(sizeof(char) * (len + 1));
            for (int j = 0; j < len; cmd[j] = 0, j++);
            cmd = my_strcat(cmd, data->current_command->argv[*i]);
            cmd = my_strcat(cmd, data->current_command->argv[*i + 1]);
            cmd = my_strcat(cmd, data->current_command->argv[*i + 2]);
            *i += 2;
        } else
            cmd = my_strdup(data->current_command->argv[*i]);
    } else
        cmd = my_strdup(data->current_command->argv[*i]);
    return (cmd);
}

char **handling_spaces(sh_data_t *data)
{
    char **array = malloc(sizeof(char *));
    char *cmd;

    array[0] = NULL;
    for (int i = 0; data->current_command->argv[i] != NULL; i++) {
        cmd = remove_line_spaces(data, &i);
        extend_array(&array, my_strdup(cmd));
        free(cmd);
    }
    return (array);
}

void set_var_value(sh_data_t *data, char *name, char *value)
{
    int pos = get_var_line_pos(data, name);
    char *new_line = create_var_line(name, value);
    int ctr = 0;
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
    for (; data->vars[ctr] != NULL; ctr++);
    qsort(data->vars, ctr, sizeof(char *), cmp);
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
    }
    return (error);
}

int builtin_set(sh_data_t *data)
{
    char *val;

    if (data->current_command->argc == 1) {
        for (int i = 0 ; data->vars[i] != NULL ; ++i)
            my_printf("%s\n", data->vars[i]);
        return (0);
    }
    data->current_command->argv = handling_spaces(data);
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
