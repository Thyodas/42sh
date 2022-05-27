/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** char_test
*/

int is_char_blank(char c)
{
    return (c == ' ' || c == '\n' || c == '\t');
}

int is_char_special(char c)
{
    return (c == '<' || c == '>' || c == '|' || c == ';');
}

int is_char_valid(char c)
{
    return (!is_char_special(c) && !is_char_blank(c) && c != '\0' && c != '\n');
}

int is_quote(int c)
{
    return (c == '\'' || c == '"' || c == '`');
}
