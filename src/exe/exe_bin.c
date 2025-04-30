/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:55:23 by uschmidt          #+#    #+#             */
/*   Updated: 2025/04/28 12:44:49 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

// initialize exe obj
// add cmd name to path
t_exe	*init_exe(t_app *app, t_cmd_info *cmd)
{
	t_exe	*exe;

	exe = (t_exe *)malloc_and_add_list(&app->malloc_list, sizeof(t_exe));
	if (!exe)
		return (set_err(cmd, ERR_MALLOC, NULL), NULL);
	exe->args = cmd->args;
	exe->path = NULL;
	exe->cmd_name = ft_strdup(cmd->args[0]);
	add_to_malloc_list(&app->malloc_list, exe->cmd_name);
	if (!exe->cmd_name)
		return (set_err(cmd, ERR_MALLOC, NULL), NULL);
	exe->path = get_path(cmd, exe, app);
	if (!exe->path)
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

	clean_args(cmd);
	err = exe_buildin(app, cmd);
	if (err == BI_NULL) 
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
	app->ret_val = err;
	return (err);
}
