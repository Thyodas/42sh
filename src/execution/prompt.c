/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** prompt
*/

#include "my.h"
#include "shell.h"

static const char *SIG_NAME[] = {
    "HUP",
    "INT",
    "QUIT",
    "ILL",
    "TRAP",
    "ABRT",
    "",
    "FPE",
    "KILL",
    "",
    "SEGV",
    "",
    "PIPE",
    "ALRM",
    "TERM"
};

void print_prompt(sh_data_t *data)
{
    char current_path[PATH_MAX] = {0};
    my_printf("\033[90m╭─ \033[94m");
    getcwd(current_path, PATH_MAX);
    my_printf("\033[94m\033[1m📂 %s", current_path);
    my_printf(" \033[0m\033[90m────────────────────────── ");
    if (data->last_exit_status != 0) {
        data->last_sig_status - 1 > 0 && data->last_sig_status - 1 <= 15 ?
            my_printf("\033[31m✘ %s", SIG_NAME[data->last_sig_status - 1])
            : my_printf("\033[31m✘ %d", data->last_exit_status);
        my_printf("\n\033[0m\033[90m╰─\033[31m❯\033[0m ");
    } else {
        my_printf("\033[32m✔");
        my_printf("\n\033[0m\033[90m╰─\033[32m❯\033[0m ");
    }
}
