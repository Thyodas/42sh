/*
** EPITECH PROJECT, 2021
** my_strstr.c
** File description:
** my_strstr
*/

int my_strncmp(char const *s1 , char const *s2, int n);

int my_strlen(char const *str);

char *my_strstr(char *str, char const *to_find)
{
    int len = my_strlen(to_find);

    if (my_strlen(to_find) == 0)
        return str;
    for (int i = 0 ; str[i] != '\0' ; i++) {
        if (my_strncmp(&str[i], to_find, len) == 0) {
            return (&str[i]);
        }
    }
    return ('\0');
}
