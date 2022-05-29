/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** parse_files.c
*/

#include "my.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void extend_array(char ***array, char *new_line);
int len_array(char **array);
char *init_str(int size);

static int cmpstringp(const void *p1, const void *p2)
{
    return strcmp(*(const char **) p1, *(const char **) p2);
}

char **parse_dir(char *path)
{
    DIR *dir = opendir(path);
    struct dirent *dirent = NULL;
    char **array = malloc(sizeof(char *));
    array[0] = NULL;

    if (dir == NULL)
        return NULL;
    dirent = readdir(dir);
    while (dirent != 0) {
        if (dirent->d_name[0] != '.') {
            char *path = init_str(my_strlen(dirent->d_name));
            my_strcpy(path, dirent->d_name);
            extend_array(&array, path);
        }
        dirent = readdir(dir);
    }
    closedir(dir);
    qsort(array, (size_t)len_array(array), sizeof(char *), cmpstringp);
    return array;
}
