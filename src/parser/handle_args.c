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
void extend_array(char ***array, char *new_line);
char *delete_char_from_string(char *str, int pos);

static char *remove_inhibitors(char *str)
{
    for (int i = 0; str[i] != 0; ++i) {
        if (str[i] == '\\')
            str = delete_char_from_string(str, i);
    }
    return str;
}

static void fill_with_args(sh_data_t *data, char **args, int *i)
{
    for (int i = 0; args[i] != 0; ++i) {
        args[i] = remove_inhibitors(args[i]);
        extend_array(&data->current_command->argv, args[i]);
        data->current_command->argc++;
    }
    *i = *i + 1;
}

static int contains_a_match(char *str)
{
    int square_bracket_found = 0;
    for (int i = 0; str[i] != 0; ++i) {
        if (str[i] == '*' && (i == 0 || str[i - 1] != '\\'))
            return 1;
        if (str[i] == '?' && (i == 0 || str[i - 1] != '\\'))
            return 1;
        if (str[i] == '[' && (i == 0 || str[i - 1] != '\\'))
            square_bracket_found = 1;
        if (str[i] == ']' && square_bracket_found && str[i - 1] != '\\')
            return 1;
    }
    return 0;
}

int handle_args(sh_data_t *data, char *str, int *i)
{
    char **args_without_curly_brackets = handle_curly_brackets(str);
    if (args_without_curly_brackets == NULL) {
        *i = *i + 1;
        return 0;
    }
    char **matching_args = handle_match(args_without_curly_brackets);
    if (matching_args == NULL && contains_a_match(str)) {
        if (data->current_command->argv[0] != NULL)
            my_fprintf(2, "%s: No match.\n", data->current_command->argv[0]);
        else
            my_fprintf(2, "%s: No match.\n", str);
        *i = *i + 1;
        return 0;
    } else if (matching_args == NULL)
        fill_with_args(data, args_without_curly_brackets, i);
    else
        fill_with_args(data, matching_args, i);
    return 1;
}
