/*
** EPITECH PROJECT, 2021
** my_str_isalphanum.c
** File description:
** my_str_isalphanum
*/

int my_str_isalphanum(char const *str)
{
    for (int i = 0 ; str[i] != '\0' ; i++) {
        if (('a' > str[i] || str[i] > 'z')
        && ('A' > str[i] || str[i] > 'Z')
        && ('0' > str[i] || str[i] > '9'))
            return (0);
    }
    return (1);
}
