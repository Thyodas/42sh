/*
** EPITECH PROJECT, 2021
** my_is_prime.c
** File description:
** my_is_prime
*/

int my_is_prime(int nb)
{
    int is_valid = 1;

    if (nb <= 1)
        return (0);
    for (int i = 2 ; i < nb && is_valid ; i++) {
        if (nb % i == 0)
            is_valid = 0;
    }
    return (is_valid);
}
