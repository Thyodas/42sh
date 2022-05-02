/*
** EPITECH PROJECT, 2021
** my_rev_list.c
** File description:
** my_rev_list
*/

#include <unistd.h>
#include "my_list.h"

void my_rev_list(linked_list_t **begin)
{
    linked_list_t *previous = NULL;
    linked_list_t *next_tmp = NULL;
    linked_list_t *current = *begin;

    while (current != NULL) {
        next_tmp = current->next;
        current->next = previous;
        previous = current;
        current = next_tmp;
    }
    *begin = previous;
}
