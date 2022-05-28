/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** alias
*/

#include "shell.h"
#include "my.h"
#define INPUT data->line

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

static int add_new_alias(sh_data_t *data)
{
    unsigned int size = 2;
    for (; INPUT[size]; ++size);
    char **new_alias = malloc(sizeof(char *) * (size--));
    new_alias[size] = NULL;
    for (size = 1; INPUT[size]; ++size)
        new_alias[size - 1] = INPUT[size];
    extend_3d_array(&data->alias, new_alias);
    return 0;
}

int builtin_alias(sh_data_t *data)
{
    /* for (unsigned int i = 0; data->alias[i]; ++i) {
        if (my_strcmp(data->alias[i][0], INPUT[1]) == 0) {
            for (unsigned int noah = 1; INPUT[noah]; ++noah) {
                free(data->alias[i][1]);
                data->alias[i][1] = my_strdup(INPUT[noah]);
                return 0;
            }
        }
    } */
    return add_new_alias(data);
}

static void should_i_replace(sh_data_t *data, char **alias, unsigned int i)
{
    if(my_strcmp(INPUT[i], alias[0]) != 0)
        return;
    unsigned int mehdy = 0;
    unsigned int size_input = 1;
    unsigned int size_alias = 1;
    for (; INPUT[size_input]; ++size_input);
    for (; alias[size_alias]; ++size_alias);
    char **new_input = malloc(sizeof(char *) * (--size_input + size_alias--));
    new_input[size_input + size_alias] = NULL;
    for (; mehdy < i; ++mehdy)
        new_input[mehdy] = INPUT[mehdy];
    for (; alias[mehdy - i + 1]; ++mehdy)
        new_input[mehdy] = alias[mehdy - i + 1];
    for (; INPUT[mehdy - (size_input - 2)]; ++mehdy)
        new_input[mehdy] = INPUT[mehdy - (size_input - 2)];
}

int alias_handler(sh_data_t *data)
{
    //TODO error_handling
    for (unsigned int i = 0; INPUT[i]; ++i) {
        for (unsigned int j = 0; data->alias[j]; ++j) {
            should_i_replace(data, data->alias[j], i);
        }
    }
    return (0);
}
