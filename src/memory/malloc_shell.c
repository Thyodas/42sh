/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** mem_shell2.c
*/

#include "shell.h"

command_t *malloc_command(void)
{
    command_t *command = malloc(sizeof(command_t));
    command->argv = malloc(sizeof(char *));
    command->argv[0] = NULL;
    command->argc = 0;
    command->read_fd = 0;
    command->write_fd = 1;
    command->input_type = -1;
    command->output_type = -1;
    command->pipe_next = NULL;
    command->pipe_prev = NULL;
    return command;
}
