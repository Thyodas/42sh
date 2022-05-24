/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** definitions
*/

#ifndef DEFINITIONS_H_
    #define DEFINITIONS_H_

    /*
    Memory management
    */
    // memory/mem_shell.c
    sh_data_t *init_shell_data(char **envp);

    /*
    Builtins
    */
    // builtin/cd.c
    int builtin_cd(sh_data_t *data);

    // builtin/setenv.c
    void set_env_value(sh_data_t *data, char *name, char *value);
    int builtin_setenv(sh_data_t *data);

    // builtin/set.c
    void set_var_value(sh_data_t *data, char *name, char *value);
    int builtin_set(sh_data_t *data);

    // builtin/setenv.c
    void set_env_value(sh_data_t *data, char *name, char *value);
    int builtin_setenv(sh_data_t *data);

    // builtin/exit.c
    void default_shell_exit(void);
    int builtin_exit(sh_data_t *data);

    // builtin/unsetenv.c
    void unset_env_value(sh_data_t *data, char *name);
    int builtin_unsetenv(sh_data_t *data);

    // builtin/unset.c
    void unset_var_value(sh_data_t *data, char *name);
    int builtin_unset(sh_data_t *data);

    // builtin/env.c
    int builtin_env(sh_data_t *data);

    /*
    Execution
    */
    // execution/command.c
    void parse_current_line(sh_data_t *data, char *line);

    // execution/env_utils.c
    int get_env_size(sh_data_t *data);
    int get_env_line_pos(sh_data_t *data, char *name);
    char *get_env_value(sh_data_t *data, char *name);
    char *create_env_line(char *name, char *value);

    // execution/var_utils.c
    int get_var_size(sh_data_t *data);
    int get_var_line_pos(sh_data_t *data, char *name);
    char *get_var_value(sh_data_t *data, char *name);
    char *create_var_line(char *name, char *value);

    // execution/signal.c
    void sig_handler(void);

    // execution/command_error.c
    void binary_error(sh_data_t *data, int status);

    // execution/builtin_utils.c
    builtin_t search_builtin(sh_data_t *data);

    // execution/prompt.c
    void print_simple_prompt(void);
    void print_prompt(sh_data_t *data);

    // execution/access.c
    int invalid_bin_access(char *path);

#endif /* !DEFINITIONS_H_ */
