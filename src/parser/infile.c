/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:20:09 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/19 16:22:21 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// finding > in splits and set infile
//options: 1) >infile 2) > infile

// circling through all the argument parts,
//multiple infiles are just overwritten by following
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
	cmd->infile = open(clean_filename(file_name), O_RDONLY);
	if (cmd->infile < 0)
		return (set_err(cmd, ERR_NO_FILE, file_name));
	return (0);
}

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

char	*find_hd_name(void)
{
	int		count;
	int		fd;
	char	*hd_name;

	count = 0;
	fd = -1;
	while (fd < 0)
	{
		hd_name = get_hd_name(count);
		if (access(hd_name, F_OK))
			fd = open(hd_name, O_RDWR | O_CREAT, 0777);
		else
			free(hd_name);
		count++;
	}
	close(fd);
	return (hd_name);
}

int	here_doc(char *delimiter, t_cmd_info *cmd)
{
	char	*next_line;
	int		fd;
	char	*hd_name;

	hd_name = find_hd_name();
	fd = open(hd_name, O_RDWR | O_CREAT, 0777);
	while (1)
	{
		next_line = readline(">");
		if (ft_strlen(delimiter) == ft_strlen(next_line)
			&& ft_strncmp(delimiter, next_line, ft_strlen(delimiter)) == 0)
		{
			free(next_line);
			close(fd);
			cmd->infile = open(hd_name, O_RDONLY);
			unlink(hd_name);
			free(hd_name); 
			return (0);
		}
		ft_fprintf(fd, "%s\n", next_line);
		free(next_line);
	}
	return (free(hd_name), 0);
}
