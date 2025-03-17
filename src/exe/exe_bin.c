/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:55:23 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/17 14:58:49 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

// if no path was found, check for build_in functions
int	exe_buildin(char **argv)
{
	if (argv[0])
		return (0);
	return (1);
}

// initialize exe obj
t_exe	*init_exe(char *args)
{
	t_exe	*exe;
	char	**paths;

	//TODO: include in track_malloc
	exe = (t_exe *)malloc(sizeof(t_exe));
	exe->args = args;
	exe->path = NULL;
	isolate_cmd_name(exe->args, &exe->cmd_name);
	paths = ft_split(getenv("PATH"), ':');
	while (*paths)
	{
		ft_printf("PATH: %s\n", *paths);
		if (!is_in_path(*paths, exe->cmd_name))
		{
			exe->path = *paths;
			break ;
		}
		paths++;
	}
	return (exe);
}

// execute with fnct
int	exe_bin(t_cmd_info *cmd)
{
	t_exe	*exe;

	exe = init_exe(cmd->args[0]);
	if (exe->path)
		return (execv(exe->path, cmd->args));
	else
		return (exe_buildin(cmd->args));
}
