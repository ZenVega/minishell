/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:42:30 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/23 12:47:02 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

static void	write_hd_file(t_app *app, t_heredoc *hd)
{
	char	*next_line;

	init_signal_hd_child(app);
	while (1)
	{
		next_line = readline("🐡 ");
		handle_signals(hd, next_line);
		if (ft_strlen(hd->del) == ft_strlen(next_line)
			&& ft_strncmp(hd->del, next_line, ft_strlen(hd->del)) == 0)
		{
			free(next_line);
			close(hd->fd); 
			exit (0);
		}
		ft_fprintf(hd->fd, "%s\n", next_line);
		free(next_line);
	}
}

int	write_heredoc(t_app *app, t_heredoc *hd, t_cmd_info *cmd)
{
	int		pid;
	int		status;
	int		err;

	err = 0;
	pid = fork();
	disable_ctrl_c_echo(1);
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		write_hd_file(app, hd);
	else
	{
		init_signal_hd_parent(app);
		waitpid(pid, &status, 0);
		err = WEXITSTATUS(status);
		if (!err)
			cmd->infile = open(hd->doc_name, O_RDONLY);
		close(hd->fd);
	}
	return (err);
}

int	create_heredoc(t_app *app, t_parser_info *p_info, t_cmd_info *cmd)
{
	t_heredoc	*hd;
	t_list		*new;
	int			err;

	while (1)
	{
		err = rep_hd(app, p_info, cmd, &hd);
		if (err == 1)
			break ;
		if (err == -1)
			return (-1);
		err = write_heredoc(app, hd, cmd);
		disable_ctrl_c_echo(1);
		if (err == ERR_SIGINT || err == ERR_SIGTER)
			return (p_info->line = "", 0);
		if (err == ERR_SIGTER)
			return (set_err(cmd, ERR_SIGTER, NULL));
		new = ft_lstnew(hd);
		if (!new)
			return (-1);
		ft_lstadd_back(&app->hds, new);
	}
	return (0);
}
