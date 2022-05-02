/*
** EPITECH PROJECT, 2021
** my_params_to_list.c
** File description:
** my_params_to_list
*/

#include <unistd.h>
#include <stdlib.h>
#include "my_list.h"

int my_add_node(void *data, linked_list_t **next_list)
{
    linked_list_t *new = malloc(sizeof(linked_list_t));

    if (new == NULL) {
        write(2, "Can't write to memory", 21);
        return (84);
    }
    new->data = data;
    new->next = *next_list;
    *next_list = new;
    return (0);
}

linked_list_t *my_params_to_list(int ac, char * const *av)
{
    linked_list_t *previous = NULL;

    for (int i = 0 ; i < ac ; i++) {
        my_add_node(av[i], &previous);
    }
    return previous;
}
