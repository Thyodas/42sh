/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** jobs.c
*/

#include "my.h"
#include "shell.h"

int size_command_list(sh_data_t *data);

static void print_args(command_t *command)
{
    if (command->pipe_next != NULL) {
        print_args(command->pipe_next);
        printf("| ");
    }
    for (int i = 0; command->argv[i] != 0; ++i)
        printf("%s ", command->argv[i]);
}

static void print_jobs(linked_list_t *suspended_command, sh_data_t *data,
                        int size, int pos)
{
    if (suspended_command->next != NULL)
        print_jobs(suspended_command->next, data, size, pos++);
    command_t *command = suspended_command->data;
    printf("[%d]\t", pos);
    if (size == pos)
        printf("+");
    else if (pos == size - 1)
        printf("-");
    else
        printf(" ");
    printf(" Suspended\t");
    print_args(command);
    printf("\n");
}

int jobs(sh_data_t *data)
{
    if (data->current_command->argv[1] != NULL) {
        my_fprintf(2, "Usage: jobs.\n");
        return 1;
    }
    if (data->suspended_command == NULL)
        return 0;
    int size = size_command_list(data);
    print_jobs(data->suspended_command, data, size, 1);
    return 0;
}
