/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** retrieve_io
*/

#include "my.h"
#include "shell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int retrieve_io_input_line(sh_data_t *data);
int retrieve_io_output_pipe(sh_data_t *data);
int retrieve_io_input_pipe(sh_data_t *data);
int retrieve_io_input(sh_data_t *data);
int retrieve_io_output(sh_data_t *data);
int retrieve_io_output_append(sh_data_t *data);
int retrieve_io_input(sh_data_t *data);

int (*const IO_RETRIEVE[])(sh_data_t *data) = {
    &retrieve_io_output_append,
    &retrieve_io_output,
    &retrieve_io_input_line,
    &retrieve_io_input,
    &retrieve_io_output_pipe,
    &retrieve_io_input_pipe
};

int retrieve_io_output(sh_data_t *data)
{
    data->current_command->write_fd = open(data->current_command->output_option,
        O_WRONLY | O_CREAT | O_TRUNC,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (data->current_command->write_fd == -1) {
        perror(data->current_command->output_option);
        return 1;
    }
    return 0;
}

int retrieve_io_output_append(sh_data_t *data)
{
    data->current_command->write_fd = open(data->current_command->output_option,
        O_WRONLY | O_CREAT | O_APPEND,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (data->current_command->write_fd == -1) {
        perror(data->current_command->output_option);
        return 1;
    }
    return 0;
}

int retrieve_io_input(sh_data_t *data)
{
    data->current_command->read_fd = open(data->current_command->input_option,
        O_RDONLY);
    if (data->current_command->read_fd == -1) {
        perror(data->current_command->input_option);
        return 1;
    }
    return 0;
}

int retrieve_io(sh_data_t *data)
{
    command_t *old_start = data->current_command;
    for (command_t *head = data->current_command; head != NULL;
        head = head->pipe_next) {
        data->current_command = head;
        if (data->current_command->input_type != -1
            && IO_RETRIEVE[data->current_command->input_type](data))
            return 1;
        if (data->current_command->output_type != -1
            && IO_RETRIEVE[data->current_command->output_type](data))
            return 1;
    }
    data->current_command = old_start;
    return 0;
}
