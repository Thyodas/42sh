/*
** EPITECH PROJECT, 2021
** my_str_to_word_array.c
** File description:
** my_str_to_word_array
*/

#include <stdlib.h>

int my_str_isalpha(char const *str);

int my_str_isnum(char const *str);

int my_strlen(char const *str);

char *my_strdup(char const *src);

static char *slice(const char *str, int intrvl[])
{
    char *new_str = (char *)malloc(sizeof(char) * (intrvl[1] - intrvl[0] + 1));
    int i = 0;

    for (; i < intrvl[1] - intrvl[0] ; i++) {
        new_str[i] = str[i + intrvl[0]];
    }
    new_str[i] = '\0';
    return (new_str);
}

static int word_number(char const *str, int is_previous_valid, int pos)
{
    char test[2];

    if (str[pos] == '\0')
        return (0);
    test[1] = '\0';
    test[0] = str[pos];
    if ((my_str_isalpha(test) || my_str_isnum(test)) && !is_previous_valid) {
        return (1 + word_number(str, 1, pos + 1));
    } else if (!(my_str_isalpha(test) || my_str_isnum(test))) {
        return (word_number(str, 0, pos + 1));
    } else
        return (word_number(str, 1, pos + 1));
}

static void m_str_warr(char const *str, int wnb, char **warr, int *intrvl)
{
    int is_alphanum = 0;
    char test[] = "a";
    int pos = 0;

    for (int i = 0 ; str[i] != '\0' ; i++) {
        test[0] = str[i];
        if (my_str_isalpha(test) || my_str_isnum(test)) {
            intrvl[0] = !is_alphanum ? i : intrvl[0];
            is_alphanum = 1;
        } else if (intrvl[1] - intrvl[0] > 0 && is_alphanum) {
            is_alphanum = 0;
            warr[pos] = my_strdup(slice(str, intrvl));
            pos++;
        }
        intrvl[1] = i + 1;
    }
    if (my_str_isalpha(slice(str, intrvl)) || my_str_isnum(slice(str, intrvl)))
        warr[pos] = my_strdup(slice(str, intrvl));
}

char **my_str_to_word_array(char const *str)
{
    int wnb;
    char **warr;
    int *intrvl;

    if (my_strlen(str) == 0) {
        char **empty = malloc(sizeof(char *));
        empty[0] = 0;
        return (empty);
    }
    wnb = word_number(str, 0, 0);
    warr = malloc(sizeof(char *) * (wnb + 1));
    intrvl = (int *)malloc(sizeof(int) * 2);
    m_str_warr(str, wnb, warr, intrvl);
    warr[wnb] = 0;
    free(intrvl);
    return (warr);
}
