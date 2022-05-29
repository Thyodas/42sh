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
void writeFile(const char *filename, char *txt);

int(*ptr[])(sh_data_t *) = {
    history_delete, disp_hist, rev_disp_history,
    //write_in_history_file,
};

/*char *second_time()
{
    time_t rawtime = time(NULL);
    struct tm *time_info = localtime(&rawtime);
    char *clock = malloc(sizeof(char) * 7);
    int sec = time_info->tm_sec;
    time_info->tm_year
    int hour = time_info->tm_hour;
    int min = time_info->tm_min;
    if (hour < 10)
        sprintf(clock, "0%d:", hour);
    else
        sprintf(clock, "%d:", hour);
    if (min < 10)
        sprintf(clock + my_strlen(clock), "0%d\t", min);
    else
        sprintf(clock + my_strlen(clock), "%d\t", min);
    return clock;
}

int write_in_history_file(sh_data_t *data)
{
    char *txt = my_strdup("");
    char *time_s = second_time();
    int len = 0;
    int length = data->history_index;

    for (int i = 0; data->history[i] != NULL; i++)
        for (int j = 0; data->history[i][j] != '\0'; j++, len ++);
    
    writeFile(data->current_command->argv[2], txt);
    return 0;
}*/

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
