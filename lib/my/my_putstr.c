/*
** EPITECH PROJECT, 2021
** my_putstr
** File description:
** my_putstr
*/

void my_putchar(int c);

int my_putstr(char const *str)
{
    for (; *str != '\0' ; str++)
        my_putchar(*str);
    return (0);
}
