/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:55:23 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/19 11:20:10 by uschmidt         ###   ########.fr       */
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
// add cmd name to path
t_exe	*init_exe(t_app *app, char *args)
{
	t_exe	*exe;
	char	**paths;
	char	*temp;

	exe = (t_exe *)malloc_and_add_list(&app->malloc_list, sizeof(t_exe));
	exe->args = args;
	exe->path = NULL;
	isolate_cmd_name(app, exe->args, &exe->cmd_name);
	paths = ft_split(getenv("PATH"), ':');
	add_list_to_malloc_list(&app->malloc_list, (void **)paths);
	while (*paths)
	{
		if (!is_in_path(*paths, exe->cmd_name))
		{
			temp = ft_strjoin(*paths, "/");
			exe->path = ft_strjoin(temp, exe->cmd_name);
			add_to_malloc_list(&app->malloc_list, exe->path);
			free(temp);
			break ;
		}
		paths++;
	}
	return (exe);
}

// execute with fnct
int	exe_bin(t_app *app, t_cmd_info *cmd)
{
	t_exe	*exe;
	// overwrite in and outfile if necessary
	exe = init_exe(app, cmd->args[0]);
	if (exe->path)
	{
		// fork here to follow processes
		ft_printf("Found in path %s\n", exe->path);
		return (execve(exe->path, cmd->args, app->envp));
	}
	else
	{
		ft_printf("Not found in path");
		return (exe_buildin(cmd->args));
	}
}
