/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** array.c
*/

#include "my.h"

void extend_array(char ***array, char *new_line)
{
    int size = 0;
    for (; (*array)[size] != NULL; ++size);
    char **new_array = malloc(sizeof(char *) * (size + 2));
    for (int i = 0; i < size; ++i)
        new_array[i] = (*array)[i];
    new_array[size] = new_line;
    new_array[size + 1] = NULL;
    free(*array);
    *array = new_array;
}

int len_array(char **array)
{
    int i = 0;
    for (; array[i] != NULL; ++i);
    return i;
}

void free_array(char **array)
{
    for (int i = 0; array[i] != 0; ++i)
        free(array[i]);
    free(array);
}
