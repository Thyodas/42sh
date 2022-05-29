/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** command
*/

#include <signal.h>
#include "shell.h"
#include "my_list.h"
#include "my.h"
#include <signal.h>

int retrieve_io(sh_data_t *data);
void close_other_pipe(sh_data_t *data);
void close_current_pipe(sh_data_t *data);
void execute_command(sh_data_t *data);
void execute_pipe_next(sh_data_t *data);
bool can_execute_bin(char *path);
void check_execution(sh_data_t *data);
void handle_pid(sh_data_t *data, int status);

void execute_binary(sh_data_t *data, char *path)
{
    int status = 0;
    data->child_pid = fork();
    if (data->child_pid == -1)
        exit(84);
    if (data->child_pid == 0) {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        execute_pipe_next(data);
        dup2(data->current_command->write_fd, 1);
        dup2(data->current_command->read_fd, 0);
        if (execve(path, data->current_command->argv, data->envp) == -1) {
            (errno == ENOEXEC) ?
            my_fprintf(2, "%s: Exec format error. Wrong Architecture.\n", path)
            : perror(path);
            exit(1);
        }
        exit(0);
    }
    handle_pid(data, status);
}

int execute_path_command(sh_data_t *data, char *path)
{
    int path_size = my_strlen(path);
    char *new_path = malloc(path_size
        + my_strlen(data->current_command->argv[0]) + 2);
    my_strcpy(new_path, path);
    new_path[path_size] = '/';
    my_strcpy(new_path + path_size + 1, data->current_command->argv[0]);
    new_path[path_size + my_strlen(data->current_command->argv[0]) + 1] = '\0';
    if (can_execute_bin(new_path)) {
        execute_binary(data, new_path);
        free(new_path);
        return (1);
    }
    free(new_path);
    return (0);
}

int execute_all_path_commands(sh_data_t *data)
{
    char *env_path = get_env_value(data, "PATH");
    if (env_path == NULL)
        env_path = data->old_path;
    env_path = my_strdup(env_path);
    char *token = strtok(env_path, ":");
    while (token != NULL) {
        if (execute_path_command(data, token)) {
            free(env_path);
            return (1);
        }
        token = strtok(NULL, ":");
    }
    free(env_path);
    return (0);
}

int execute_builtins(sh_data_t *data)
{
    int old_stdout_fd;
    builtin_t builtin = search_builtin(data);
    if (builtin.name != NULL) {
        if (data->current_command->write_fd != 1) {
            old_stdout_fd = dup(1);
            dup2(data->current_command->write_fd, 1);
        }
        data->last_exit_status = builtin.execute(data);
        if (data->current_command->write_fd != 1)
            dup2(old_stdout_fd, 1);
        if (data->current_command->pipe_next != NULL) {
            execute_pipe_next(data);
            int status;
            wait(&status);
        }
        return 1;
    }
    return 0;
}

void execute_command(sh_data_t *data)
{
    check_execution(data);
    if (data->current_command->read_fd != 0)
        close(data->current_command->read_fd);
    if (data->current_command->write_fd != 1)
        close(data->current_command->write_fd);
}
