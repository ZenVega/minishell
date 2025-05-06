/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:20:09 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/06 11:01:41 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// finding > in splits and set infile
//options: 1) >infile 2) > infile

// circling through all the argument parts, multiple infiles are just overwritten by following
int	set_infile(char **args, t_cmd_info *cmd)
{
	int		i;
	int		err;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '<')
		{
			err = found_infile(args, i, cmd);
			if (err != 0)
				return (err);
		}
		i++;
	}
	return (0);
}

int	found_infile(char **args, int i, t_cmd_info *cmd)
{
	char	*file_name;

	file_name = NULL;
	// case < infile
	if (ft_strlen(args[i]) == 1)
	{
		if (args[i + 1])
			file_name = args[i + 1];
		else
			return (set_err(cmd, ERR_SYNTAX, "after <"));
		return (simple_infile(file_name, cmd));
	}
	if (ft_strlen(args[i]) == 2 && args[i][1] == '<')
	{
		if (!args[i + 1])
			return (set_err(cmd, ERR_SYNTAX, "after <<"));
		return (here_doc(args[i + 1], cmd));
	}
	return (0);
}

int	simple_infile(char *file_name, t_cmd_info *cmd)
{
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	cmd->infile = open(file_name, O_RDONLY);
	if (cmd->infile < 0)
		return (set_err(cmd, ERR_NO_FILE, file_name));
	return (0);
}
int here_doc(char *delimiter, t_cmd_info *cmd)
{
	char	*next_line;
	int		fd;

	fd = open("here_doc", O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 0777);
	if (fd < 0)
		return (set_err(cmd, ERR_NO_FILE, "here_doc"));
	while (1)
	{
		next_line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(delimiter, next_line, ft_strlen(delimiter)) == 0)
		{
			free(next_line);
			close(fd);
			cmd->infile = open("here_doc", O_RDONLY);
			unlink("here_doc");
			return (0);
		}
		write(fd, next_line, ft_strlen(next_line));
		free(next_line);
	}
	return (0);
}