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

void	*free_paths(t_cmd_info *cmd, char **paths)
{
	while (*paths)
	{
		free(*paths);
		paths++;
	}
	set_err(cmd, ERR_MALLOC, NULL);
	return (NULL);
}

char	**get_paths(t_cmd_info *cmd, char *cmd_name)
{
	int		path_len;
	int		i;
	char	**paths;
	char	*tmp;

	tmp = getenv("PATH");
	if (!tmp)
		return (set_err(cmd, ERR_NO_VAR, "PATH"), NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (set_err(cmd, ERR_MALLOC, NULL), NULL);
	i = 0;
	while (paths[i])
	{
		path_len = ft_strlen(cmd_name) + ft_strlen(paths[i]) + 2;
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (free_paths(cmd, paths), NULL);
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, cmd_name);
		if (!paths[i])
			return (free_paths(cmd, paths), NULL);
		free(tmp);
		i++;
	}
	return (paths);
}

// initialize exe obj
// add cmd name to path
t_exe	*init_exe(t_app *app, t_cmd_info *cmd)
{
	t_exe	*exe;
	char	**paths;
	int		found;

	found = 0;
	exe = (t_exe *)malloc_and_add_list(&app->malloc_list, sizeof(t_exe));
	if (!exe)
		return (set_err(cmd, ERR_MALLOC, NULL), NULL);
	exe->args = cmd->args;
	exe->path = NULL;
	exe->cmd_name = cmd->args[0];
	paths = get_paths(cmd, exe->cmd_name);
	if (!paths)
		return (NULL);
	add_to_malloc_list(&app->malloc_list, paths);
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
		return (set_err(cmd, ERR_NO_FILE, NULL), NULL);
	return (exe);
}

int	call_execve(t_exe *exe, t_app *app, t_cmd_info *cmd)
{
	reroute_io(cmd->infile, cmd->outfile);
	execve(exe->path, exe->args, app->envp);
	perror("execve failed");
	exit(-1);
}
// execute with fnct
int	exe_bin(t_app *app, t_cmd_info *cmd)
{
	t_exe	*exe;
	int		pid;

	//TODO: build ins will be checket first, before allocating path memory
	exe = init_exe(app, cmd);
	if (!exe)
		return (-1);
	if (exe->path)
	{
		pid = fork();
		if (pid == 0)
			call_execve(exe, app, cmd);
		waitpid(pid, NULL, 0);
		if (cmd->infile != 0)
			close(cmd->infile);
		if (cmd->outfile != 1)
			close(cmd->outfile);
	}
	else
		return (-1);
	return (0);
}
