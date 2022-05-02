/*
** EPITECH PROJECT, 2021
** my_showstr.c
** File description:
** my_showstr
*/

int my_getnbr_base(char const *str, char const *base);

int my_putnbr_base(int nbr, char const *base);

void my_putchar(int c);

static int is_printable(char c)
{
    if (32 > c || c > 126)
        return (0);
    return (1);
}

int my_showstr(char const *str)
{
    for (int i = 0; str[i] != '\0' ; i++) {
        if (!is_printable(str[i]) && str[i] < 16) {
            my_putchar('\\');
            my_putchar('0');
            my_putnbr_base(str[i], "0123456789abcdef");
        } else if (!is_printable(str[i]) && str[i] >= 16) {
            my_putchar('\\');
            my_putnbr_base(str[i], "0123456789abcdef");
        } else
            my_putchar(str[i]);
    }
    return (0);
}
