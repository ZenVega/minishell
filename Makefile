SRC_FOLDER	= src/
OBJ_FOLDER	= ofiles/

NAME		= minishell

CFILES		:=
# vpath adds a path to find files(%.c)
vpath %.c $(SRC_FOLDER)
CFILES += $(NAME).c

vpath %.c $(SRC_FOLDER)malloc_list
CFILES += malloc_list.c

vpath %.c $(SRC_FOLDER)init
CFILES += init.c

OFILES      = $(addprefix $(OBJ_FOLDER), $(notdir $(CFILES:.c=.o)))

LIBFT_PATH	= $(SRC_FOLDER)libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

INC			= \
			-I ./$(LIBFT_PATH)\

DEPS		= $(SRC_FOLDER)includes/minishell.h\
			  $(SRC_FOLDER)includes/CONSTANTS.h\

CC			= cc

CFLAGS		= -g -Wall -Wextra -Werror

all: $(NAME) 

debug: $(NAME)
	gdb --args ./$(NAME)

test: $(NAME)
	./$(NAME)

norm:
	norminette $(NAME).c
	norminette src/*
	norminette includes/*

$(NAME): $(OFILES) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES) $(LIBFT) $(INC)

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_PATH)

$(OBJ_FOLDER)%.o: %.c $(DEPS)
	mkdir -p $(OBJ_FOLDER)
	$(CC) $(CFLAGS) -I/usr/include $(INC) -g -c $< -o $@

clean:
	rm -f $(OFILES)
	rm -fd $(OBJ_FOLDER)
	find $(SRC_FOLDER) -name "*.o" -delete
	$(MAKE) -C $(LIBFT_PATH) clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re test debug norm
