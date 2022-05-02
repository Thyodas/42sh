/*
** EPITECH PROJECT, 2021
** my_sort_int_array.c
** File description:
** my_sort_int_array
*/

static void my_sort_swap_cmp(int *a, int *b)
{
    int temp;

    if (*a <= *b) {
        temp = *a;
        *a = *b;
        *b = temp;
    }
}

void my_sort_int_array(int *array, int size)
{
    for (int i = size ; i > 0 ; i--) {
        for (int j = 0 ; j < i - 1 ; j++) {
            my_sort_swap_cmp(&array[j + 1], &array[j]);
        }
    }
}
