SRC_FOLDER	= src/
OBJ_FOLDER	= ofiles/

NAME		= minishell

CFILES		:=
# vpath adds a path to find files(%.c)
vpath %.c $(SRC_FOLDER)
CFILES += $(NAME).c

vpath %.c $(SRC_FOLDER)buildins
CFILES += buildins.c
vpath %.c $(SRC_FOLDER)buildins/cd
CFILES += cd.c
CFILES += cd_utils.c
vpath %.c $(SRC_FOLDER)buildins/echo
CFILES += echo.c
vpath %.c $(SRC_FOLDER)buildins/env
CFILES += env.c
vpath %.c $(SRC_FOLDER)buildins/export_and_set
CFILES += export.c
CFILES += export_and_set_utils.c
CFILES += export_with_args.c
CFILES += set.c
vpath %.c $(SRC_FOLDER)buildins/exit
CFILES += exit.c
vpath %.c $(SRC_FOLDER)buildins/pwd
CFILES += pwd.c

vpath %.c $(SRC_FOLDER)error
CFILES += error.c

vpath %.c $(SRC_FOLDER)expand
CFILES += expand.c
CFILES += expand_utils.c

vpath %.c $(SRC_FOLDER)exe
CFILES += exe.c
CFILES += exe_bin.c
CFILES += exe_get_path.c
CFILES += exe_pipe.c
CFILES += exe_utils.c

vpath %.c $(SRC_FOLDER)init
CFILES += init.c

vpath %.c $(SRC_FOLDER)heredoc
CFILES += heredoc.c
CFILES += heredoc_utils.c
CFILES += heredoc_signals.c

vpath %.c $(SRC_FOLDER)malloc_list
CFILES += malloc_list.c

vpath %.c $(SRC_FOLDER)mask
CFILES += mask.c

vpath %.c $(SRC_FOLDER)parser
CFILES += cmd_info_init.c
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
CFILES += clean.c
CFILES += utils.c
CFILES += sorting.c

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

CFLAGS		= -Wall -Wextra -Werror

all: $(NAME) 

run: $(NAME)
	@/bin/bash -c "./$(NAME)"

debug: $(NAME)
	@/bin/bash -c "gdb ./$(NAME)"

val_test: $(NAME)
	@/bin/bash -c "valgrind --leak-check=full --track-fds=yes ./$(NAME)"

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
