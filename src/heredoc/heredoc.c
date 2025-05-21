/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:42:30 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/21 15:38:36 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

int	here_doc(t_app *app, char *delimiter, t_cmd_info *cmd)
{
	char	*next_line;
	int		fd;
	char	*hd_name;
	int		pid;
	int		status;
	int		err;

	usleep (10000); //sehr dirty, I know
	err = 0;
	hd_name = find_hd_name(&fd);
	pid = fork();
	if (pid == -1)
		return (-1); // error handling
	else if (pid == 0)
	{
		init_signal_hd_child(app);
		while (1)
		{
			next_line = readline("🐡 ");
			// handles Ctrl-D
			if (next_line == NULL)
			{
				write(STDOUT_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted ", 67);
				write(STDOUT_FILENO, delimiter, ft_strlen(delimiter));
				write(STDOUT_FILENO, ")\n", 2);
				close(fd);
				exit (0);
			}
			//everything goes well
			if (ft_strlen(delimiter) == ft_strlen(next_line)
				&& ft_strncmp(delimiter, next_line, ft_strlen(delimiter)) == 0)
			{
				free(next_line);
				close(fd); 
				exit (0);
			}
			ft_fprintf(fd, "%s\n", next_line);
			free(next_line);
		}
	}
	else
	{
		init_signal_hd_parent(app);
		waitpid(pid, &status, 0);
		ft_printf("%d, %d, %d\n", status % 256, WIFEXITED(status), WIFSIGNALED(status));
		if (g_global_signal == 130)
		{
			kill(pid, SIGTERM);
			err = 107;
			unlink(hd_name);
			close(fd);
		}
		else
		{
			cmd->infile = open(hd_name, O_RDONLY);
			unlink(hd_name);
		}
	}
	return (free(hd_name), err);
}

int	create_heredoc(t_app *app, t_parser_info *p_info, t_cmd_info *cmd)
{
	t_heredoc	*hd;
	t_list		*new;
	int			err;

	while (1)
	{
		err = find_del(app, p_info, cmd, &hd);
		if (err == 1)
			break ;
		if (err == -1)
			return (-1);
		new = ft_lstnew(hd);
		if (!new)
			return (-1);
		ft_lstadd_back(&app->hds, new);
	}
	return (0);
}
