SRC_FOLDER	= src/
OBJ_FOLDER	= ofiles/

NAME		= minishell

CFILES		:=
# vpath adds a path to find files(%.c)
vpath %.c $(SRC_FOLDER)
CFILES += $(NAME).c

vpath %.c $(SRC_FOLDER)error
CFILES += error.c

vpath %.c $(SRC_FOLDER)exe
CFILES += exe.c
CFILES += exe_bin.c
CFILES += exe_pipe.c
CFILES += exe_utils.c

vpath %.c $(SRC_FOLDER)init
CFILES += init.c

vpath %.c $(SRC_FOLDER)malloc_list
CFILES += malloc_list.c

vpath %.c $(SRC_FOLDER)parser
CFILES += cmd_info_init.c
CFILES += dollar.c
CFILES += here_doc.c
CFILES += in_out_utils.c
CFILES += infile.c
CFILES += outfile.c
CFILES += parser.c
CFILES += pipe_split.c
CFILES += set_io_files.c

vpath %.c $(SRC_FOLDER)shell
CFILES += shell.c

vpath %.c $(SRC_FOLDER)signals
CFILES += signals.c

vpath %.c $(SRC_FOLDER)utils
CFILES += utils.c

#notdir removes all path from filename 
#addprefix adds something to each file, in this case the output folder
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
	/bin/bash -c "gdb ./$(NAME)"

test: $(NAME)
	/bin/bash -c "./$(NAME)"

val_test: $(NAME)
	/bin/bash -c "valgrind --leak-check=full --track-fds=yes ./$(NAME)"

norm:
	norminette $(NAME).c
	norminette src/*
	norminette includes/*

$(NAME): $(OFILES) $(LIBFT)
	$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OFILES) $(LIBFT) $(INC)

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_PATH)

$(OBJ_FOLDER)%.o: %.c $(DEPS)
	mkdir -p $(OBJ_FOLDER)
	$(CC) $(CFLAGS) -I/usr/include $(INC) -g -c $< -o $@

clean:
	rm -f $(OFILES)
	rm -frd $(OBJ_FOLDER)
	find $(SRC_FOLDER) -name "*.o" -delete
	$(MAKE) -C $(LIBFT_PATH) clean

fclean:	clean
	rm -f $(SRC_FOLDER)exe/test/$(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re test debug norm
