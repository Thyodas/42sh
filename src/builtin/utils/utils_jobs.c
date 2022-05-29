/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** utils_jobs.c
*/

#include "my.h"
#include "shell.h"

int size_command_list(sh_data_t *data)
{
    linked_list_t *suspend_list = data->suspended_command;
    int size = 0;
    while (suspend_list != NULL) {
        size++;
        suspend_list = suspend_list->next;
    }
    return size;
}

command_t *get_command_by_index(sh_data_t *data, int index)
{
    int size = size_command_list(data);
    if (index > size || index < 1) {
        my_fprintf(2, "%d: No such process\n");
        return NULL;
    }
    int pos = 1;
    linked_list_t *suspended_list = data->suspended_command;
    command_t *output;
    while (suspended_list != NULL) {
        if (pos == index) {
            output = suspended_list->data;
            return output;
        }
        pos++;
        suspended_list = suspended_list->next;
    }
    return NULL;
}

command_t *get_command_fg(sh_data_t *data)
{
    command_t *current_command = data->current_command;
    command_t *suspended_command;
    if (current_command->argv[1] == NULL ||
        !my_strcmp(current_command->argv[1], "%%") ||
        !my_strcmp(current_command->argv[1], "%+")) {
        suspended_command = data->suspended_command->data;
        data->suspended_command = data->suspended_command->next;
        return suspended_command;
    }
    if (!my_strcmp(current_command->argv[1], "%-")) {
        suspended_command = data->suspended_command->next->data;
        data->suspended_command = data->suspended_command->next->next;
        return suspended_command;
    }
    if (current_command->argv[1][0] == '%' &&
        my_str_isnum(&current_command->argv[1][1]))
        return get_command_by_index(data,
                                    my_getnbr(&current_command->argv[1][1]));
    suspended_command = data->suspended_command->data;
    return suspended_command;
}

command_t *get_command_kill(sh_data_t *data)
{
    command_t *current_command = data->current_command;
    command_t *suspended_command;
    if (!my_strcmp(current_command->argv[1], "%%") ||
        !my_strcmp(current_command->argv[1], "%+")) {
        suspended_command = data->suspended_command->data;
        return suspended_command;
    }
    if (!my_strcmp(current_command->argv[1], "%-")) {
        suspended_command = data->suspended_command->next->data;
        return suspended_command;
    }
    if (current_command->argv[1][0] == '%' &&
        my_str_isnum(&current_command->argv[1][1]))
        return get_command_by_index(data,
                                    my_getnbr(&current_command->argv[1][1]));
    suspended_command = data->suspended_command->data;
    return suspended_command;
}
