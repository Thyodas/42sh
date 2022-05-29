/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** parse_curly_brackets.c
*/

#include "my.h"
#include "shell.h"
#include "my_list.h"
#include "globbings.h"

char *init_str(int size);
globbings_t init_globbings(void);
void extend_array(char ***array, char *new_line);

static void append_str(globbings_t *glob, char *str, int size)
{
    if (size <= 1) {
        extend_array(&glob->str_replacable, "");
        return;
    }
    char *new_str = init_str(size + 1);
    my_strncpy(new_str, str, size);
    extend_array(&glob->str_replacable, new_str);
}

static void fill_replacable(globbings_t *glob)
{
    int pos = 0;
    int i = 0;
    for (; glob->inside_bracket[i] != 0; ++i) {
        if (glob->inside_bracket[i] == ',') {
            append_str(glob, &glob->inside_bracket[pos], i - pos);
            pos = i + 1;
        }
    }
    append_str(glob, &glob->inside_bracket[pos], i - pos);
}

static int add_tmp_in_list(linked_list_t **list_globs, globbings_t *tmp,
                            char *str)
{
    if (tmp->pos_bracket_open == -1 && tmp->pos_bracket_close == -1) {
        *tmp = init_globbings();
        return 0;
    }
    else if (tmp->pos_bracket_close == -1)
        return 1;
    globbings_t *glob = malloc(sizeof(globbings_t));
    *glob = init_globbings();
    glob->pos_bracket_open = tmp->pos_bracket_open;
    glob->pos_bracket_close = tmp->pos_bracket_close;
    glob->size_bracket = tmp->pos_bracket_close - tmp->pos_bracket_open;
    glob->inside_bracket = init_str(glob->size_bracket);
    my_strncpy(glob->inside_bracket, &str[glob->pos_bracket_open + 1],
                glob->size_bracket - 1);
    fill_replacable(glob);
    my_add_node(glob, list_globs);
    *tmp = init_globbings();
    return 0;
}

int parse_curly_brackets(char *str, linked_list_t **list_globs)
{
    globbings_t tmp = init_globbings();
    int error = 0;
    for (int i = 0; str[i] != 0 && !error; ++i) {
        if (str[i] == '{' && (i == 0 || str[i - 1] != '\\'))
            tmp.pos_bracket_open = i;
        if (str[i] == '}' && tmp.pos_bracket_open != -1 && str[i - 1] != '\\'
            && str[i - 1] != '{') {
            tmp.pos_bracket_close = i;
            error = add_tmp_in_list(list_globs, &tmp, str);
        }
        if (str[i] == ' ' && tmp.pos_bracket_open != -1)
            error = 1;
    }
    if (error || (tmp.pos_bracket_open != -1 && tmp.pos_bracket_close == -1 &&
        str[tmp.pos_bracket_open + 1] != '}')) {
        my_fprintf(2, "Missing '}'.\n");
        return 1;
    }
    return 0;
}