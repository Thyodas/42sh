/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** is_a_dir.c
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int is_a_dir(char *path)
{
    struct stat st;
    if (stat(path, &st))
        return -1;
    return S_ISDIR(st.st_mode);
}
