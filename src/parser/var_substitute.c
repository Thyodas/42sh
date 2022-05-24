/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** var_substitute.c
*/

#include "my.h"
#include "shell.h"

void var_substitute(sh_data_t *data)
{
    char *var;

    for (int i = 0; data->line[i] != NULL; i++) {
        if ((var = my_strstr(data->line[i], "$")) != NULL)
            var[0] = '\0';
    }
}