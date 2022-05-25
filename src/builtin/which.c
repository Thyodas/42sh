/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** where
*/

#include "shell.h"
#include "my.h"

char *concat_path_binary(char *path, char *binary);

static int print_paths_for_binary(sh_data_t *data, char *binary)
{
    char *env_path = get_env_value(data, "PATH");
    if (env_path == NULL)
        env_path = data->old_path;
    env_path = my_strdup(env_path);
    char *token = strtok(env_path, ":");
    char *new_path;
    while (token != NULL) {
        new_path = concat_path_binary(token, binary);
        if (can_execute_bin(new_path)) {
            my_printf("%s\n", new_path);
            free(env_path);
            return (true);
        }
        token = strtok(NULL, ":");
    }
    free(env_path);
    return (false);
}

int builtin_which(sh_data_t *data)
{
    if (data->current_command->argc == 1) {
        my_fprintf(2, "%s: Too few arguments.\n",
            data->current_command->argv[0]);
        return (1);
    }
    bool found = true;
    for (int i = 1; i < data->current_command->argc; ++i)
        if (my_strstr(data->current_command->argv[i], "/") != NULL) {
            my_fprintf(2, "%s: / in command makes no sense\n",
                data->current_command->argv[0]);
            return (1);
        }
    for (int i = 1; i < data->current_command->argc; ++i)
        if (!print_paths_for_binary(data, data->current_command->argv[i])) {
            found = false;
            my_fprintf(2, "%s: Command not found.\n",
                data->current_command->argv[i]);
        }
    return (found ? 0 : 1);
}
