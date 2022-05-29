/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** handle_match.c
*/

#include "my.h"
#include "my_list.h"
#include "shell.h"
#include "globbings.h"
#include <unistd.h>

void parse_square(char *str, linked_list_t **list_globs);
int	match(char *s1, char *s2, int pos1, int pos2);
char *init_str(int size);
void extend_array(char ***array, char *new_line);
char **get_all_sub_files(char *path, int max_depth);
char *concat_path(char *str1, char *str2);
char *get_start_path(char **args);
int get_max_depth(char *str);
char *get_file_without_start(char *file, char *start_path);
void free_array(char **array);

static char *replace_str(globbings_t *glob, int i, char *token)
{
    int len_tot = my_strlen(token);
    char *new_str = init_str(len_tot - glob->size_square + 2);
    int pos_square = 0;
    for (; token[pos_square] != '['; pos_square++);
    my_strncpy(new_str, token, pos_square);
    new_str[my_strlen(new_str)] = glob->char_replacable[i];
    if (my_strlen(new_str) < len_tot - glob->size_square + 1)
        my_strcat(new_str, &token[pos_square + glob->size_square + 1]);
    return new_str;
}

static void get_possibilities(char *token, linked_list_t *match_list,
                                char ***possibilites)
{
    if (match_list == NULL) {
        extend_array(possibilites, token);
        return;
    }
    globbings_t *glob = match_list->data;
    for (int i = 0; glob->char_replacable[i] != 0; ++i) {
        char *new_str = replace_str(glob, i, token);
        if (match_list->next != NULL)
            get_possibilities(new_str, match_list->next, possibilites);
        else
            extend_array(possibilites, new_str);
    }
}

static void match_all_files(char **files, char *full_path, char *start_path,
                            char ***new_args)
{
    for (int i = 0; files[i] != 0; ++i) {
        if (match(files[i], full_path, 0, 0))
            extend_array(new_args, get_file_without_start(files[i],
                        start_path));
    }
}

static char **handle_possibilities(char *str)
{
    linked_list_t *match_list = NULL;
    parse_square(str, &match_list);
    char **possibilities = malloc(sizeof(char *));
    possibilities[0] = NULL;
    get_possibilities(str, match_list, &possibilities);
    return possibilities;
}

char **handle_match(char **args)
{
    char *start_path = get_start_path(args);
    int max_depth = get_max_depth(args[0]);
    char **files = get_all_sub_files(start_path, max_depth);
    char **new_args = malloc(sizeof(char *));
    new_args[0] = NULL;
    for (int i = 0; args[i] != 0; ++i) {
        char **possibilites = handle_possibilities(args[i]);
        for (int j = 0; possibilites[j] != 0; ++j) {
            char *full_path = concat_path(start_path, possibilites[j]);
            match_all_files(files, full_path, start_path, &new_args);
        }
    }
    free_array(files);
    if (new_args[0] == NULL)
        return NULL;
    return new_args;
}
