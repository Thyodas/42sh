/*
** EPITECH PROJECT, 2022
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** history
*/

#include "my.h"
#include "shell.h"

int history_flag(sh_data_t *data);

int my_nbrlen(int nb)
{
    int res = 0;

    for(; nb > 0; res++)
        nb = nb / 10;
    return res;
}

char *history_maker(char **line, int length, int len, char *clock)
{
    char *dest = malloc(sizeof(char) * (length + len + 2));

    dest = my_strcat(dest, clock);
    for (int i = 0; line[i] != NULL; i++) {
        dest = my_strcat(dest, line[i]);
        dest = my_strcat(dest, " ");
    }
    return dest;
}

static int disp_history(sh_data_t *data)
{
    int len = 0;
    int space = 0;
    int history_len = 0;

    for (;data->history[len] != NULL; len++);
    history_len = my_nbrlen(len) + 1;
    int nbr = data->history_index - len;
    for (int i = 0; data->history[i] != NULL; i++, nbr++) {
        if (i == 0)
            space = history_len - my_nbrlen(i) - 1;
        else
            space = history_len - my_nbrlen(i);
        for (; space > 0; space--)
            my_putchar(' ');
        my_put_nbr(nbr + 1);
        my_putchar('\t');
        my_printf("%s\n", data->history[i]);
    }
    return 0;
}

static int disp_history_n(sh_data_t *data, int n)
{
    int len = 0;
    int space = 1;
    int history_len = 0;
    int index = data->history_index;

    for (;data->history[len] != NULL; len++);
    history_len = my_nbrlen(len);
    int nbr = data->history_index - len;
    for (int i = len - n; data->history[i] != NULL; i++, nbr++) {
        if (i == 0)
            space = history_len - my_nbrlen(i);
        else
            space = history_len - my_nbrlen(i) + 1;
        for (; space > 0; space--)
            my_putchar(' ');
        my_put_nbr(nbr + 1);
        my_putchar('\t');
        my_printf("%s\n", data->history[i]);
    }
    return 0;
}

int builtin_history(sh_data_t *data)
{
    if (data->current_command->argc > 3) {
        my_fprintf(2, "history: Too many arguments.\n");
        return (1);
    }
    if (data->current_command->argc == 1)
        return (disp_history(data));
    if (my_str_isnum(data->current_command->argv[1]) == 1
        && data->current_command->argc == 2) {
        int n = my_getnbr(data->current_command->argv[1]);
        return (disp_history_n(data, n));
    }
    return history_flag(data);
}