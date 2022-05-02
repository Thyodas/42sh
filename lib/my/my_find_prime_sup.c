/*
** EPITECH PROJECT, 2021
** my_find_prime_sup.c
** File description:
** my_find_prime_sup
*/

int my_is_prime(int nb);

int my_find_prime_sup(int nb)
{
    long i = nb;

    while (!my_is_prime((int)i)) {
        i++;
        if (i > 2147483647)
            return (0);
    }
    return i;
}
