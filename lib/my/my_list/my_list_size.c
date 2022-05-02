/*
** EPITECH PROJECT, 2021
** my_list_size.c
** File description:
** my_list_size
*/

#include <unistd.h>
#include "my_list.h"

int my_list_size(linked_list_t const *begin)
{
    int counter = 0;

    while (begin != NULL) {
        counter++;
        begin = begin->next;
    }
    return (counter);
}
