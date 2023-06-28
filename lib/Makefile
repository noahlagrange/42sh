##
## EPITECH PROJECT, 2023
## B-PSU-200-RUN-2-1-minishell1-leo.sautron
## File description:
## Makefile
##

NAME = libmy.a

CFLAGS = -Wall -Werror -Wextra -W -I ../include

SRC = my_strcmp.c\
	my_strcpy.c\
	my_strlen.c\
	my_strdup.c\
	my_getnbr.c\
	my_str_to_word_array.c\
	my_strncmp.c\
	my_strcat.c\
	my_putstr.c\
	mini_printf.c\
	my_put_nbr.c\
	my_putchar.c\
	my_strstr.c\
	list.c \
	linked_list.c \
	dup_array.c \
	parser.c \
	skip.c \
	my_strchr.c \
	my_calloc.c \
	my_insert_str.c \
	my_lennbr.c \
	manage_list.c \
	append.c \
	my_strconcat.c \
	get_str_nbr.c \
	my_arrayconcate.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../

clean:
	find -type f -name "#*#" -delete -o \
	-type f -name "*~" -delete -o -type f -name "*.o" -delete -o \
	-type f -name "*.gc*" -delete

fclean: clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re: fclean all
