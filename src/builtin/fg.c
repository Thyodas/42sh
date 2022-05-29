/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** fg.c
*/

#include "my.h"
#include "shell.h"
#include <sys/types.h>
#include <signal.h>
#include "my_list.h"

void binary_error(sh_data_t *data, int status);

static int send_signals(sh_data_t *data, command_t *stored_command)
{
    int status = 0;
    data->suspended_command = data->suspended_command->next;
    command_t *pipe = stored_command;
    while (pipe->pipe_next != NULL)
        pipe = pipe->pipe_next;
    while (pipe->pipe_prev != NULL) {
        kill(pipe->pid, SIGCONT);
        waitpid(pipe->pid, &status, WUNTRACED);
        pipe = pipe->pipe_prev;
    }
    return status;
}

int job_control(sh_data_t *data)
{
    if (data->suspended_command == NULL) {
        my_fprintf(2, "fg: No current job.\n");
        return 1;
    }
    command_t *stored_command = data->suspended_command->data;
    int status = send_signals(data, stored_command);
    if (WIFSTOPPED(status))
        my_add_node(stored_command, &data->suspended_command);
    else
        binary_error(data, status);
    return 0;
}
