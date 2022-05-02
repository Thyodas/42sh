##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC = check_overflow.c \
	  convert_base.c \
	  my_compute_power_rec.c \
	  my_compute_square_root.c \
	  my_find_prime_sup.c \
	  my_getnbr_base.c \
	  my_getnbr.c \
	  my_is_prime.c \
	  my_isneg.c \
	  my_put_nbr.c \
	  my_putchar.c \
	  my_putnbr_base.c \
	  my_putstr.c \
	  my_revstr.c \
	  my_show_word_array.c \
	  my_showmem.c \
	  my_showstr.c \
	  my_sort_int_array.c \
	  my_str_isalpha.c \
	  my_str_islower.c \
	  my_str_isnum.c \
	  my_str_isalphanum.c \
	  my_str_isprintable.c \
	  my_str_isupper.c \
	  my_strcapitalize.c \
	  my_strcat.c \
	  my_strdup.c \
	  my_strlen.c \
	  my_strlowcase.c \
	  my_strncat.c \
	  my_strncmp.c \
	  my_strcmp.c \
	  my_strncpy.c \
	  my_strstr.c \
	  my_strupcase.c \
	  my_swap.c \
	  my_strcpy.c \
	  power.c \
	  swap_endian_color.c \
	  get_color.c \
	  my_printf/my_printf.c \
	  my_printf/struct_utils.c \
	  my_printf/type_base.c \
	  my_printf/type_char.c \
	  my_printf/type_num.c \
	  my_printf/type_utils.c \
	  my_printf/printf_handling.c \
	  my_printf/type_float.c \
	  my_printf/str_utils.c \
	  my_printf/type_long_base.c \
	  my_printf/my_fprintf.c \
	  my_list/my_add_in_sorted_list.c \
	  my_list/my_apply_on_matching_nodes.c \
	  my_list/my_apply_on_nodes.c \
	  my_list/my_concat_list.c \
	  my_list/my_delete_nodes.c \
	  my_list/my_find_node.c \
	  my_list/my_list_size.c \
	  my_list/my_merge.c \
	  my_list/my_params_to_list.c \
	  my_list/my_rev_list.c \
	  my_list/my_sort_list.c \
	  my_strtok.c \
	  my_strtok_alpha.c \
	  my_strcmp_alpha.c \
	  my_putstr_stream.c

OBJ = $(SRC:.c=.o)

NAME = libmy.a

all:
	 @echo "\033[1;37m\033[1;42m                     Lib 📚️\
	                      \033[0m"
	 @$(MAKE) -s $(NAME)

%.o: %.c
	@echo "👉️ Compiling \033[1m$<\033[0m"
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ)

		 ar rc $(NAME) $(OBJ)
		 mkdir -p ../../include
		 cp my.h ../../include/my.h
		 cp my_list/my_list.h ../../include/my_list.h
		 cp $(NAME) ../$(NAME)

clean:
	   rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)
		rm -f ../$(NAME)

re: fclean all

.PHONY: fclean all re clean $(NAME)
