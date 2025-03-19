# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 11:27:10 by jhelbig           #+#    #+#              #
#    Updated: 2025/03/19 09:47:15 by jhelbig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parser_tester

SRC = parser_test.c \
		parser_error.c \
		cmd_info_init.c \
		in_out.c \
		../malloc_list/malloc_list.c

OBJS = $(SRC:%.c=%.o)

HEADERS = parser.h \
			../malloc_list/malloc_list.h

LIBFT_DIR = ../libft

LIBFT_A = $(LIBFT_DIR)/libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

MAKEALL = make all

MAKEBONUS = make bonus

MAKECLEAN = make clean

MAKEFCLEAN = make fclean

all: $(NAME)

${NAME}: ${OBJS} ${HEADERS} $(LIBFT_A)
		$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(LIBFT_A)


${LIBFT_A}:
	$(MAKEBONUS) -C $(LIBFT_DIR)

debug: $(NAME)
	gdb --args ./$(NAME)

clean: 
	$(MAKECLEAN) -C $(LIBFT_DIR)
	rm -f $(OBJS)
	
fclean: clean
	$(MAKEFCLEAN) -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
