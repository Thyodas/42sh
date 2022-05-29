/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** alias
*/

#include "my.h"
#include "shell.h"
#include "define.h"
int len_array(char **array);
unsigned int my_3d_array_len(char ***array);
void extend_3d_array(char ****array, char **new_line);

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
    if (len_array(ALIAS[u]) > 2)
        my_printf("(");
    for (unsigned int v = 1; ALIAS[u][v]; ++v) {
        my_printf("%s", ALIAS[u][v]);
        if (ALIAS[u][v + 1])
            my_printf(" ");
    }
    if (len_array(ALIAS[u]) > 2)
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

static int compare(const void *a, const void *b)
{
    return my_strcmp(**(char ***)a, **(char ***)b);
}

int builtin_alias(sh_data_t *data)
{
    unsigned int size = 0;
    if (ARGC == 1) {
        qsort(ALIAS, my_3d_array_len(ALIAS), sizeof(char **), compare);
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
