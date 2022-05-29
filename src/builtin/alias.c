/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** alias
*/

#include "my.h"
#include "shell.h"
#include "define.h"

/// UTILS ///

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

static unsigned int array_len (char **array)
{
    unsigned int size = 0;
    for (; array[size] != NULL; ++size);
    return size;
}

/// BUILTIN_ALIAS ///

static int add_new_alias(sh_data_t *data)
{
    unsigned int size = 2;

    for (; ARGV[size]; ++size);
    char **new_alias = malloc(sizeof(char *) * (size--));
    new_alias[size] = NULL;
    for (size = 1; ARGV[size]; ++size)
        new_alias[size - 1] = ARGV[size];
    extend_3d_array(&ALIAS, new_alias);
    return 0;
}

static void show_alias(sh_data_t *data, unsigned int u)
{
    my_printf("%s\t", ALIAS[u][0]);
    if (array_len(ALIAS[u]) > 2)
        my_printf("(");
    for (unsigned int v = 1; ALIAS[u][v]; ++v) {
        my_printf("%s", ALIAS[u][v]);
        if (ALIAS[u][v + 1])
            my_printf(" ");
    }
    if (array_len(ALIAS[u]) > 2)
        my_printf(")\n");
    else
        my_printf("\n");
}

static void replace_alias(sh_data_t *data, unsigned int size, unsigned int i)
{
    for (unsigned int noah = 1; ALIAS[i][noah]; ++noah)
        free(ALIAS[i][noah]);
    for (size = 0; ARGV[size]; ++size);
    char **new_alias = malloc(sizeof(char *) * (size--));
    new_alias[size] = NULL;
    for (size = 1; ARGV[size]; ++size)
        new_alias[size - 1] = ARGV[size];
    free(ALIAS[i]);
    ALIAS[i] = new_alias;
}

int builtin_alias(sh_data_t *data)
{
    unsigned int size = 0;
    if (ARGC == 1) {
        for (unsigned int u = 0; ALIAS[u]; ++u)
            show_alias(data, u);
        return 0;
    } else if (ARGC == 2)
        return 0;
    for (unsigned int i = 0; ALIAS[i]; ++i) {
        if (my_strcmp(ALIAS[i][0], ARGV[1]) == 0) {
            replace_alias(data, size, i);
            return 0;
        }
    }
    return add_new_alias(data);
}
