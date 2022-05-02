/*
** EPITECH PROJECT, 2021
** my_strncat.c
** File description:
** my_strncat
*/

int my_strlen(char const *str);

char *my_strncat(char *dest, char const *src, int nb)
{
    int i = 0;
    int len = my_strlen(dest);

    for (; src[i] != '\0' && i < nb ; i++) {
        dest[len + i] = src[i];
    }
    dest[len + i] = '\0';
    return dest;
}
