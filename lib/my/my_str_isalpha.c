/*
** EPITECH PROJECT, 2021
** my_str_isalpha.c
** File description:
** my_str_isalpha
*/

int my_str_isalpha(char const *str)
{
    for (int i = 0 ; str[i] != '\0' ; i++) {
        if (('a' > str[i] || str[i] > 'z')
        && ('A' > str[i] || str[i] > 'Z'))
            return (0);
    }
    return (1);
}
