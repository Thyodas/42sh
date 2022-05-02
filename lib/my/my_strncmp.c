/*
** EPITECH PROJECT, 2021
** my_strncmp
** File description:
** my_strncmp
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    if (n <= 0)
        return (0);
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < n - 1)
        i++;
    if (s1[i] == s2[i])
        return (0);
    return (s1[i] - s2[i]);
}
