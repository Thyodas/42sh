/*
** EPITECH PROJECT, 2021
** my_getnbr_base.c
** File description:
** my_getnbr_base
*/

char *my_strstr(char const *str, char const *to_find);

int power(int nb, int power);

int my_strlen(char const *str);

static int get_pos_base(char const *base, char c)
{
    int i = 0;

    while (base[i] != c && base[i] != '\0') {
        i++;
    }
    return (i);
}

static long sl_lg(char const *str, int *strt_end, char const *base, int is_neg)
{
    int len = my_strlen(str);
    int base_len = my_strlen(base);
    int new_len = strt_end[1] - strt_end[0];
    long new_long = 0;

    for (int i = 0; i < new_len && i + strt_end[0] < len ; i++) {
        char c = str[i + strt_end[0]];
        int pow = power(base_len, new_len - i - 1);
        new_long += (long)get_pos_base(base, c) * (long)pow;
        if (!is_neg && new_long > 2147483647)
            return (0);
        else if (is_neg && new_long > 2147483648)
            return (0);
    }
    return (new_long);
}

static void chkn(char const *str, int *is_neg, int *strt_end, char const *base)
{
    int i = 0;
    char temp[2] = "a";

    temp[0] = str[i];
    while (str[i] != '\0' && (str[i] == '-' || str[i] == '+')) {
        if (str[i] == '-')
            *is_neg = *is_neg ? 0 : 1;
        i++;
        temp[0] = str[i];
    }
    strt_end[0] = i;
    while (str[i] != '\0' && my_strstr(base, temp) != 0) {
        i++;
        temp[0] = str[i];
    }
    strt_end[1] = i;
}

int my_getnbr_base(char const *str, char const *base)
{
    int is_neg = 0;
    int strt_end[2] = {0, 0};
    long nb;

    if (my_strlen(str) == 0 || my_strlen(base) == 0)
        return (0);
    chkn(str, &is_neg, strt_end, base);
    nb = sl_lg(str, strt_end, base, is_neg);
    if (!is_neg && strt_end[1] - strt_end[0] >= 32)
        return (0);
    if (is_neg && strt_end[1] - strt_end[0] > 32)
        return (0);
    return (is_neg ? (int)nb * (-1) : (int)nb);
}
