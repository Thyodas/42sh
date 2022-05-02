/*
** EPITECH PROJECT, 2021
** my_put_nbr
** File description:
** my_put_nbr
*/

void my_putchar(int c);

static int rec_my_put_nbr(long nb)
{
    if (nb != 0) {
        rec_my_put_nbr(nb / 10);
        my_putchar(nb % 10 + 48);
    }
    return (0);
}

int my_put_nbr(int nb)
{
    if (nb == 0) {
        my_putchar(48);
    } else if (nb >= 0) {
        rec_my_put_nbr(nb);
    } else {
        my_putchar(45);
        rec_my_put_nbr((long)nb * (-1));
    }
    return (0);
}
