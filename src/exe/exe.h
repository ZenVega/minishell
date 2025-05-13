/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:25 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/13 10:05:30 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# include "../buildins/buildins.h"
# include "../error/error.h"
# include "../init/init.h"
# include "../malloc_list/malloc_list.h"
# include "../parser/parser.h"
# include "../signals/signals.h"
# include "../utils/utils.h"
# include <errno.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_exe {
	char	**args;
	char	*cmd_name;
	char	*path;
}	t_exe;

//exe.c
int				exe(t_app *app, t_cmd_info *cmd);
//exe_bin.c
int				exe_bin(t_app *app, t_cmd_info *cmd);
//exe_clean.c
int				clean_args(t_cmd_info *cmd);
//exe_pip
int				open_pipe(t_app *app, t_cmd_info *cmd);
//exe_utils.c
int				is_valid(t_cmd_info *cmd);
void			*free_paths(t_cmd_info *cmd, char **paths,
					int len, char *cmd_name);
int				has_access_ret(t_app *app, t_cmd_info *cmd, char *path);
//exe_get_path
char			*get_path(t_cmd_info *cmd, t_exe *exe, t_app *app);
#endif
