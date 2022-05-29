/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** alias
*/

#include "shell.h"
#include "my.h"
#define INPUT data->line
#define ALIAS data->alias
#define ARGV data->current_command->argv
#define ARGC data->current_command->argc

///UTILS///

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

///BUILTIN_ALIAS///

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

int builtin_alias(sh_data_t *data)
{
    unsigned int size = 0;
    if (ARGC == 1) {
        for (unsigned int u = 0; ALIAS[u]; ++u) {
            printf("%s\t", ALIAS[u][0]);
            if (array_len(ALIAS[u]) > 2)
                printf("(");
            for (unsigned int v = 1; ALIAS[u][v]; ++v) {
                printf("%s", ALIAS[u][v]);
                if (ALIAS[u][v + 1])
                    printf(" ");
            }
            if (array_len(ALIAS[u]) > 2)
                printf(")\n");
            else
                printf("\n");
        }
        return 0;
    } else if (ARGC == 2) return 0;

    for (unsigned int i = 0; ALIAS[i]; ++i) {
        if (my_strcmp(ALIAS[i][0], ARGV[1]) == 0) {
            for (unsigned int noah = 1; ALIAS[i][noah]; ++noah)
                free(ALIAS[i][noah]);
            for (size = 0; ARGV[size]; ++size);
            char **new_alias = malloc(sizeof(char *) * (size--));
            new_alias[size] = NULL;
            for (size = 1; ARGV[size]; ++size)
                new_alias[size - 1] = ARGV[size];
            free(ALIAS[i]);
            ALIAS[i] = new_alias;
            return 0;
        }
    }
    return add_new_alias(data);
}


///ALIAS_HANDLING///


static void should_i_replace(sh_data_t *data, char **alias, unsigned int *i)
{
    if(my_strcmp(INPUT[*i], alias[0]) != 0)
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
    printf("new_input\n");
    // for (unsigned int u = 0; INPUT[u]; ++u)
    //     printf("%s ", INPUT[u]);
    // printf("\n");
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
