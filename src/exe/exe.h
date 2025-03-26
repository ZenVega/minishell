/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:25 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/19 11:06:28 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXE_H
# define EXE_H

# include "../includes/minishell.h"
# include "../malloc_list/malloc_list.h"
# include "../utils/utils.h"
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_exe {
	char	**args;
	char	*cmd_name;
	char	*path;
}	t_exe;

//exe.c
int		exe(t_app *app, t_cmd_info *cmd);
//exe_bin.c
int		exe_bin(t_app *app, t_cmd_info *cmd);
//exe_utils.c
int		is_valid(t_cmd_info *cmd);
void	reroute_io(int input, int output);
int		is_in_path(char *path, char *cmd_name);

#endif
