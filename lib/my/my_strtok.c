/*
** EPITECH PROJECT, 2022
** my_strtok
** File description:
** my_strtok
*/

#include <stdlib.h>

char *my_strcpy(char *dest, char const *src);

static int char_in(char c, char *str)
{
    for (; *str ; ++str)
        if (*str == c)
            return (1);
    return (0);
}

char *my_strtok(char *string, char *delimiters)
{
    static char *iter_str = "";
    int i = 0;
    int j = 0;

    if (string != NULL) {
        for (; string[j] && char_in(string[j], delimiters) ; ++j);
        iter_str = &string[j];
    }
    char *start = iter_str;
    for (; iter_str[i] && !char_in(iter_str[i], delimiters) ; ++i);
    iter_str = &iter_str[i];
    int a = 0;
    for (; iter_str[a] && char_in(iter_str[a], delimiters) ; ++a)
        iter_str[a] = '\0';
    if (start[0] == '\0')
        return (NULL);
    iter_str = &iter_str[a];
    return (start);
}
