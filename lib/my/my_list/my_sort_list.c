/*
** EPITECH PROJECT, 2021
** my_sort_list.c
** File description:
** my_sort_list
*/

#include <stdlib.h>
#include "my_list.h"

int my_list_size(linked_list_t const *begin);

static linked_list_t *get_i(linked_list_t *begin, int index)
{
    linked_list_t *current = begin;

    for (int i = 0 ; i < index ; i++) {
        current = current->next;
    }
    return (current);
}

static void my_swap(linked_list_t *begin, int pos1, int pos2, int (*cmp)())
{
    void *temp;

    if ((*cmp)(get_i(begin, pos1)->data, get_i(begin, pos2)->data) < 0) {
        temp = get_i(begin, pos1)->data;
        get_i(begin, pos1)->data = get_i(begin, pos2)->data;
        get_i(begin, pos2)->data = temp;
    }
}

void my_sort_list(linked_list_t **begin, int (*cmp)())
{
    int size = my_list_size(*begin);

    for (int i = size ; i > 0 ; i--) {
        for (int j = 0 ; j < i - 1 ; j++) {
            my_swap(*begin, j + 1, j, cmp);
        }
    }
}
