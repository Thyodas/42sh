/*
** EPITECH PROJECT, 2021
** convert_base.c
** File description:
** convert_base
*/

#include <stdlib.h>

int my_strlen(char const *str);

int my_getnbr_base(char const *str, char const *base);

char *my_strcat(char *dest, char const *src);

char *my_strcpy(char *dest, char const *src);

char *my_putnbr_base_str(int nbr, char const *base, char *str)
{
    int len_base = my_strlen(base);
    int remainder;
    char convert[2];
    convert[1] = '\0';

    if (nbr == 0 || len_base == 0)
        return (str);
    if (nbr < 0) {
        nbr = nbr * (-1);
        my_strcat(str, "-");
    }
    remainder = nbr % len_base;
    nbr /= len_base;
    my_putnbr_base_str(nbr, base, str);
    convert[0] = base[remainder];
    my_strcat(str, convert);
    return (str);
}

char *convert_base(char const *nbr, char const *base_from, char const *base_to)
{
    int nb = my_getnbr_base(nbr, base_from);
    char *new_str = (char *)malloc(sizeof(char) * 34);
    return (my_putnbr_base_str(nb, base_to, new_str));
}
