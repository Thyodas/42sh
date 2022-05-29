/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** parse_square_brackets.c
*/

#include "my.h"
#include "shell.h"
#include "globbings.h"
#include "my_list.h"

char *init_str(int size);
globbings_t init_globbings(void);

static void append_char_in_string(globbings_t *glob, char c)
{
    int len_str = 0;
    if (glob->char_replacable != NULL)
        len_str = my_strlen(glob->char_replacable);
    char *new_str = init_str(len_str + 2);
    if (glob->char_replacable != NULL)
        my_strcpy(new_str, glob->char_replacable);
    new_str[len_str] = c;
    if (glob->char_replacable)
        free(glob->char_replacable);
    glob->char_replacable = new_str;
}

static void append_range_in_string(globbings_t *glob, char c1, char c2)
{
    if (c1 > c2)
        return;
    int len_range = c2 - c1 + 1;
    int len_str = 0;
    if (glob->char_replacable != NULL)
        len_str = my_strlen(glob->char_replacable);
    char *range = init_str(len_range + 1);
    int pos = 0;
    for (int i = c1; i <= c2; ++i)
        range[pos++] = i;
    char *new_str = init_str(len_range + len_str + 1);
    if (glob->char_replacable != NULL)
        my_strcpy(new_str, glob->char_replacable);
    my_strcat(new_str, range);
    if (glob->char_replacable)
        free(glob->char_replacable);
    glob->char_replacable = new_str;
}

static void fill_replacable(globbings_t *glob)
{
    for (int i = 0; glob->inside_square[i] != 0; ++i) {
        if (glob->inside_square[i + 1] != 0 &&
            glob->inside_square[i + 1] == '-' &&
            glob->inside_square[i + 2] != 0) {
            append_range_in_string(glob, glob->inside_square[i],
                                    glob->inside_square[i + 2]);
            i += 2;
        } else
            append_char_in_string(glob, glob->inside_square[i]);
    }
}

static void add_tmp_in_list(linked_list_t **list_globs, globbings_t *tmp,
                            char *str)
{
    if (tmp->pos_square_open == -1 || tmp->pos_square_close == -1) {
        *tmp = init_globbings();
        return;
    }
    globbings_t *glob = malloc(sizeof(globbings_t));
    *glob = init_globbings();
    glob->pos_square_open = tmp->pos_square_open;
    glob->pos_square_close = tmp->pos_square_close;
    glob->size_square = tmp->pos_square_close - tmp->pos_square_open;
    glob->inside_square = init_str(glob->size_square);
    my_strncpy(glob->inside_square, &str[glob->pos_square_open + 1],
                glob->size_square - 1);
    fill_replacable(glob);
    if (glob->char_replacable != NULL)
        my_add_node(glob, list_globs);
    *tmp = init_globbings();
}

void parse_square(char *str, linked_list_t **list_globs)
{
    globbings_t tmp = init_globbings();
    for (int i = 0; str[i] != 0; ++i) {
        if (str[i] == '[' && (i == 0 || str[i - 1] != '\\'))
            tmp.pos_square_open = i;
        if (str[i] == ']' && tmp.pos_square_open != -1 && str[i - 1] != '\\'
            && str[i - 1] != '[') {
            tmp.pos_square_close = i;
            add_tmp_in_list(list_globs, &tmp, str);
        }
    }
}