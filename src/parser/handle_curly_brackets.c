/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** handle_globbings.c
*/

#include "my.h"
#include "shell.h"
#include "globbings.h"
#include "my_list.h"

char *remove_quote(char *str);
void parse_square(char *str, linked_list_t **list_globs);
char *init_str(int size);
int parse_curly_brackets(char *str, linked_list_t **list_globs);
void extend_array(char ***array, char *new_line);

globbings_t init_globbings(void)
{
    globbings_t globbings;
    globbings.pos_char = 0;
    globbings.char_replacable = NULL;
    globbings.inside_square = NULL;
    globbings.pos_bracket_close = -1;
    globbings.pos_bracket_open = -1;
    globbings.pos_square_close = -1;
    globbings.pos_square_open = -1;
    globbings.size_bracket = -1;
    globbings.size_square = -1;
    globbings.pos_str = 0;
    globbings.str_replacable = malloc(sizeof(char *));
    globbings.str_replacable[0] = NULL;
    return globbings;
}

static char *replace_str(globbings_t *glob, int i, char *str)
{
    int len_replace = my_strlen(glob->str_replacable[i]);
    int len_tot = my_strlen(str);
    char *new_str = init_str(len_tot - glob->size_bracket + len_replace);
    int pos_bracket = 0;
    for (; str[pos_bracket] != '{'; pos_bracket++);
    my_strncpy(new_str, str, pos_bracket);
    my_strcat(new_str, glob->str_replacable[i]);
    if (my_strlen(new_str) < len_tot - glob->size_bracket + len_replace)
        my_strcat(new_str, &str[glob->pos_bracket_close + 1]);
    return new_str;
}

static void create_new_args(char *str, linked_list_t *list_curly,
                            char ***args)
{
    if (list_curly == NULL) {
        extend_array(args, str);
        return;
    }
    globbings_t *glob = list_curly->data;
    for (int i = 0; glob->str_replacable[i] != 0; ++i) {
        char *new_str = replace_str(glob, i, str);
        if (list_curly->next != NULL)
            create_new_args(new_str, list_curly->next, args);
        else
            extend_array(args, new_str);
    }
}

char **handle_curly_brackets(char *str)
{
    str = remove_quote(str);
    int error = 0;
    linked_list_t *list_curly = NULL;
    char **args = malloc(sizeof(char *));
    args[0] = NULL;
    error = parse_curly_brackets(str, &list_curly);
    if (error)
        return NULL;
    my_rev_list(&list_curly);
    create_new_args(str, list_curly, &args);
    return args;
}
