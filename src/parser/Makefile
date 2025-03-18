# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 11:27:10 by jhelbig           #+#    #+#              #
#    Updated: 2025/03/18 11:38:37 by jhelbig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parser_tester

SRC = parser_test.c \
		parser_error.c \
		cmd_info_init.c \
		in_out.c

OBJS = $(SRC:%.c=%.o)

HEADERS = parser.h

LIBFT_DIR = ../libft

LIBFT_A = $(LIBFT_DIR)/libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

MAKEALL = make all

MAKECLEAN = make clean

MAKEFCLEAN = make fclean

all: $(NAME)

${NAME}: ${OBJS} ${HEADERS} $(LIBFT_A)
		$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(LIBFT_A)


${LIBFT_A}:
	$(MAKEALL) -C $(LIBFT_DIR)
	
clean: 
	$(MAKECLEAN) -C $(LIBFT_DIR)
	rm -f $(OBJS)
	
fclean: clean
	$(MAKEFCLEAN) -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
