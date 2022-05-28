/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** shell
*/

#ifndef SHELL_H_
    #define SHELL_H_

    #include <stdio.h>
    #include <unistd.h>
    #include <limits.h>
    #include <string.h>
    #include <stdbool.h>
    #include <stdlib.h>

    #include <sys/types.h>
    #include <sys/time.h>
    #include <sys/resource.h>
    #include <sys/wait.h>
    #include <sys/stat.h>

    #include <errno.h>

    typedef struct command_s {
        char **argv;
        int argc;
        int read_fd;
        int write_fd;
        int output_type;
        int input_type;
        char *output_option;
        char *input_option;
        struct command_s *pipe_next;
        struct command_s *pipe_prev;
    } command_t;

    enum {
        T_OUTPUT_APPEND,
        T_OUTPUT_NORMAL,
        T_INPUT_LINE,
        T_INPUT_NORMAL,
        T_OUTPUT_PIPE,
        T_INPUT_PIPE
    };

    enum {
        T_NONE,
        T_BASIC,
        T_AND,
        T_OR
    };

    #define HEREDOC_TEMP_FILE "/tmp/mysh_heredoc.tmp"

    typedef struct {
        char **vars;
        char **envp;
        char **line;
        char *old_pwd;
        char *old_path;
        int last_exit_status;
        int last_sig_status;
        pid_t child_pid;
        bool is_prompt_mode;
        bool execute_binary;
        command_t *current_command;
    } sh_data_t;

    typedef struct {
        char *name;
        int (*execute)(sh_data_t *data);
    } builtin_t;

    typedef struct {
        char *name;
        int size;
        int (*handler)(sh_data_t *data, char **options, bool *error);
    } special_token_t;

    #include "definitions.h"

    static const builtin_t BUILTIN_JUMP_TABLE[] = {
        {"cd", &builtin_cd},
        {"setenv", &builtin_setenv},
        {"unsetenv", &builtin_unsetenv},
        {"set", &builtin_set},
        {"unset", &builtin_unset},
        {"env", &builtin_env},
        {"exit", &builtin_exit},
        {"where", &builtin_where},
        {"which", &builtin_which},
        {"repeat", &builtin_repeat}
    };

    #define BUILTIN_NB (sizeof(BUILTIN_JUMP_TABLE) / sizeof(builtin_t))

#endif /* !SHELL_H_ */
