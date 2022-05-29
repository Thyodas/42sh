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
command_t *get_command_fg(sh_data_t *data);

static int send_signals(command_t *stored_command)
{
    int status = 0;
    command_t *pipe = stored_command;
    if (pipe->pipe_next == NULL) {
        kill(pipe->pid, SIGCONT);
        waitpid(pipe->pid, &status, WUNTRACED);
        return status;
    }
    while (pipe->pipe_next != NULL)
        pipe = pipe->pipe_next;
    while (pipe->pipe_prev != NULL) {
        kill(pipe->pid, SIGCONT);
        waitpid(pipe->pid, &status, WUNTRACED);
        pipe = pipe->pipe_prev;
    }
    return status;
}

int fg(sh_data_t *data)
{
    if (data->suspended_command == NULL) {
        my_fprintf(2, "fg: No current job.\n");
        return 1;
    }
    command_t *stored_command = get_command_fg(data);
    int status = send_signals(stored_command);
    if (WIFSTOPPED(status))
        my_add_node(stored_command, &data->suspended_command);
    else
        binary_error(data, status);
    return 0;
}
