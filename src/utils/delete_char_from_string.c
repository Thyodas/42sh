/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** delete_char_from_string.c
*/

#include "my.h"
#include <stdlib.h>

char *init_str(int size);

char *delete_char_from_string(char *str, int pos)
{
    int len = my_strlen(str);
    char *new_str;
    if (len <= 1)
        new_str = init_str(1);
    else
        new_str = init_str(len - 1);
    my_strncpy(new_str, str, pos);
    if (my_strlen(new_str) < len - 1)
        my_strcat(new_str, &str[pos + 1]);
    return new_str;
}