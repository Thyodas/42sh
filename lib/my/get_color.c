/*
** EPITECH PROJECT, 2021
** get_color.c
** File description:
** get_color
*/

int get_color(unsigned char red, unsigned char green, unsigned char blue)
{
    int rgb = 0;
    rgb += (red << 16) + (green << 8) + blue;
    return (rgb);
}
