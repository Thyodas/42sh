/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** parse_command
*/

#include "shell.h"
#include "my_list.h"
#include "my.h"
#include "time.h"

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
int handle_separators(sh_data_t *data, char **options, bool *error,
                        const special_token_t *token_list);
int check_if_separator(char *str);
special_token_t get_io_token(const special_token_t *token_list, char *str);
char *remove_quote(char *str);
char *history_maker(char **line, int length, int len, char *clock);

static const special_token_t TOKEN_LIST[] = {
    {">>", 2, &handle_io_output_append},
    {">", 1, &handle_io_output},
    {"<<", 2, &handle_io_input_line},
    {"<", 1, &handle_io_input},
    {"|", 1, &handle_io_pipe},
    {NULL, 0, NULL}
};

static void fill_command_args(sh_data_t *data, char *str, int *i)
{
    str = remove_quote(str);
    extend_array(&data->current_command->argv, str);
    data->current_command->argc++;
    *i = *i + 1;
}

static int parse_next_command(sh_data_t *data, char **line, bool *error)
{
    int i = 0;
    special_token_t io_token;
    data->current_command = malloc_command();
    while (line[i] != NULL) {
        if (check_if_separator(line[i]))
            return i;
        io_token = get_io_token(TOKEN_LIST, line[i]);
        if (io_token.size == 0) {
            fill_command_args(data, line[i], &i);
            continue;
        }
        line[i + 1] = remove_quote(line[i + 1]);
        i += io_token.handler(data, &line[i + 1], error);
    }
    return (i + 1);
}

static void init_command_execution(sh_data_t *data)
{
    reset_data(data);
    if (retrieve_io(data)) {
        data->last_exit_status = 1;
        return;
    }
    execute_command(data);
}

static void parse_command_and_exec(sh_data_t *data, int len)
{
    bool error = false;
    for (int i = 0; i < len ;) {
        if (check_if_separator(data->line[i])) {
            i += handle_separators(data, &data->line[i], &error, TOKEN_LIST);
            continue;
        }
        i += parse_next_command(data, &data->line[i], &error);
        if (!error)
            init_command_execution(data);
        else {
            error = false;
            data->last_exit_status = 1;
        }
    }
}

char *my_itoa(int nb)
{
    int len = 0;
    char *str = NULL;
    int neg = (nb < 0) ? -1 : 1;

    nb *= neg;
    if (nb == 0)
        return ("0");
    for (int tmp = nb ; tmp > 0; ++len)
        tmp /= 10;
    str = malloc(sizeof(char) * (len + 1));
    str[len] = '\0';
    if (neg == -1)
        str[0] = '-';
    for (; len--; nb /= 10) {
        if (neg == -1)
            str[len + 1] = nb % 10  + '0';
        else
            str[len] = nb % 10  + '0';
    }
    return (str);
}

char *command_time()
{
    time_t rawtime = time(NULL);
    struct tm *time_info = localtime(&rawtime);
    char *clock = malloc(sizeof(char) * 8);
    int hour = time_info->tm_hour;
    int min = time_info->tm_min;
    clock = my_strcat(clock, my_itoa(hour));
    clock = my_strcat(clock, ":");
    clock = my_strcat(clock, my_itoa(min));
    clock = my_strcat(clock, "\t\0");
    return clock;
}

void parse_current_line(sh_data_t *data, char *line)
{
    char *last_command = my_strdup("");
    char *time = command_time();

    line[my_strlen(line) - 1] = line[my_strlen(line) - 1] == '\n' ?
        '\0' : line[my_strlen(line) - 1];
    data->line = line_to_array(line);
    if (data->line == NULL || data->line[0] == NULL)
        return;
    int len = 0;
    int length = 0;
    for (; data->line[len] != NULL; len++)
        for (int i = 0; data->line[len][i] != '\0'; i++, length++);
    length += len + 1;
    length += my_strlen(time);
    last_command = history_maker(data->line, length, len, time);
    extend_array(&data->history, last_command);
    data->history_index++;
    parse_command_and_exec(data, len);
}
