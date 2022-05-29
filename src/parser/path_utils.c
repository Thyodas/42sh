/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** path_utils.c
*/

#include "my.h"
#include <unistd.h>

char *init_str(int size);

char *concat_path(char *str1, char *str2)
{
    char *new_path = init_str(my_strlen(str1) + my_strlen(str2) + 1);
    if (str1[0] != '/' || my_strlen(str1) > 1) {
        my_strcpy(new_path, str1);
        my_strcat(new_path, "/");
    }
    my_strcat(new_path, str2);
    return new_path;
}

char *get_start_path(char **args)
{
    char *start_path;
    if (args[0][0] == '/')
        start_path = "/";
    else {
        start_path = init_str(1024);
        getcwd(start_path, 1024);
    }
    return start_path;
}

int get_max_depth(char *str)
{
    int max_depth = 0;

    if (str[0] == '\0')
        return (max_depth);
    for (int i = 1; str[i] != 0; ++i) {
        if (str[i] == '/')
            max_depth++;
    }
    return max_depth;
}

char *get_file_without_start(char *file, char *start_path)
{
    int len_start = my_strlen(start_path);
    char *new_file = init_str(my_strlen(file) - len_start + 1);
    if (len_start == 1)
        my_strcpy(new_file, file);
    else
        my_strcpy(new_file, &file[len_start + 1]);
    return new_file;
}