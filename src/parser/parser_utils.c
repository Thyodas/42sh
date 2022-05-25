/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** parser_utils.c
*/

#include "my.h"
#include "shell.h"

int is_quote(int c);;

special_token_t get_io_token(const special_token_t *token_list, char *str)
{
    int i = 0;

    for (; token_list[i].size != 0; ++i)
        if (my_strncmp(str, token_list[i].name, token_list[i].size) == 0)
            return (token_list[i]);
    return (token_list[i]);
}

char *remove_quote(char *str)
{
    if (str == NULL)
        return NULL;
    int len = my_strlen(str);
    if (len == 0 || !(str[0] == str[len - 1] && is_quote(str[0])))
        return str;
    char *new_str = malloc(sizeof(char) * len);
    my_strcpy(new_str, &str[1]);
    new_str[len - 2] = '\0';
    free(str);
    return new_str;
}
