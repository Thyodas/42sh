/*
** EPITECH PROJECT, 2022
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** history_flag
*/

#include "my.h"
#include "shell.h"

int write_in_history_file(sh_data_t *data);
static int history_delete(sh_data_t *data);
int add_in_file(sh_data_t *data);
int n_flag(sh_data_t *data);
int add_from_file_to_history(sh_data_t *data);

int(*ptr[])(sh_data_t *) = {
    history_delete, add_in_file, add_from_file_to_history, n_flag,
    write_in_history_file,
};

static int history_delete(sh_data_t *data)
{
    for (int i = 0; data->history[i] != NULL; i++)
        free(data->history[i]);
    free(data->history);
    data->history = malloc(sizeof(char *));
    data->history[0] = my_strdup("");
    if (data->current_command->argc > 2
    && my_str_isnum(data->current_command->argv[2]) == 0)
        my_fprintf(2, "history: Badly formed number.\n");
    return 0;
}

static char **offset_delete(sh_data_t *data, int line)
{
    int i = 0;
    int len = 0;
    char **new_array = NULL;

    for(; data->history[len] != NULL; len++);
    new_array = malloc(sizeof(char *) * len);
    for(; data->history[i] != NULL; i++) {
        if (i == line)
            continue;
        if (i > line)
            new_array[i - 1] = my_strdup(data->history[i]);
        else
            new_array[i - 1] = my_strdup(data->history[i]);
    }
    return new_array;
}

int add_in_file(sh_data_t *data)
{
    return 0;
}

int add_from_file_to_history(sh_data_t *data)
{
    return 0;
}

int n_flag(sh_data_t *data)
{
    return 0;
}

int write_in_history_file(sh_data_t *data)
{
    return 0;
}

int history_flag(sh_data_t *data)
{
    char flag[] = {'c', 'a', 'n', 'r', 'w', 'p', 's'};

    for (int h = 0; flag[h] != '\0'; h++) {
        if (flag[h] == data->current_command->argv[1][1])
            return ptr[h](data);
    }
    if (my_strcmp(data->current_command->argv[1], "-d") == 0) {
        if (data->current_command->argc == 3 
        && my_str_isnum(data->current_command->argv[2]) == 0) {
            my_fprintf(2, "Usage: history [-chrSLMT] [# number of events].\n");
            return 1;
        }
        if (data->current_command->argc > 3) {
            my_fprintf(2, "history: Too many arguments.\n");
            return 1;
        }
        if (data->current_command->argc == 2) {
            my_fprintf(2, "Usage: history [-chrSLMT] [# number of events].\n");
            return 1;
        }
        data->history = offset_delete(data, my_getnbr(data->current_command->argv[3]));
        return 0;
    }
    if (data->current_command->argc >= 2) {
        my_fprintf(2, "history: Badly formed number.\n");
        return 1;
    }
    return 0;
}