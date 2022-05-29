/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** mem_shell
*/

#include "shell.h"
#include "my.h"

sh_data_t *get_shell_data(sh_data_t *data);

void init_default_vars(sh_data_t *data)
{
    char env_path[PATH_MAX];
    char *term = get_env_value(data, "TERM");
    char *error = getcwd(env_path, PATH_MAX);
    set_var_value(data, "term", term ? term : "");
    set_var_value(data, "cwd", error ? env_path : "");
    set_var_value(data, "_", "");
    set_var_value(data, "status", "0");
}

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

void init_shell_data_2(sh_data_t *data)
{
    data->history = malloc(sizeof(char *));
    data->history[0] = NULL;
    data->history_index = 0;
}

sh_data_t *init_shell_data(char **envp)
{
    sh_data_t *data = malloc(sizeof(sh_data_t));
    if (data == NULL)
        return (NULL);
    data->vars = malloc(sizeof(char *) * 1);
    data->vars[0] = NULL;
    data->alias = malloc(sizeof(char *));
    data->alias[0] = NULL;
    data->envp = envp;
    data->envp = malloc_envp(data);
    data->old_pwd = my_strdup("");
    data->old_path = my_strdup("");
    data->execute_binary = 0;
    data->last_exit_status = 0;
    data->last_sig_status = 0;
    data->current_command = NULL;
    data->suspended_command = NULL;
    init_shell_data_2(data);
    init_default_vars(data);
    return (data);
}

void reset_data(sh_data_t *data)
{
    data->last_exit_status = 0;
    data->last_sig_status = 0;
}
