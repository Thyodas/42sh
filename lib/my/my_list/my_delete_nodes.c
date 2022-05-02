/*
** EPITECH PROJECT, 2021
** my_delete_nodes.c
** File description:
** my_delete_nodes
*/

#include "my_list.h"
#include <unistd.h>
#include <stdlib.h>

static void my_delete_rec(linked_list_t **begin, void const *data_ref,
int (*cmp)(), linked_list_t *previous)
{
    linked_list_t *current = *begin;

    if (current == NULL) {
        if (previous != NULL) {
            previous->next = NULL;
        }
        return;
    }
    if ((*cmp)(current->data, data_ref) == 0) {
        if (previous != NULL) {
            previous->next = current->next;
            my_delete_rec(&(current->next), data_ref, cmp, previous);
        } else {
            *begin = (*begin)->next;
            my_delete_rec(begin, data_ref, cmp, previous);
        }
        free(current);
        return;
    }
    my_delete_rec(&(current->next), data_ref, cmp, current);
}

int my_delete_nodes(linked_list_t **begin, void const *data_ref, int (*cmp)())
{
    linked_list_t *previous = NULL;

    my_delete_rec(begin, data_ref, cmp, previous);
    return (0);
}
