/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:55:23 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/08 14:59:04 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

char	**get_paths(t_cmd_info *cmd, char *cmd_name)
{
	int		i;
	int		path_len;
	char	**paths;
	char	*tmp;

	tmp = getenv("PATH");
	if (!tmp)
		return (set_err(cmd, ERR_NO_VAR, "PATH"), NULL);
	cmd_name = ft_strjoin("/", cmd_name);
	if (!cmd_name)
		return (set_err(cmd, ERR_MALLOC, NULL), NULL);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (set_err(cmd, ERR_MALLOC, NULL), NULL);
	path_len = get_paths_len(paths);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd_name);
		if (!tmp)
			return (free_paths(cmd, paths, path_len, cmd_name));
		free(paths[i]);
		paths[i] = tmp;
		if (!paths[i])
			return (free_paths(cmd, paths, path_len, cmd_name));
		i++;
	}
	free(cmd_name);
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
			add_to_malloc_list(&app->malloc_list, *paths);
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
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		init_sa_child(app);
		reroute_io(cmd->infile, cmd->outfile);
		execve(exe->path, exe->args, app->envp);
		perror("execve failed");
		exit(-1);
	}
	init_sa_parent(app);
	waitpid(pid, &status, 0);
	return (status);
}

int	exe_bin(t_app *app, t_cmd_info *cmd)
{
	t_exe	*exe;
	int		err;

	err = exe_buildin(app, cmd);
	if (err == 1) 
	{
		exe = init_exe(app, cmd);
		if (!exe || !exe->path)
			err = -1;
		else
			err = call_execve(exe, app, cmd);
	}
	if (cmd->infile != 0)
		close(cmd->infile);
	if (cmd->outfile != 1)
		close(cmd->outfile);
	return (err);
}
