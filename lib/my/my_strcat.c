/*
** EPITECH PROJECT, 2021
** my_strcat.c
** File description:
** my_strcat
*/

int my_strlen(char const *str);

char *my_strcat(char *dest, char const *src)
{
    int i = my_strlen(dest);

    for (; *src != '\0' ; src++) {
        dest[i] = *src;
        i++;
    }
    dest[i] = '\0';
    return dest;
}
