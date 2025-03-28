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

void	*free_paths(char **paths)
{
	while (*paths)
	{
		free(*paths);
		paths++;
	}
	errno = ENOMEM;
	return (NULL);
}

char	**get_paths(char *cmd)
{
	int		path_len;
	int		i;
	char	**paths;
	char	*tmp;

	tmp = getenv("PATH");
	if (!tmp)
		return (errno = ENOENT, NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (errno = ENOMEM, NULL);
	i = 0;
	while (paths[i])
	{
		path_len = ft_strlen(cmd) + ft_strlen(paths[i]) + 2;
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (free_paths(paths), NULL);
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, cmd);
		if (!paths[i])
			return (free_paths(paths), NULL);
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
	if (!paths)
		return (NULL);
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
	if (!found)
		return (errno = EPERM, NULL);
	return (exe);
}

// execute with fnct
int	exe_bin(t_app *app, t_cmd_info *cmd)
{
	t_exe	*exe;
	int		pid;
	int		status;

	//TODO: build ins will be checket first, before allocating path memory
	exe = init_exe(app, cmd->args);
	if (!exe)
		return (errno);
	if (exe->path)
	{
		pid = fork();
		if (pid == 0)
		{
			reroute_io(cmd->infile, cmd->outfile);
			execve(exe->path, cmd->args, app->envp);
			//execve(exe->path, cmd->args, app->envp);
			perror("execve failed");
			exit(errno);
		}
		wait(&status);
	}
	else
	{
		ft_printf("Not found in path\n");
		return (exe_buildin(cmd->args));
	}
	return (errno);
}
