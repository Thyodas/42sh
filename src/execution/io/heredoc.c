/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** heredoc
*/

#include "my.h"
#include "shell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int heredoc_prompt(sh_data_t *data)
{
    while (1) {
        if (data->is_prompt_mode)
            my_putstr("? ");
        char *line = NULL;
        size_t len = 0;
        ssize_t line_size = getline(&line, &len, stdin);
        if (line_size == -1 || line == NULL)
            return 1;
        line[line_size - 1] = line[line_size - 1] == '\n' ? '\0'
            : line[line_size - 1];
        if (my_strcmp(line, data->current_command->input_option) == 0) {
            free(line);
            return 0;
        }
        my_fprintf(data->current_command->read_fd, "%s\n", line);
        free(line);
    }
}

int retrieve_io_input_line(sh_data_t *data)
{
    if ((data->current_command->read_fd = open(
        HEREDOC_TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC,
        S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) == -1) {
        perror(HEREDOC_TEMP_FILE);
        return 1;
    }
    if (heredoc_prompt(data))
        return 1;
    if ((data->current_command->read_fd = open(
        HEREDOC_TEMP_FILE, O_RDONLY)) == -1) {
        perror(HEREDOC_TEMP_FILE);
        return 1;
    }
    return 0;
}
