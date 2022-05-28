/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** parse_files_recursively.c
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
int is_a_dir(char *path);

static int cmpstringp(const void *p1, const void *p2)
{
    return strcmp(*(const char **) p1, *(const char **) p2);
}

static char *concat_path_parser(char *str1, char *str2)
{
    char *new_path = init_str(my_strlen(str1) + my_strlen(str2) + 1);
    my_strcpy(new_path, str1);
    if (my_strcmp(str1, "/") != 0)
        my_strcat(new_path, "/");
    my_strcat(new_path, str2);
    return new_path;
}

static char *get_full_path(struct dirent *dirent, char *path)
{
    char *file = init_str(my_strlen(dirent->d_name));
    my_strcpy(file, dirent->d_name);
    char *full_path = concat_path_parser(path, file);
    return full_path;
}

static void parse_dir_recursively(char *path, int max_depth, char ***array)
{
    static int depth = 0;
    if (depth > max_depth)
        return;
    DIR *dir = opendir(path);
    struct dirent *dirent = NULL;
    if (dir == NULL)
        return;
    while ((dirent = readdir(dir)) != 0) {
        if (dirent->d_name[0] == '.')
            continue;
        char *full_path = get_full_path(dirent, path);
        extend_array(array, full_path);
        if (is_a_dir(full_path)) {
            depth++;
            parse_dir_recursively(full_path, max_depth, array);
            depth--;
        }
    }
    closedir(dir);
}

char **get_all_sub_files(char *path, int max_depth)
{
    char **array = malloc(sizeof(char *));
    array[0] = NULL;
    parse_dir_recursively(path, max_depth, &array);
    qsort(array, (size_t)len_array(array), sizeof(char *), cmpstringp);
    return array;
}
