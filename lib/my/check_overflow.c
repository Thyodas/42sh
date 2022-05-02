/*
** EPITECH PROJECT, 2021
** check_overflow.c
** File description:
** It's time to check your damn int overflow
*/

int check_overflow(long nb)
{
    if (nb > 2147483647 || nb < -2147483648)
        return (0);
    else
        return ((int)nb);
}
