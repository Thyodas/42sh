/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** match.c
*/

#include "my.h"

int	match(char *s1, char *s2)
{
    if (*s2 == '?')
        return (match(s1 + 1, s2 + 1));
    if (*s1 != '\0' && *s2 == '*')
        return (match(s1 + 1, s2) || match(s1, s2 + 1));
    if (*s1 == '\0' && *s2 == '*')
        return (match(s1, s2 + 1));
    if (*s1 == *s2 && *s1 != '\0')
        return (match(s1 + 1, s2 + 1));
    if (*s1 == *s2 && *s1 == '\0')
        return (1);
    return (0);
}
