/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** main
*/

#include "my.h"
#include "shell.h"
#include "my_list.h"
#include "definitions.h"

static void my_shell_prompt(char **envp)
{
    sig_handler();
    sh_data_t *data = init_shell_data(envp);
    if (data == NULL)
        exit(84);
    data->is_prompt_mode = true;
    size_t len = 0;
    ssize_t lineSize = 0;
    while (1) {
        char *line = NULL;
        print_prompt(data);
        lineSize = getline(&line, &len, stdin);
        if (lineSize == EOF)
            default_shell_exit();
        if (line[0] == '\n') {
            free(line);
            continue;
        }
        parse_current_line(data, line);
        free(line);
    }
}

static int my_shell_pipe(char **envp)
{
    sh_data_t *data = init_shell_data(envp);
    data->is_prompt_mode = false;
    if (data == NULL)
        exit(84);
    size_t len = 0;
    ssize_t lineSize = 0;
    while (1) {
        char *line = NULL;
        lineSize = getline(&line, &len, stdin);
        if (lineSize == EOF)
            break;
        if (line[0] == '\n') {
            free(line);
            continue;
        }
        parse_current_line(data, line);
        free(line);
    }
    return (data->last_exit_status);
}

int main(int argc, char **argv, char **envp)
{
    if (argc > 1 || argv == NULL)
        return (84);
    if (isatty(0))
        my_shell_prompt(envp);
    else
        return (my_shell_pipe(envp));
    return (0);
}
