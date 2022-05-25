/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** command_error
*/

#include "my.h"
#include "shell.h"
#include <signal.h>

int execute_builtins(sh_data_t *data);
int execute_all_path_commands(sh_data_t *data);
int execute_path_command(sh_data_t *data, char *path);
void execute_binary(sh_data_t *data, char *path);

void print_signal_error(sh_data_t *data, int status)
{
    data->last_sig_status = WTERMSIG(status);
    switch (WTERMSIG(status)) {
        case SIGSEGV:
            my_fprintf(2, "Segmentation fault");
            data->last_exit_status = 139;
            break;
        case SIGFPE:
            my_fprintf(2, "Floating exception");
            data->last_exit_status = 136;
            break;
        case SIGINT:
            break;
        default:
            my_fprintf(2, strsignal(WTERMSIG(status)));
    }
    if (WCOREDUMP(status))
        my_fprintf(2, " (core dumped)\n");
    else
        my_fprintf(2, "\n");
}

void binary_error(sh_data_t *data, int status)
{
    if (WIFEXITED(status)) {
        data->last_exit_status = WEXITSTATUS(status);
    } else
        data->last_exit_status = 0;
    if (WIFSIGNALED(status)) {
        print_signal_error(data, status);
    }
    if (WIFSTOPPED(status)) {
        data->last_sig_status = WSTOPSIG(status);
        if (data->last_sig_status != SIGINT)
            my_fprintf(2, "%s\n", strsignal(WSTOPSIG(status)));
    }
}

int invalid_bin_access(char *path)
{
    struct stat sb;
    if (stat(path, &sb) == -1)
        return (0);
    if (access(path, 0 | F_OK) == 0
        && (access(path, 0 | X_OK) == -1 || S_ISDIR(sb.st_mode))) {
        my_fprintf(2, "%s: Permission denied.\n", path);
        return (1);
    }
    return (0);
}

bool can_execute_bin(char *path)
{
    struct stat sb;
    return (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR);
}

void check_execution(sh_data_t *data)
{
    if (data->current_command == NULL || data->current_command->argv == NULL
        || data->current_command->argv[0] == NULL)
        return;
    if (my_strstr(data->current_command->argv[0], "/") == NULL) {
        if (execute_builtins(data))
            return;
        if (execute_all_path_commands(data))
            return;
    } else {
        if (invalid_bin_access(data->current_command->argv[0])) {
            data->last_exit_status = 1;
            return;
        }
        if (can_execute_bin(data->current_command->argv[0])) {
            execute_binary(data, data->current_command->argv[0]);
            return;
        }
    }
    my_fprintf(2, "%s: Command not found.\n", data->current_command->argv[0]);
    data->last_exit_status = 1;
}
