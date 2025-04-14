/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:59:35 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/08 15:31:32 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*find_pipe(char *line, int *mask)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && !mask[i])
			return (&line[i]);
		i++;
	}
	return (NULL);
}

/*
gives back a left side and a right side of the pipe for further handling
*/
int	pipe_split(char **parts, t_parser_info *p_info, t_list **malloc_list)
{
	char	*part;
	size_t	len;

	if (!p_info->line || p_info->line[0] == '\0')
		return (2);
	part = find_pipe(p_info->line, p_info->mask);
	// pipe found
	if (part)
	{
		parts[2] = NULL;
		//left part
		len = part - p_info->line;
		parts[0] = malloc_and_add_list(malloc_list, len + 1);
		if (parts[0])
			ft_strlcpy(parts[0], p_info->line, len);
		parts[0][len] = '\0';
		//right part
		parts[1] = ft_strdup(part + 1);
		add_to_malloc_list(malloc_list, parts[1]);
		if (!parts[0] || !parts[1])
			return (-1);
	}
	// no pipe
	else
		return (1);
	return (0);
}
