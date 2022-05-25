/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** where
*/

#include "shell.h"
#include "my.h"

char *concat_path_binary(char *path, char *binary)
{
    int path_size = my_strlen(path);
    char *new_path = malloc(path_size
        + my_strlen(binary) + 2);
    my_strcpy(new_path, path);
    new_path[path_size] = '/';
    my_strcpy(new_path + path_size + 1, binary);
    new_path[path_size + my_strlen(binary) + 1] = '\0';
    return (new_path);
}

int print_paths_for_binary(sh_data_t *data, char *binary)
{
    char *env_path = get_env_value(data, "PATH");
    if (env_path == NULL)
        env_path = data->old_path;
    env_path = my_strdup(env_path);
    char *token = strtok(env_path, ":");
    char *new_path;
    bool found = false;
    while (token != NULL) {
        new_path = concat_path_binary(token, binary);
        if (can_execute_bin(new_path)) {
            my_printf("%s\n", new_path);
            found = true;
        }
        token = strtok(NULL, ":");
    }
    free(env_path);
    return (found);
}

int builtin_where(sh_data_t *data)
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
        if (!print_paths_for_binary(data, data->current_command->argv[i]))
            found = false;
    return (found ? 0 : 1);
}
