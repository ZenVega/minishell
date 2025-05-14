/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:02:31 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/14 15:25:35 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

static void	handle_parent(t_app *app, int pid0, t_cmd_info *cmd, int *status)
{
	init_sa_parent(app);
	waitpid(pid0, status, 0);
	if (cmd && cmd->err_info.suspect)
		free(cmd->err_info.suspect);
	free_malloc_list(app);
}

int	open_pipe(t_app *app, t_cmd_info *cmd)
{
	pid_t			pids[2];
	int				fd[2];
	t_parser_info	p_info;
	int				status;

	pids[0] = fork();
	if (pids[0] == -1)
		return (set_err(cmd, ERR_FORK, NULL));
	if (pids[0] == 0)
	{
		if (pipe(fd) < 0)
			return (set_err(cmd, ERR_PIPE, NULL));
		pids[1] = fork();
		if (pids[1] == -1)
			return (set_err(cmd, ERR_FORK, NULL));
		else if (pids[1] == 0)
		{
			init_sa_child(app);
			close(fd[0]);
			p_info = init_parser_info(cmd->infile, fd[1], cmd->args[0]);
			exe(app, parser(p_info, app));
			close(fd[1]);
			exit(app->ret_val);
		}
		else
		{
			init_sa_child(app);
			close(fd[1]);
			p_info = init_parser_info(fd[0], cmd->outfile, cmd->args[1]);
			exe(app, parser(p_info, app));
			close(fd[0]);
			waitpid(pids[1], &status, 0);
			exit(app->ret_val);
		}
	}
	else
		handle_parent(app, pids[0], cmd, &status);
	app->ret_val = WEXITSTATUS(status);
	return (WEXITSTATUS(status));
}
