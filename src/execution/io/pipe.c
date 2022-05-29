/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** pipe
*/

#include "my.h"
#include "shell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void execute_command(sh_data_t *data);

int retrieve_io_output_pipe(sh_data_t *data)
{
    if (data->current_command->pipe_prev == NULL
        || data->current_command->pipe_prev->argc == 0) {
        my_fprintf(2, "Invalid null command.\n");
        return 1;
    }
    return 0;
}

int retrieve_io_input_pipe(sh_data_t *data)
{
    if (data->current_command->pipe_next == NULL
        || data->current_command->pipe_next->argc == 0) {
        my_fprintf(2, "Invalid null command.\n");
        return 1;
    }
    return 0;
}

void close_other_pipe(sh_data_t *data)
{
    if (data->current_command->output_type == T_OUTPUT_PIPE)
        close(data->current_command->pipe_prev->read_fd);
    if (data->current_command->input_type == T_INPUT_PIPE)
        close(data->current_command->pipe_next->write_fd);
}

void close_current_pipe(sh_data_t *data)
{
    if (data->current_command->output_type == T_OUTPUT_PIPE)
        close(data->current_command->write_fd);
    if (data->current_command->input_type == T_INPUT_PIPE)
        close(data->current_command->read_fd);
}

void execute_pipe_next(sh_data_t *data)
{
    if (data->current_command->pipe_next != NULL) {
        int pipe_fd[2];
        if (pipe(pipe_fd) == -1) {
            perror("pipe");
            exit(1);
        }
        data->current_command->read_fd = pipe_fd[0];
        data->current_command->pipe_next->write_fd = pipe_fd[1];
        data->child_pid = fork();
        signal(SIGINT, SIG_DFL);
        if (data->child_pid == -1)
            exit(1);
        if (data->child_pid == 0) {
            close(pipe_fd[0]);
            data->current_command = data->current_command->pipe_next;
            execute_command(data);
            exit(0);
        }
        close(pipe_fd[1]);
    }
}
