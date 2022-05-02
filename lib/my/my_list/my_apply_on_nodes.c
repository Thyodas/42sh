/*
** EPITECH PROJECT, 2021
** my_apply_on_nodes.c
** File description:
** my_apply_on_nodes
*/

#include <unistd.h>
#include "my_list.h"

int my_apply_on_nodes(linked_list_t *begin, void (*f)())
{
    linked_list_t *current = begin;

    while (current != NULL) {
        (*f)(current->data);
        current = current->next;
    }
    return (0);
}
