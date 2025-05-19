/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:02:31 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/19 12:29:36 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	handle_parent(int pid0, t_cmd_info *cmd, int *status)
{
	waitpid(pid0, status, 0);
	if (cmd && cmd->err_info.suspect)
		free(cmd->err_info.suspect);
}

static void	handle_grandchild(t_app *app, int fd[2], t_cmd_info *cmd)
{
	t_parser_info	p_info;

	init_sa_child(app);
	close(fd[0]);
	p_info = init_parser_info(cmd->infile, fd[1], cmd->args[0]);
	exe(app, parser(p_info, app));
	close(fd[1]);
	exit(app->ret_val);
}

static int	handle_child(t_app *app, int pids[2], t_cmd_info *cmd)
{
	t_parser_info	p_info;
	int				status;
	int				fd[2];

	status = 0;
	if (pipe(fd) < 0)
		return (set_err(cmd, ERR_PIPE, NULL));
	pids[1] = fork();
	if (pids[1] == -1)
		return (set_err(cmd, ERR_FORK, NULL));
	else if (pids[1] == 0)
		handle_grandchild(app, fd, cmd);
	else
	{
		init_sa_child(app);
		close(fd[1]);
		if (cmd->infile != STDIN_FILENO)
			close(cmd->infile);
		p_info = init_parser_info(fd[0], cmd->outfile, cmd->args[1]);
		exe(app, parser(p_info, app));
		waitpid(pids[1], &status, 0);
		close(fd[0]);
		exit(app->ret_val);
	}
	return (0);
}

int	open_pipe(t_app *app, t_cmd_info *cmd)
{
	pid_t			pids[2];
	int				status;

	if (global_signal == 0)
	{
		init_sa_parent(app);
		global_signal = -1;
	}
	pids[0] = fork();
	if (pids[0] == -1)
		return (set_err(cmd, ERR_FORK, NULL));
	if (pids[0] == 0)
		return (handle_child(app, pids, cmd));
	else
		handle_parent(pids[0], cmd, &status);
	app->ret_val = WEXITSTATUS(status);
	return (0);
}
