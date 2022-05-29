/*
** EPITECH PROJECT, 2021
** B-PSU-210-STG-2-1-42sh-guillaume.hein
** File description:
** globbings.h
*/

#ifndef GLOBBINGS_H
    #define GLOBBINGS_H

    typedef struct globbings {
        int pos_square_open;
        int pos_square_close;
        int size_square;
        char *inside_square;
        char *char_replacable;
        int pos_char;
        int pos_bracket_open;
        int pos_bracket_close;
        int size_bracket;
        char *inside_bracket;
        int pos_str;
        char **str_replacable;
    } globbings_t;

#endif