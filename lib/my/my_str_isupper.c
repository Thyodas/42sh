/*
** EPITECH PROJECT, 2021
** my_str_isupper.c
** File description:
** my_str_isupper
*/

int my_str_isupper(char const *str)
{
    for (int i = 0; str[i] != '\0' ; i++) {
        if ('A' > str[i] || str[i] > 'Z')
            return (0);
    }
    return (1);
}
