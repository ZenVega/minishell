/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uschmidt <uschmidt@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:15:04 by uschmidt          #+#    #+#             */
/*   Updated: 2025/05/19 17:32:41 by uschmidt         ###   ########.fr       */
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

int	here_doc(char *delimiter, t_cmd_info *cmd)
{
	char	*next_line;
	int		fd;
	char	*hd_name;

	hd_name = find_hd_name(&fd);
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
