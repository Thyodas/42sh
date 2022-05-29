/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** insert_char_in_str.c
*/

#include "my.h"

char *init_str(int size);

char *insert_char_in_str(char *str, int pos, char c)
{
    int len = my_strlen(str);
    char *new_str;
    if (!len)
        new_str = init_str(2);
    else
        new_str = init_str(len + 1);
    if (len != 0)
        my_strncpy(new_str, str, pos);
    new_str[pos] = c;
    if (my_strlen(new_str) < len + 1)
        my_strcat(new_str, &str[pos]);
    return new_str;
}