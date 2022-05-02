/*
** EPITECH PROJECT, 2021
** my_str_isprintable.c
** File description:
** my_str_isprintable
*/

int my_str_isprintable(char const *str)
{
    for (int i = 0 ; str[i] != '\0' ; i++) {
        if (32 > str[i] || str[i] > 126)
            return (0);
    }
    return (1);
}
