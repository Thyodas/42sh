/*
** EPITECH PROJECT, 2021
** my_strupcase
** File description:
** my_strupcase
*/

char *my_strupcase(char *str)
{
    for (int i = 0 ; str[i] != '\0' ; i++) {
        if ('a' <= str[i] && str[i] <= 'z')
            str[i] = str[i] - 32;
    }
    return (str);
}
