/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** token_handlers
*/

#include "my.h"
#include "shell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

special_token_t get_io_token(const special_token_t *token_list, char *str);
command_t *malloc_command(void);

static const special_token_t TOKEN_LIST[] = {
    {">>", 2, NULL},
    {">", 1, NULL},
    {"<<", 2, NULL},
    {"<", 1, NULL},
    {";", 1, NULL},
    {"|", 1, NULL},
    {NULL, 0, NULL}
};

int handle_io_pipe(sh_data_t *data, char **options, bool *error)
{
    if (*options == NULL || data->current_command->argv == 0) {
        my_fprintf(2, "Invalid null command.\n");
        *error = true;
        return 1;
    }
    if (data->current_command->output_type != -1) {
        my_fprintf(2, "Ambiguous output redirect.\n");
        *error = true;
        return 2;
    }
    command_t *new_command = malloc_command();
    data->current_command->output_type = T_OUTPUT_PIPE;
    data->current_command->pipe_prev = new_command;
    new_command->input_type = T_INPUT_PIPE;
    new_command->pipe_next = data->current_command;
    data->current_command = new_command;
    return 1;
}

int handle_io_output(sh_data_t *data, char **options, bool *error)
{
    if (*options == NULL || get_io_token(TOKEN_LIST, *options).size != 0) {
        my_fprintf(2, "Missing name for redirect\n");
        *error = true;
        return *options == NULL ? 1 : 2;
    }
    if (data->current_command->output_type != -1) {
        my_fprintf(2, "Ambiguous output redirect.\n");
        *error = true;
        return 2;
    }
    data->current_command->output_type = T_OUTPUT_NORMAL;
    data->current_command->output_option = *options;
    return 2;
}

int handle_io_output_append(sh_data_t *data, char **options, bool *error)
{
    if (*options == NULL || get_io_token(TOKEN_LIST, *options).size != 0) {
        my_fprintf(2, "Missing name for redirect\n");
        *error = true;
        return *options == NULL ? 1 : 2;
    }
    if (data->current_command->output_type != -1) {
        my_fprintf(2, "Ambiguous output redirect.\n");
        *error = true;
        return 2;
    }
    data->current_command->output_type = T_OUTPUT_APPEND;
    data->current_command->output_option = *options;
    return 2;
}

int handle_io_input(sh_data_t *data, char **options, bool *error)
{
    if (*options == NULL || get_io_token(TOKEN_LIST, *options).size != 0) {
        my_fprintf(2, "Missing name for redirect\n");
        *error = true;
        return *options == NULL ? 1 : 2;
    }
    if (data->current_command->input_type != -1) {
        my_fprintf(2, "Ambiguous input redirect.\n");
        *error = true;
        return 2;
    }
    data->current_command->input_type = T_INPUT_NORMAL;
    data->current_command->input_option = *options;
    return 2;
}

int handle_io_input_line(sh_data_t *data, char **options, bool *error)
{
    if (*options == NULL || get_io_token(TOKEN_LIST, *options).size != 0) {
        my_fprintf(2, "Missing name for redirect\n");
        *error = true;
        return *options == NULL ? 1 : 2;
    }
    if (data->current_command->output_type != -1) {
        my_fprintf(2, "Ambiguous input redirect.\n");
        *error = true;
        return 2;
    }
    data->current_command->input_type = T_INPUT_LINE;
    data->current_command->input_option = *options;
    return 2;
}
