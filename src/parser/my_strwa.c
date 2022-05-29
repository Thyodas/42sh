/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** my_strwa
*/

#include <stddef.h>
#include <stdlib.h>

static int get_nbr_of_word(char const *str, char div)
{
    int is_in_word = 0;
    int nb_word = 0;

    for (unsigned int i = 0; str[i]; i++) {
        if (str[i] != div && str[i] != '\t') {
            is_in_word == 0 ? ++nb_word : 0;
            is_in_word = 1;
        } else {
            str[i] == div || str[i] == '\t'? is_in_word = 0 : 0;
        }
    }
    return (nb_word);
}

static char **malloc_array(char const *str, char div)
{
    int len_word = 0;
    int m = 0;
    int nb_word = get_nbr_of_word(str, div);
    char **tab = malloc(sizeof(char *) * (nb_word + 1));

    for (unsigned int i = 0; str[i]; i++) {
        if (str[i] != div || str[i] == '\t')
            ++len_word;
        if ((str[i + 1] == div || str[i + 1] == '\t' || str[i + 1] == '\0') &&
                (str[i] != div && str[i] != '\t')) {
            tab[m] = malloc(sizeof(char) * (len_word + 1));
            len_word = 0;
            ++m;
        }
    }
    return (tab);
}

char **my_stwa(char const *str, char div)
{
    int j = 0;
    int k = 0;
    for (; str[0] == ' '; str++);
    char **tab = malloc_array(str, div);

    for (unsigned int i = 0; str[i]; ++i) {
        if (str[i] != div && str[i] != '\t') {
            tab[j][k] = str[i];
            ++k;
        }
        if ((str[i + 1] == div || str[i + 1] == '\t' || str[i + 1] == '\0') &&
                (str[i] != div && str[i] != '\t')) {
            tab[j++][k] = '\0';
            k = 0;
        }
    }
    tab[j] = NULL;
    return (tab);
}

void concat_in_array(char ***oldline, char **array, unsigned int *i)
{
    unsigned int i_new = 0;
    unsigned int i_input = 0;
    unsigned int i_alias = 0;
    unsigned int size_input = 0;
    unsigned int size_array = 0;

    for (; (*oldline)[size_input]; ++size_input);
    for (; array[size_array]; ++size_array);
    char **new_input = malloc(sizeof(char *) * (size_input + size_array));
    new_input[size_input + size_array - 1] = NULL;
    for (; i_new < *i; ++i_new, ++i_input)
        new_input[i_new] = (*oldline)[i_input];
    for (; array[i_alias]; ++i_new, ++i_alias)
        new_input[i_new] = array[i_alias];
    for (++i_input; (*oldline)[i_input]; ++i_new, ++i_input)
        new_input[i_new] = (*oldline)[i_input];
    (*oldline) = new_input;
}
