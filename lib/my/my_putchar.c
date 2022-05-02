/*
** EPITECH PROJECT, 2021
** my_putchar.c
** File description:
** my_putchar
*/

#include <unistd.h>

void my_putchar(int c)
{
    write(1, &c, 1);
}
