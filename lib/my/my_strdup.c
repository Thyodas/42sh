/*
** EPITECH PROJECT, 2021
** my_strdup.c
** File description:
** my_strdup
*/

#include <stdlib.h>

char *my_strcpy(char *dest, char const *src);

int my_strlen(char const *str);

char *my_strdup(char const *src)
{
    char *new_str = malloc(sizeof(char) * (my_strlen(src) + 1));
    if (new_str == NULL)
        return (NULL);
    my_strcpy(new_str, src);
    return new_str;
}
