/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** handle_inhibitors.c
*/

#include "my.h"
#include "shell.h"

char *delete_char_from_string(char *str, int pos);
char *insert_char_in_str(char *str, int pos, char c);

static const char *ascii_str[] = {
    "\\0",
    "\\a",
    "\\b",
    "\\t",
    "\\n",
    "\\v",
    "\\f",
    "\\r"
};

static const char ascii_char[] = {
    0,
    '\a',
    '\b',
    '\t',
    '\n',
    '\v',
    '\f',
    '\r'
};

static char* delete_and_insert(char *str, int pos, int i)
{
    str = delete_char_from_string(str, pos);
    str = delete_char_from_string(str, pos);
    if (i != 0)
        str = insert_char_in_str(str, pos, ascii_char[i]);
    return str;
}

static char *check_if_replacable_ascii(char *str, int pos)
{
    for (int i = 0; i < 8; ++i) {
        if (!my_strncmp(&str[pos], ascii_str[i], 2))
            str = delete_and_insert(str, pos, i);
    }
    return str;
}

char *handle_ascii_inhib(char *str)
{
    for (int i = 0; str[i] != 0; ++i) {
        if (str[i] == '\\')
            str = check_if_replacable_ascii(str, i);
    }
    return str;
}