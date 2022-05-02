/*
** EPITECH PROJECT, 2021
** my_compute_power_rec.c
** File description:
** my_compute_power_rec
*/

int check_overflow(long nb);

int my_compute_power_rec(int nb, int p)
{
    long previous;

    if (p < 0)
        return (0);
    else if (p == 0)
        return (1);
    else {
        previous = (long)my_compute_power_rec(nb, p - 1);
        return (check_overflow((long)nb * (long)check_overflow(previous)));
    }
}
