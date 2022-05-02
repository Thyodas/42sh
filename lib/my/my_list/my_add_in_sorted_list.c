/*
** EPITECH PROJECT, 2021
** my_add_in_sorted_list.c
** File description:
** my_add_in_sorted_list
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_list.h"

int my_add_node(void *data, linked_list_t **next_list);

void my_sort_list(linked_list_t **begin, int (*cmp)());

void my_add_in_sorted_list(linked_list_t **begin, void *data, int (*cmp)())
{
    linked_list_t *new = malloc(sizeof(linked_list_t));
    linked_list_t *current = *begin;

    new->data = data;
    new->next = NULL;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new;
    my_sort_list(&(*begin), cmp);
}
