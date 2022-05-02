/*
** EPITECH PROJECT, 2021
** my_strcmp_alpha
** File description:
** my_strcmp_alpha
*/

static char to_lower(char c)
{
    if ('A' <= c && c <= 'Z')
        return c - 'A' + 'a';
    else
        return c;
}

int my_strcmp_alpha(char const *s1, char const *s2)
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0'
    && to_lower(s1[i]) == to_lower(s2[i]))
        i++;
    if (to_lower(s1[i]) == to_lower(s2[i]))
        return (0);
    else if (to_lower(s1[i]) > to_lower(s2[i]))
        return (1);
    else
        return (-1);
}
