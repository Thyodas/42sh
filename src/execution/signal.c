/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** signal
*/

#include "my.h"
#include "shell.h"
#include <signal.h>

void print_prompt(sh_data_t *data);

sh_data_t *get_shell_data(sh_data_t *data)
{
    static sh_data_t *temp_data = NULL;
    if (data == NULL)
        return (temp_data);
    else {
        temp_data = data;
        return data;
    }
}

void handle_interrupt(__attribute__((unused)) int signal)
{
    sh_data_t *data = get_shell_data(NULL);
    if (data == NULL)
        return;
    data->last_sig_status = SIGINT;
    data->last_exit_status = 1;
    my_putchar('\n');
    print_prompt(data);
    return;
}

void handle_stop_in_main(__attribute__((unused)) int signal)
{
    return;
}

void sig_handler(void)
{
    signal(SIGINT, handle_interrupt);
    signal(SIGTSTP, handle_stop_in_main);
    signal(SIGCONT, SIG_DFL);
}
