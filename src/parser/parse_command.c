/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** parse_command
*/

#include "shell.h"
#include "my_list.h"
#include "my.h"

char **line_to_array(char const *str);
void extend_array(char ***array, char *new_line);
void execute_command(sh_data_t *data);
command_t *malloc_command(void);
int handle_io_output(sh_data_t *data, char **options, bool *error);
int handle_io_output_append(sh_data_t *data, char **options, bool *error);
int handle_io_input(sh_data_t *data, char **options, bool *error);
int handle_io_input_line(sh_data_t *data, char **options, bool *error);
int handle_io_pipe(sh_data_t *data, char **options, bool *error);
int retrieve_io(sh_data_t *data);
void close_current_pipe(sh_data_t *data);
void close_other_pipe(sh_data_t *data);
void reset_data(sh_data_t *data);
int is_quote(int c);
void var_substitute(sh_data_t *data);

static const special_token_t TOKEN_LIST[] = {
    {">>", 2, &handle_io_output_append},
    {">", 1, &handle_io_output},
    {"<<", 2, &handle_io_input_line},
    {"<", 1, &handle_io_input},
    {"|", 1, &handle_io_pipe},
    {NULL, 0, NULL}
};

special_token_t get_io_token(const special_token_t *token_list, char *str)
{
    int i = 0;

    for (; token_list[i].size != 0; ++i)
        if (my_strncmp(str, token_list[i].name, token_list[i].size) == 0)
            return (token_list[i]);
    return (token_list[i]);
}

static char *remove_quote(char *str)
{
    if (str == NULL)
        return NULL;
    int len = my_strlen(str);
    if (len == 0 || !(str[0] == str[len - 1] && is_quote(str[0])))
        return str;
    char *new_str = malloc(sizeof(char) * len);
    my_strcpy(new_str, &str[1]);
    new_str[len - 2] = '\0';
    free(str);
    return new_str;
}

int parse_next_command(sh_data_t *data, char **line, bool *error)
{
    int i = 0;
    special_token_t io_token;
    data->current_command = malloc_command();
    while (line[i] != NULL && my_strcmp(line[i], ";") != 0) {
        io_token = get_io_token(TOKEN_LIST, line[i]);
        if (io_token.size == 0) {
            line[i] = remove_quote(line[i]);
            extend_array(&data->current_command->argv, line[i]);
            data->current_command->argc++;
            ++i;
            continue;
        }
        line[i + 1] = remove_quote(line[i + 1]);
        i += io_token.handler(data, &line[i + 1], error);
    }
    return (i + 1);
}

void init_command_execution(sh_data_t *data)
{
    reset_data(data);
    if (retrieve_io(data)) {
        data->last_exit_status = 1;
        return;
    }
    execute_command(data);
}

void parse_current_line(sh_data_t *data, char *line)
{
    line[my_strlen(line) - 1] = line[my_strlen(line) - 1] == '\n' ?
        '\0' : line[my_strlen(line) - 1];
    data->line = line_to_array(line);
    if (data->line == NULL || data->line[0] == NULL)
        return;
    var_substitute(data);
    int len = 0;
    bool error = false;
    for (; data->line[len] != NULL; len++);
    for (int i = 0; i < len ;) {
        i += parse_next_command(data, &data->line[i], &error);
        if (!error)
            init_command_execution(data);
        else {
            error = false;
            data->last_exit_status = 1;
        }
    }
}
