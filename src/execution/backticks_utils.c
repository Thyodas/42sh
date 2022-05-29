/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** backticks_utils.c
*/

#include "shell.h"
#include "my.h"

char *clean_str(char *str)
{
    char *res = malloc(sizeof(char) * (my_strlen(str) + 1));
    int a = 0;

    for (int i = 0; i < my_strlen(str); res[i++] = 0);
    while (str[0] == '\t' || str[0] == ' ')
        str++;
    for (int i = 0; str[i] != '\0'; i++) {
        (str[i] == ' ' || str[i] == '\t') ?
        (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0') ?
        0 : (1 == 1) ? res[a++] = ' ' : 0 : (1 == 1) ? res[a++] = str[i] : 0;
    }
    res[a] = '\0';
    return (res);
}

char *reformat(char *str)
{
    char *res;
    int i = 0;

    for (; str[i] != '\0'; i++)
        str[i] = str[i] == '\n' ? ' ' : str[i];
    str[i] = '\0';
    res = clean_str(str);
    return (res);
}

char **dup_array(char **array)
{
    char **res;
    int i = 0;

    while (array[i] != NULL)
        i++;
    res = malloc(sizeof(char *) * (i + 1));
    for(int j = 0; j < i; j++)
        res[j] = strdup(array[j]);
    res[i] = NULL;
    return (res);
}

void close_dup(int a, int b)
{
    close(b);
    dup2(a, b);
    close(a);
}