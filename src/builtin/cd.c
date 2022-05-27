/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** cd
*/

#include "my.h"
#include "shell.h"

static void change_old_pwd(sh_data_t *data, char *old_pwd)
{
    free(data->old_pwd);
    data->old_pwd = my_strdup(old_pwd);
    set_env_value(data, "OLDPWD", data->old_pwd);
}

static int cd_back(sh_data_t *data)
{
    if (data->current_command->argc > 2
        || data->current_command->argv[1][1] != '\0') {
        my_fprintf(2, "Usage: cd [-plvn][-|<dir>].");
        return (1);
    }
    char env_path[PATH_MAX];
    getcwd(env_path, PATH_MAX);
    if (chdir(data->old_pwd) == -1) {
        my_fprintf(2, "%s: %s.\n", data->old_pwd, strerror(errno));
        return (1);
    }
    change_old_pwd(data, env_path);
    set_env_value(data, "PWD", getcwd(env_path, PATH_MAX));
    set_var_value(data, "cwd", getcwd(env_path, PATH_MAX));
    return (0);
}

static int cd_home(sh_data_t *data)
{
    char *path = get_env_value(data, "HOME");
    char env_path[PATH_MAX];
    getcwd(env_path, PATH_MAX);
    if (chdir(path) == -1) {
        my_fprintf(2, "cd: Can't change to home directory.\n");
        return (1);
    }
    change_old_pwd(data, env_path);
    set_env_value(data, "PWD", getcwd(env_path, PATH_MAX));
    set_var_value(data, "cwd", getcwd(env_path, PATH_MAX));
    return (0);
}

int builtin_cd(sh_data_t *data)
{
    if (data->current_command->argc > 2) {
        my_fprintf(2, "cd: Too many arguments.\n");
        return (1);
    }
    if (data->current_command->argc == 1)
        return (cd_home(data));
    if (data->current_command->argv[1][0] == '-')
        return (cd_back(data));
    char env_path[PATH_MAX];
    getcwd(env_path, PATH_MAX);
    if (chdir(data->current_command->argv[1]) == -1) {
        my_fprintf(2, "%s: %s.\n", data->current_command->argv[1],
            strerror(errno));
        return (1);
    }
    change_old_pwd(data, env_path);
    set_env_value(data, "PWD", getcwd(env_path, PATH_MAX));
    set_var_value(data, "cwd", getcwd(env_path, PATH_MAX));
    return (0);
}
