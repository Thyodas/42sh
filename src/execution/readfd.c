/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** readfd.c
*/

#include "my.h"

char *read_fd(int fd)
{
    char buf[1024] = {0};
    int size;
    int total_size = 0;
    char *previous = NULL;
    char *str = my_strdup("");

    while ((size = read(fd, buf, 1024))) {
        previous = str;
        str = malloc(total_size + size + 1);
        my_strncpy(str, previous, total_size);
        my_strncpy(str + total_size, buf, size);
        total_size += size;
        str[total_size] = '\0';
        free(previous);
    }
    return (str);
}
