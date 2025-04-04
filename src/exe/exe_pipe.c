/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:02:31 by uschmidt          #+#    #+#             */
/*   Updated: 2025/03/27 14:10:07 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

int	open_pipe(t_app *app, t_cmd_info *cmd)
{
	pid_t			pids[2];
	int				fd[2];
	t_parser_info	p_info;
	int				err;

	err = 0;
	pids[0] = fork();
	if (pids[0] == -1)
		return (-1);
	if (pids[0] == 0)
	{
		if (pipe(fd) < 0)
			return (-1);
		pids[1] = fork();
		if (pids[1] == -1)
			return (-1);
		else if (pids[1] == 0) //Child process - write to parent
		{
			close(fd[0]);
			p_info = init_parser_info(cmd->infile, fd[1], cmd->args[0]);
			exe(app, parser(p_info, &app->malloc_list));
			exit(0);
		}
		else //Parent process - read from child
		{
			close(fd[1]);
			p_info = init_parser_info(fd[0], cmd->outfile, cmd->args[1]);
			exe(app, parser(p_info, &app->malloc_list));
			exit(0);
		}
	}
	else
		waitpid(pids[0], NULL, 0);
	return (err);
}
