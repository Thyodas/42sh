##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC = src/main.c \
	  src/memory/mem_shell.c \
	  src/execution/command.c \
	  src/execution/env_utils.c \
	  src/execution/signal.c \
	  src/execution/builtin_utils.c \
	  src/execution/command_error.c \
	  src/execution/prompt.c \
	  src/execution/io/retrieve_io.c \
	  src/execution/io/heredoc.c \
	  src/execution/io/pipe.c \
	  src/builtin/cd.c \
	  src/builtin/setenv.c \
	  src/builtin/exit.c \
	  src/builtin/unsetenv.c \
	  src/builtin/env.c \
	  src/parser/parse_line.c \
	  src/parser/parse_command.c \
	  src/parser/token_handlers.c \
	  src/parser/char_test.c

OBJ = $(SRC:.c=.o)

NAME = 42sh

INCLUDE = include

LIB = lib/my

CFLAGS = -I$(INCLUDE) -Wall -Wextra -g

%.o: %.c
	@echo "👉️ Compiling \033[1m$<\033[0m"
	@$(CC) $(CFLAGS) -c -o $@ $<

all:
	@$(MAKE) -s $(NAME)

make_lib:
		  make -C $(LIB)

title:
		@echo "\033[1;37m\033[1;46m                   MINISHELL1\
                    \033[0m"

$(NAME): make_lib title $(OBJ)
		 gcc -g -o $(NAME) $(OBJ) -L$(LIB) -lmy
		 rm -f $(OBJ)

clean:
	   make clean -C $(LIB)
	   rm -f $(OBJ)

fclean: clean
		make fclean -C lib/my
		rm -f $(NAME)

re: fclean all

tests_run: re
		cp ./42sh ./tests/42sh
		cd ./tests && ./tester.sh

.PHONY: fclean title all debug re clean tests_run make_lib $(NAME)