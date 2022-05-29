/*
** EPITECH PROJECT, 2022
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** history_flag
*/

#include "my.h"
#include "shell.h"
#include <time.h>

int rev_disp_history(sh_data_t *data);
int disp_history_n(sh_data_t *data, int n);
int history_delete(sh_data_t *data);
int my_nbrlen(int nbr);
int disp_hist(sh_data_t *data);
int write_in_history_file(sh_data_t *data);
int disp_hist(sh_data_t *data);
void write_file(const char *filename, char *txt);

int(*ptr[])(sh_data_t *) = {
    history_delete, disp_hist, rev_disp_history,
};

int history_flag(sh_data_t *data)
{
    char flag[] = {'c', 'h', 'r'};

    for (int h = 0; flag[h] != '\0'; h++) {
        if (flag[h] == data->current_command->argv[1][1])
            return ptr[h](data);
    }
    if (data->current_command->argc == 2) {
        my_fprintf(2, "Usage: history [-chrSLMT] [# number of events].\n");
        return 1;
    }
    if (data->current_command->argc > 2) {
        my_fprintf(2, "history: Badly formed number.\n");
        return 1;
    }
    return 0;
}
