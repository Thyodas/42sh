/*
** EPITECH PROJECT, 2021
** my_showmem.c
** File description:
** my_showmem
*/

int my_putnbr_base(int nbr, char const *base);

void my_putchar(int c);

int my_strlen(char const *str);

int my_char_isprintable(char c)
{
    if (32 > c || c > 126)
        return (0);
    return (1);
}

int my_putnbr_base_n(int nbr, char const *base, int n)
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
    if (nbr != 0 || n != 0)
        my_putnbr_base_n(nbr, base, n - 1);
    my_putchar(base[remainder]);
    return (0);
}

static void print_line_hex(const char *str, int size)
{
    int i = 0;

    for (; i < size && i < 16 ; i++) {
        if (i % 2 == 0)
            my_putchar(' ');
        if (str[i] < 16)
            my_putchar('0');
        my_putnbr_base(str[i], "0123456789abcdef");
    }
    for (; i < 16 ; i++) {
        if (i % 2 == 0)
            my_putchar(' ');
        my_putchar(' ');
        my_putchar(' ');
    }
    my_putchar(' ');
}

static void print_line_char(const char *str, int size)
{
    int i = 0;

    for (; i < size && i < 16 ; i++) {
        if (my_char_isprintable(str[i]))
            my_putchar(str[i]);
        else
            my_putchar('.');
    }
    my_putchar('\n');
}

int my_showmem(char const *str, int size)
{
    for (int i = 0 ; i < size ; i++) {
        if (i % 16 == 0) {
            my_putnbr_base_n(i, "0123456789abcdef", 7);
            my_putchar(':');
            print_line_hex(&str[i], size - i);
            print_line_char(&str[i], size - i);
        }
    }
    return (0);
}
