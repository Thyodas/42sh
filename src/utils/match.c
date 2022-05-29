/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** match.c
*/

#include "my.h"

int match(char *s1, char *s2, int pos1, int pos2)
{
    if (s2[pos2] == '?' && (pos2 == 0 || s2[pos2 - 1] != '\\'))
        return (match(s1, s2, pos1 + 1, pos2 + 1));
    if (s1[pos1] != '\0' && (s2[pos2] == '*' && (pos2 == 0 ||
                                                    s2[pos2 - 1] != '\\')))
        return (match(s1, s2, pos1 + 1, pos2) ||
            match(s1, s2, pos1, pos2 + 1));
    if (s1[pos1] == '\0' && (s2[pos2] == '*' && (pos2 == 0 ||
                                                    s2[pos2 - 1] != '\\')))
        return (match(s1, s2, pos1, pos2 + 1));
    if (s1[pos1] == s2[pos2] && s1[pos1] != '\0')
        return (match(s1, s2, pos1 + 1, pos2 + 1));
    if (s1[pos1] == s2[pos2] && s1[pos1] == '\0')
        return (1);
    return (0);
}
