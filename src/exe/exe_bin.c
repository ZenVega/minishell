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

char	**get_paths(char *cmd)
{
	int		path_len;
	int		i;
	char	**paths;
	char	*tmp;

	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		path_len = ft_strlen(cmd) + ft_strlen(paths[i]) + 2;
		tmp = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, cmd);
		free(tmp);
		i++;
	}
	return (paths);
}

// initialize exe obj
// add cmd name to path
t_exe	*init_exe(t_app *app, char **args)
{
	t_exe	*exe;
	char	**paths;
	int		found;

	found = 0;
	exe = (t_exe *)malloc_and_add_list(&app->malloc_list, sizeof(t_exe));
	exe->args = args;
	exe->path = NULL;
	exe->cmd_name = args[0];
	paths = get_paths(exe->cmd_name);
	while (*paths)
	{
		if (!found && !access(*paths, X_OK))
		{
			found = 1;
			exe->path = *paths;
			add_to_malloc_list(&app->malloc_list, exe->path);
		}
		else
			free(*paths);
		paths++;
	}
	return (exe);
}

// execute with fnct
int	exe_bin(t_app *app, t_cmd_info *cmd)
{
	t_exe	*exe;
	int		pid;
	int		status;

	exe = init_exe(app, cmd->args);
	if (exe->path)
	{
		ft_printf("Found in path %s\n", exe->path);
		pid = fork();
		if (pid == 0)
		{
			reroute_io(cmd->infile, cmd->outfile);
			execve(exe->path, cmd->args, app->envp);
			perror("execve failed");
			exit(1);
		}
		wait(&status);
	}
	else
	{
		ft_printf("Not found in path\n");
		return (exe_buildin(cmd->args));
	}
	return (1);
}
