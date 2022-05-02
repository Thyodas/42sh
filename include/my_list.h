/*
** EPITECH PROJECT, 2021
** mylist.h
** File description:
** mylist
*/

#ifndef MYLIST_H_H
    #define MYLIST_H_H

    typedef struct node {
        void *data;
        struct node *next;
    } linked_list_t;

    int my_add_node(void *data, linked_list_t **next_list);
    void my_sort_list(linked_list_t **begin, int (*cmp)());
    void my_add_in_sorted_list(linked_list_t **begin, void *data,
        int (*cmp)());
    int my_apply_on_matching_nodes(linked_list_t *begin, int (*f)(),
        void const *data_ref, int (*cmp)());
    int my_apply_on_nodes(linked_list_t *begin, void (*f)());
    void my_concat_list(linked_list_t **begin1, linked_list_t *begin2);
    int my_delete_nodes(linked_list_t **begin, void const *data_ref,
        int (*cmp)());
    linked_list_t *my_find_node(linked_list_t *begin, void const *data_ref,
        int (*cmp)());
    int my_list_size(linked_list_t const *begin);
    void my_merge(linked_list_t **begin1, linked_list_t *begin2,
        int (*cmp)());
    linked_list_t *my_params_to_list(int ac, char * const *av);
    void my_rev_list(linked_list_t **begin);
    void my_sort_list(linked_list_t **begin, int (*cmp)());

#endif /* !MYLIST_H_H */
