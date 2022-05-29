/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** separator_handlers.c
*/

#include "my.h"
#include "shell.h"
#include "my_list.h"
#include <stdlib.h>

char *remove_quote(char *str);
special_token_t get_io_token(const special_token_t *token_list, char *str);

static int error_handling(char **line, const special_token_t *token_list,
                            bool *error, int separator_type)
{
    if (separator_type == T_BASIC)
        return 0;
    else if (line[1] == NULL) {
        my_fprintf(2, "Invalid null command.\n");
        *error = 1;
        return 1;
    }
    remove_quote(line[0]);
    special_token_t token = get_io_token(token_list, line[1]);
    if (token.size != 0) {
        my_fprintf(2, "Invalid null command.\n");
        *error = 1;
        return 1;
    }
    return 0;
}

int check_if_separator(char *str)
{
    char *separators[] = {";", "&&", "||"};
    int id_separators[] = {T_BASIC, T_AND, T_OR};
    for (int i = 0; i < 3; ++i)
        if (my_strcmp(separators[i], str) == 0)
            return id_separators[i];
    return T_NONE;
}

static int find_next_command(char **line)
{
    int i = 1;
    for (; line[i] != NULL && !check_if_separator(line[i]); ++i);
    return i;
}

int handle_separators(sh_data_t *data, char **line, bool *error,
                        const special_token_t *token_list)
{
    int separator_type = check_if_separator(line[0]);
    if (separator_type == T_NONE)
        return 0;
    if (error_handling(line, token_list, error, separator_type) != 0) {
        data->last_exit_status = 1;
        return 1;
    }
    if (separator_type == T_AND && data->last_exit_status)
        return find_next_command(line);
    else if (separator_type == T_AND)
        return 1;
    if (separator_type == T_OR && data->last_exit_status)
        return 1;
    else if (separator_type == T_OR)
        return find_next_command(line);
    return 1;
}
