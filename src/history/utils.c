/*
** EPITECH PROJECT, 2022
** B-PSU-210
** File description:
** utils
*/

#include "my.h"
#include "shell.h"

int my_nbrlen(int nb);

static void is_printable(char *line, int tab, int j)
{
    if (tab == 1 && line[j] == '\t') {
        j++;
        for (int i = j; line[i] != '\0'; i++) {
            my_putchar(line[i]);
        }
        my_putchar('\n');
    }
}

int disp_hist(sh_data_t *data)
{
    int tab = 0;
    for (int i = 0; data->history[i] != NULL; i++) {
        for (int j = 0; data->history[i][j] != '\0'; j++) {
            (data->history[i][j] == '\t') ? tab++ : 0;
            is_printable(data->history[i], tab, j);
        }
        tab = 0;
    }
    return 0;
}

int rev_disp_history(sh_data_t *data)
{
    int len = 0;
    int space = 0;
    int history_len = 0;

    for (;data->history[len] != NULL; len++);
    history_len = my_nbrlen(len) + 1;
    int nbr = data->history_index;
    for (int i = len - 1; i >= 0; i--, nbr--) {
        if (i == 0)
            space = history_len - my_nbrlen(i) - 1;
        else
            space = history_len - my_nbrlen(i);
        for (; space > 0; space--)
            my_putchar(' ');
        my_put_nbr(nbr);
        my_putchar('\t');
        my_printf("%s\n", data->history[i]);
    }
    return 0;
}

int disp_history_n(sh_data_t *data, int n)
{
    int len = 0;
    int space = 1;
    int history_len = 0;

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

int history_delete(sh_data_t *data)
{
    for (int i = 0; data->history[i] != NULL; i++)
        free(data->history[i]);
    free(data->history);
    data->history = malloc(sizeof(char *));
    data->history[0] = my_strdup("");
    if (data->current_command->argc > 2
    && my_str_isnum(data->current_command->argv[2]) == 0)
        my_fprintf(2, "history: Badly formed number.\n");
    return 0;
}
