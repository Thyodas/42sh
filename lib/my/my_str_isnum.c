/*
** EPITECH PROJECT, 2021
** my_str_isnum.c
** File description:
** my_str_isnum
*/

int my_str_isnum(char const *str)
{
    for (int i = 0 ; str[i] != '\0' ; i++) {
        if ('0' > str[i] || str[i] > '9')
            return (0);
    }
    return (1);
}
