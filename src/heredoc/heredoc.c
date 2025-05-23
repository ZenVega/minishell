/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:42:30 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/23 12:11:34 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	write_heredoc(t_app *app, t_heredoc *hd, t_cmd_info *cmd)
{
	char	*next_line;
	int		pid;
	int		status;
	int		err;

	err = 0;
	pid = fork();
	if (pid == -1)
		return (-1); // error handling
	else if (pid == 0)
	{
		init_signal_hd_child(app);
		while (1)
		{
			next_line = readline("🐡 ");
			// handles Ctrl-C
 			if (g_global_signal == ERR_SIG)
			{
				unlink(hd->doc_name);
				close(hd->fd);
				write(2, "^C\n", 3);
				exit(ERR_SIG);
				g_global_signal = 0;
			}
			// handles Ctrl-D
			if (next_line == NULL)
			{
				write(STDOUT_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted ", 67);
				write(STDOUT_FILENO, hd->del, ft_strlen(hd->del));
				write(STDOUT_FILENO, ")\n", 2);
				close(hd->fd);
				exit (0);
			}
			//everything goes well
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
	else
	{
		init_signal_hd_parent(app);
		waitpid(pid, &status, 0);
		err = WEXITSTATUS(status);
		if (!err)
			cmd->infile = open(hd->doc_name, O_RDONLY);
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
		if (err == ERR_SIG)
			return (set_err(cmd, ERR_SIG, NULL));
		new = ft_lstnew(hd);
		if (!new)
			return (-1);
		ft_lstadd_back(&app->hds, new);
	}
	return (0);
}
