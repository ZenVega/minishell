/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:25 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/17 11:51:20 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef EXE_H
# define EXE_H

# include "../includes/minishell.h"
# include "../utils/utils.h"
# include <unistd.h>
# include <stdlib.h>

typedef struct s_exe {
	char	*args;
	char	*cmd;
	char	*path;
}	t_exe;

//exe.c
int		exe(t_cmd_info *cmd);
//exe_bin.c
int		exe_bin(t_cmd_info *cmd);
//exe_utils.c
void	isolate_cmd(char *args, char *dest);
int		is_valid(t_cmd_info *cmd);

#endif
