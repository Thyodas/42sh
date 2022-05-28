/*
** EPITECH PROJECT, 2021
** my_str_to_word_array.c
** File description:
** my_str_to_word_array
*/

#include "my.h"
#include "shell.h"
#include <stdlib.h>

int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_strlen(char const *str);
char *my_strdup(char const *src);
int is_char_blank(char c);
int is_char_special(char c);
int is_char_valid(char c);
int is_quote(int c);
void extend_array(char ***array, char *new_line);

static const special_token_t TOKEN_LIST[] = {
    {">>", 2, NULL},
    {">", 1, NULL},
    {"<<", 2, NULL},
    {"<", 1, NULL},
    {";", 1, NULL},
    {"||", 2, NULL},
    {"|", 1, NULL},
    {";", 1, NULL},
    {"&&", 2, NULL},
    {NULL, 0, NULL}
};

int get_str_by_condition(char ***array, const char *str,
int (*condition)(char c))
{
    int size = 0;
    for (; condition(str[size]); ++size);
    char *new_str = malloc(sizeof(char) * (size + 1));
    my_strncpy(new_str, str, size);
    new_str[size] = '\0';
    extend_array(array, new_str);
    return (size);
}

int quote_handling(char ***array, const char *str)
{
    char quote = str[0];
    int size = 1;

    for (; str[size] != quote; ++size)
        if (str[size] == '\0') {
            my_fprintf(2, "Unmatched '%c'.\n", quote);
            return (-1);
        }
    size++;
    char *new_str = malloc(sizeof(char) * (size + 1));
    my_strncpy(new_str, str, size);
    new_str[size] = '\0';
    extend_array(array, new_str);
    return (size);
}

int handle_char(char ***array, const char *str, int pos)
{
    for (int i = 0; TOKEN_LIST[i].size != 0; ++i) {
        if (my_strncmp(&str[pos], TOKEN_LIST[i].name,
            TOKEN_LIST[i].size) == 0) {
            extend_array(array, my_strdup(TOKEN_LIST[i].name));
            return (TOKEN_LIST[i].size);
        }
    }
    if (is_quote(str[pos])) {
        return (quote_handling(array, str + pos));
    }
    if (is_char_valid(str[pos])) {
        return (get_str_by_condition(array, str + pos, &is_char_valid));
    }
    return 1;
}

char **line_to_array(char const *str)
{
    char **array = malloc(sizeof(char *));
    array[0] = NULL;
    int len = my_strlen(str);
    int tmp;
    for (int i = 0; i < len;) {
        tmp = handle_char(&array, str, i);
        if (tmp == -1)
            return NULL;
        i += tmp;
    }
    return array;
}
