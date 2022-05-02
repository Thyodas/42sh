/*
** EPITECH PROJECT, 2021
** my_apply_on_matching_nodes.c
** File description:
** my_apply_on_matching_nodes
*/

#include "my_list.h"
#include <unistd.h>

int my_apply_on_matching_nodes(linked_list_t *begin, int (*f)(),
void const *data_ref, int (*cmp)())
{
    linked_list_t *current = begin;

    while (current != NULL) {
        if ((*cmp)(current->data, data_ref) == 0)
            (*f)(current->data);
        current = current->next;
    }
    return (0);
}
