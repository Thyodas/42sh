/*
** EPITECH PROJECT, 2021
** my_strcapitalize.c
** File description:
** my_strcapitalize
*/

int my_str_isalpha(char const *str);

int my_strlen(char const *str);

static char to_upper(char c)
{
    if ('a' <= c && c <= 'z')
        return (c - 32);
    return (c);
}

static char to_lower(char c)
{
    if ('A' <= c && c <= 'Z')
        return (c + 32);
    return (c);
}

static int is_alpha(char c)
{
    if ('a' <= c && c <= 'z')
        return (1);
    else if ('A' <= c && c <= 'Z')
        return (1);
    else
        return (0);
}

char *my_strcapitalize(char *str)
{
    if (my_strlen(str) == 0)
        return (str);
    str[0] = to_upper(str[0]);
    for (int i = 1; str[i] != '\0' ; i++) {
        if (is_alpha(str[i - 1]) || ('0' <= str[i - 1] && str[i - 1] <= '9'))
            str[i] = to_lower(str[i]);
        else
            str[i] = to_upper(str[i]);
    }
    return (str);
}
