/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:25 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/27 14:07:53 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXE_H
# define EXE_H

# include "../malloc_list/malloc_list.h"
# include "../utils/utils.h"
# include <dirent.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../parser/parser.h"

typedef struct s_exe {
	char	**args;
	char	**envp;
	char	*cmd_name;
	char	*path;
}	t_exe;

//exe.c
int				exe(t_app *app, t_cmd_info *cmd);
//exe_bin.c
int				exe_bin(t_app *app, t_cmd_info *cmd);
//exe_pip
int				open_pipe(t_app *app, t_cmd_info *cmd);
//exe_utils.c
t_parser_info	init_parser_info(int infile, int outfile, char *line);
int				is_in_path(char *path, char *cmd_name);
int				is_valid(t_cmd_info *cmd);
void			reroute_io(int input, int output);

#endif
