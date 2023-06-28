##
## EPITECH PROJECT, 2023
## makefile
## File description:
## finalstumper_2
##

NAME = 42sh

SRC = src/mysh.c\
	src/command.c\
	src/manage_array.c\
	src/manage_cd.c\
	src/child_proc.c\
	src/priority.c\
	src/separation_of_command.c\
	src/exec_ast.c\
	src/my_stats.c\
	src/manage_exit.c\
	src/manage_pipe.c\
	src/check_error.c\
	src/where.c	\
	src/ast.c\
	src/update.c\
	src/create_ast.c\
	src/redirection.c\
	src/check_case2.c\
	src/manage_echo.c \
	src/redirection_right.c\
	src/my_builtins.c \
	src/histo/init_history.c\
	src/histo/manage_history.c\
	src/histo/check_history.c \
	src/job_control/job_control.c \
	src/prompt/prompt.c	\
	src/prompt/color_panel1.c	\
	src/prompt/color_panel2.c	\
	src/prompt/command_prompt.c	\
	src/prompt/check_errors.c	\
	src/alias/struct_alias.c \
	src/alias/exec_alias.c \
	src/alias/lib.c \
	src/globbings/manage_star.c \
	src/globbings/get.c \
	src/which.c	\

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -W

CC = gcc

all: mlib $(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CFLAGS) -L . -lmy -I include/

debug: mlib
		$(CC) -o debug $(SRC) $(CFLAGS) -L . -lmy -g3 -ggdb -I include/

mlib:
	make -C lib/

clean:
	find -type f -name "#*#" -delete -o \
	-type f -name "*~" -delete -o -type f -name "*.o" -delete -o \
	-type f -name "*.gc*" -delete
	make clean -C lib/

fclean: clean
	rm -f $(NAME)
	rm -f debug
	make fclean -C lib/

re: fclean all
