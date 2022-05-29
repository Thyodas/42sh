/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** exec_utils.c
*/

#include "my.h"
#include "shell.h"
int retrieve_io(sh_data_t *data);
void reset_data(sh_data_t *data);
void execute_command(sh_data_t *data);

void init_command_execution(sh_data_t *data)
{
    reset_data(data);
    if (retrieve_io(data)) {
        data->last_exit_status = 1;
        return;
    }
    execute_command(data);
}

void handle_pid(sh_data_t *data, int status)
{
    data->current_command->pid = data->child_pid;
    waitpid(data->child_pid, &status, WUNTRACED);
    if (WIFSTOPPED(status))
        my_add_node(data->current_command, &data->suspended_command);
    else
        binary_error(data, status);
}
