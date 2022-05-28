/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** handle_args.c
*/

#include "my.h"
#include "shell.h"

char **handle_curly_brackets(char *str);
char **handle_match(char **args);
void extend_array(char ***array, char *new_line);;

static void fill_with_args(sh_data_t *data, char **args, int *i)
{
    for (int i = 0; args[i] != 0; ++i) {
        extend_array(&data->current_command->argv, args[i]);
        data->current_command->argc++;
    }
    *i = *i + 1;
}

void handle_args(sh_data_t *data, char *str, int *i)
{
    char **args_without_curly_brackets = handle_curly_brackets(str);
    char **matching_args = handle_match(args_without_curly_brackets);
    if (matching_args == NULL)
        fill_with_args(data, args_without_curly_brackets, i);
    else
        fill_with_args(data, matching_args, i);
}