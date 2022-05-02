/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** mem_shell
*/

#include "shell.h"
#include "my.h"

sh_data_t *get_shell_data(sh_data_t *data);

static char **malloc_envp(sh_data_t *data)
{
    int len = get_env_size(data);
    char **new_env = malloc(sizeof(char *) * (len + 1));
    if (new_env == NULL)
        exit(84);
    for (int i = 0 ; data->envp[i] != NULL ; i++) {
        new_env[i] = my_strdup(data->envp[i]);
        if (new_env[i] == NULL)
            exit(84);
    }
    new_env[len] = NULL;
    return (new_env);
}

command_t *malloc_command(void)
{
    command_t *command = malloc(sizeof(command_t));
    command->argv = malloc(sizeof(char *));
    command->argv[0] = NULL;
    command->argc = 0;
    command->read_fd = 0;
    command->write_fd = 1;
    command->input_type = -1;
    command->output_type = -1;
    command->pipe_next = NULL;
    command->pipe_prev = NULL;
    return command;
}

sh_data_t *init_shell_data(char **envp)
{
    sh_data_t *data = malloc(sizeof(sh_data_t));
    if (data == NULL)
        return (NULL);
    data->envp = envp;
    data->envp = malloc_envp(data);
    data->old_pwd = my_strdup("");
    data->old_path = my_strdup("");
    data->execute_binary = 0;
    data->last_exit_status = 0;
    data->last_sig_status = 0;
    data->current_command = NULL;
    get_shell_data(data);
    return (data);
}

void reset_data(sh_data_t *data)
{
    data->last_exit_status = 0;
    data->last_sig_status = 0;
}
