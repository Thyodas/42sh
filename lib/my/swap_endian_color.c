/*
** EPITECH PROJECT, 2021
** swap_endian_color.c
** File description:
** swap_endian_color
*/

union ARGB {
    char byte[4];
    int raw_nb;
};

static void my_swap(char *a, char *b)
{
    char temp = *a;

    *a = *b;
    *b = temp;
}

int swap_endian_color(int color)
{
    union ARGB convert;
    char temp;

    convert.raw_nb = color;
    my_swap(&convert.byte[0], &convert.byte[3]);
    my_swap(&convert.byte[1], &convert.byte[2]);
    return (convert.raw_nb);
}
