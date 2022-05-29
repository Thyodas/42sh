/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** exec_utils.c
*/

#include "my.h"
#include "shell.h"

void handle_pid(sh_data_t *data, int status)
{
    data->current_command->pid = data->child_pid;
    waitpid(data->child_pid, &status, WUNTRACED);
    if (WIFSTOPPED(status))
        my_add_node(data->current_command, &data->suspended_command);
    else
        binary_error(data, status);
}