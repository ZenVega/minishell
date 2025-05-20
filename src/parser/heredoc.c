/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:15:04 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/20 15:45:30 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_hd_name(int count)
{
	char	*hd_name;
	char	*hd_id;

	hd_id = ft_itoa(count);
	if (!hd_id)
		return (NULL);
	hd_name = ft_strjoin("here_doc_", hd_id);
	if (!hd_name)
		return (free(hd_id), NULL);
	free(hd_id);
	return (hd_name);
}

static char	*find_hd_name(int *fd)
{
	int		count;
	char	*hd_name;

	count = 0;
	*fd = -1;
	while (*fd < 0)
	{
		hd_name = get_hd_name(count);
		if (access(hd_name, F_OK))
			*fd = open(hd_name, O_RDWR | O_CREAT, 0777);
		else
			free(hd_name);
		count++;
	}
	return (hd_name);
}

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
				write(STDOUT_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted delimiter)\n", 78);
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
		cmd->infile = open(hd_name, O_RDONLY);
		unlink(hd_name);
		if (g_global_signal == 130)
		{
			kill(pid, SIGTERM);
			err = 107;
			close(fd);
		}
	}
	return (free(hd_name), err);
}
