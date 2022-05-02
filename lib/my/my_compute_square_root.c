/*
** EPITECH PROJECT, 2021
** my_compute_square_root.c
** File description:
** my_compute_square_root
*/

int my_compute_square_root(int nb)
{
    int result;
    int i = 0;

    if (nb <= 0)
        return (0);
    for (; result < nb && result != nb ; i++) {
        result = i * i;
    }
    if (result > nb)
        return (0);
    else
        return (i - 1);
}
