/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:55:23 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/17 10:18:02 by uschmidt         ###   ########.fr       */
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

// finds path of binary on system
char	*get_path(char *cmd_name)
{
	char	*path;

	path = getenv("PATH");
	ft_printf("%s\n", path);
	path = cmd_name;
	return (path);
}

// execute with fnct
int	exe_bin(t_cmd_info *cmd)
{
	char	*path;

	path = get_path(cmd->args[0]);
	if (path)
		return (execv(path, cmd->args));
	else
		return (exe_buildin(cmd->args));
}
