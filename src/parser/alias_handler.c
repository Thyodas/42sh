/*
** EPITECH PROJECT, 2022
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** alias_handler
*/

#include "my.h"
#include "shell.h"
#include "define.h"

static void should_i_replace(sh_data_t *data, char **alias, unsigned int *i)
{
    if (my_strcmp(INPUT[*i], alias[0]) != 0)
        return;
    unsigned int i_input = 0;
    unsigned int i_alias = 1;
    unsigned int i_new = 0;
    unsigned int size_input = 1;
    unsigned int size_alias = 1;
    for (; INPUT[size_input]; ++size_input);
    for (; alias[size_alias]; ++size_alias);
    char **new_input = malloc(sizeof(char *) * (--size_input + size_alias--));
    new_input[size_input + size_alias] = NULL;
    for (; i_new < *i; ++i_new, ++i_input)
        new_input[i_new] = INPUT[i_input];
    for (; alias[i_alias]; ++i_new, ++i_alias)
        new_input[i_new] = alias[i_alias];
    for (++i_input; INPUT[i_input]; ++i_new, ++i_input)
        new_input[i_new] = INPUT[i_input];
    INPUT = new_input;
}

int alias_handler(sh_data_t *data)
{
    for (unsigned int i = 0; INPUT[i]; ++i) {
        if (my_strcmp(INPUT[i], "alias") == 0)
            for (; INPUT[i + 1] != NULL && INPUT[i][0] != ';'; ++i);
        for (unsigned int j = 0; ALIAS[j]; ++j) {
            should_i_replace(data, ALIAS[j], &i);
        }
    }
    return (0);
}
