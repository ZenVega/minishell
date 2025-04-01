/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:55:23 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/27 14:03:49 by uschmidt         ###   ########.fr       */
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
	exe->args = dup_str_arr(args);
	if (!exe->args)
		return (NULL);
	exe->envp = dup_str_arr(app->envp);
	if (!exe->envp)
	{
		free_list(exe->args);
		return (NULL);
	}
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
		return (errno = ENOENT, NULL);
	return (exe);
}

void	free_exe(t_exe *exe)
{
	free_list(exe->args);
	free_list(exe->envp);
	free(exe->path);
	free(exe);
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
		return (-1);
	if (exe->path)
	{
		pid = fork();
		if (pid == 0)
		{
			reroute_io(cmd->infile, cmd->outfile);
			free_malloc_list(app);
			free(app);
			free(cmd);
			execve(exe->path, exe->args, exe->envp);
			perror("execve failed");
			exit(errno);
		}
		//TODO: how to test this?
		waitpid(pid, &status, 0);
		if (cmd->infile != 0)
			close(cmd->infile);
		if (cmd->outfile != 1)
			close(cmd->outfile);
	}
	else
	{
		free(exe);
		return (-1);
	}
	return (0);
}
