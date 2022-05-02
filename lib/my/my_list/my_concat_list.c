/*
** EPITECH PROJECT, 2021
** my_concat_list.c
** File description:
** my_concat_list
*/

#include <unistd.h>
#include "my_list.h"

void my_concat_list(linked_list_t **begin1, linked_list_t *begin2)
{
    linked_list_t *current = *begin1;

    if (current == NULL)
        *begin1 = begin2;
    else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = begin2;
    }
}
