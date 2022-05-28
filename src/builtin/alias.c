/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** alias
*/

#include "shell.h"
#include "my.h"
#define INPUT data->input

static void extend_3d_array(char ****array, char **new_line)
{
    int size = 0;
    for (; (*array)[size] != NULL; ++size);
    char ***new_array = malloc(sizeof(char **) * (size + 2));
    for (int i = 0; i < size; ++i)
        new_array[i] = (*array)[i];
    new_array[size] = new_line;
    new_array[size + 1] = NULL;
    free(*array);
    *array = new_array;
}

static void add_alias(sh_data_t *data)
{
    unsigned int size = 0;
    char *new_alias = NULL;
    for (unsigned int i = 2/*skip alias*/; INPUT[i]; ++i) {
        size += my_strlen(INPUT[i]);
        new_alias = realloc(new_alias, sizeof(char) * (size + 1));
        my_strcat(new_alias, INPUT[i]);
    }
    extend_3d_array(&data->alias, (char **){INPUT[1], new_alias}); //TODO review
    return;
}

static void checker(sh_data_t *data, char *alias)
{
    return;
}

int alias_handler(sh_data_t *data)
{
    //TODO error_handling
    if (my_strcmp("alias", input[0])) {
        add_alias(data);
        return;
    }
    for (unsigned int i = 0; i alias[i]; ++i) {
        if (my_strcmp(INPUT[0], alias[i][0])) {
            INPUT[i] = alias[i][1];
        }
    }
    return (0);
}
