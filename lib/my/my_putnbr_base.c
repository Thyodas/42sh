/*
** EPITECH PROJECT, 2021
** my_putnbr_base.c
** File description:
** my_putnbr_base
*/

void my_putchar(int c);

int my_strlen(char const *str);

int my_putnbr_base(int nbr, char const *base)
{
    int len_base = my_strlen(base);
    int remainder;

    if (len_base == 0)
        return (0);
    if (nbr < 0) {
        nbr = nbr * (-1);
        my_putchar('-');
    }
    remainder = nbr % len_base;
    nbr /= len_base;
    if (nbr != 0)
        my_putnbr_base(nbr, base);
    my_putchar(base[remainder]);
    return (0);
}
