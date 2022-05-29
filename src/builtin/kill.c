/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** kill.c
*/

#include "my.h"
#include "shell.h"
#include <signal.h>

command_t *get_command_by_index(sh_data_t *data, int index);

static int handle_kill_error(sh_data_t *data)
{
    if (data->current_command->argv[1] == NULL) {
        my_fprintf(2, "kill: Too few arguments.\n");
        return 1;
    }
    return 0;
}

static int print_kill_error(void)
{
    my_fprintf(2, "kill: Arguments should be jobs or process id's.\n");
    return 1;
}

static void kill_process(sh_data_t *data, command_t *command)
{
    linked_list_t *tmp = data->suspended_command;
    command_t *temp = tmp->data;
    if (temp->pid == command->pid) {
        data->suspended_command = data->suspended_command->next;
        kill(command->pid, SIGKILL);
        return;
    }
    linked_list_t *prev = tmp;
    tmp = tmp->next;
    while (tmp != NULL) {
        temp = tmp->data;
        if (temp->pid == command->pid) {
            prev->next = tmp->next;
            kill(command->pid, SIGKILL);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}

int kill_builtin(sh_data_t *data)
{
    if (handle_kill_error(data))
        return 1;
    char *arg = data->current_command->argv[1];
    if (!my_strcmp(arg, "%%") || !my_strcmp(arg, "%+")) {
        kill_process(data, data->suspended_command->data);
        return 0;
    } else if (!my_strcmp(arg, "%-")) {
        kill_process(data, data->suspended_command->next->data);
        return 0;
    }
    if (arg[0] == '%' && my_str_isnum(&arg[1])) {
        command_t *command = get_command_by_index(data, my_getnbr(&arg[1]));
        if (command == NULL)
            return 1;
        kill_process(data, command);
        return 0;
    }
    return print_kill_error();
}