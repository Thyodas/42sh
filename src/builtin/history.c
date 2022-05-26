/*
** EPITECH PROJECT, 2022
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** history
*/

#include "my.h"
#include "shell.h"
int my_nbr_len(int nb)
{
    int res = 0;

    for(; nb > 0; res++)
        nb = nb / 10;
    return res;
}

static int history(sh_data_t *data)
{
    int len = 0;
    int space = 1;
    int history_len = 0;

    for (;data->history[len] != NULL; len++);
    history_len = my_nbr_len(len);
    for (int i = 0; data->history[i] != NULL; i++) {
        if (i == 0)
            space = history_len - my_nbr_len(i);
        else
            space = history_len - my_nbr_len(i) + 1;
        for (; space > 0; space--)
            my_putchar(' ');
        my_put_nbr(i);
        my_putstr("  ");
        //time
        // my_putstr("  ");
        my_printf("%s\n", data->history[i]);
    }
    return 0;
}

static int history_n(sh_data_t *data, int n)
{
    int len = 0;
    int space = 1;
    int history_len = 0;

    for (;data->history[len] != NULL; len++);
    history_len = my_nbr_len(len);
    for (int i = 0; i < n && !data->history[i]; i++) {
        if (i == 0)
            space = history_len - my_nbr_len(i) - 1;
        else
            space = history_len - my_nbr_len(i) + 1;
        for (; space > 0; space--)
            my_putchar(' ');
        my_put_nbr(i);
        my_putstr("  ");
        //time
        // my_putstr("  ");
        my_printf("%s\n", data->history[i]);
    }
    return 0;
}

int builtin_history(sh_data_t *data)
{
    if (data->current_command->argc > 2) {
        my_fprintf(2, "history: Too many arguments.\n");
        return (1);
    }
    if (data->current_command->argc == 1)
        return (history(data));
    if (my_str_isnum(data->current_command->argv[1]) == 0) {
        int n = my_getnbr(data->current_command->argv[1]);
        return (history_n(data, n));
    }
    return 0;
}