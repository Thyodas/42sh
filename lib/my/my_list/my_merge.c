/*
** EPITECH PROJECT, 2021
** my_merge.c
** File description:
** my_merge
*/

#include <stdlib.h>
#include <unistd.h>
#include "my_list.h"

void my_concat_list(linked_list_t **begin1, linked_list_t *begin2);

void my_sort_list(linked_list_t **begin, int (*cmp)());

void my_merge(linked_list_t **begin1, linked_list_t *begin2, int (*cmp)())
{
    my_concat_list(&(*begin1), begin2);
    my_sort_list(&(*begin1), cmp);
}
