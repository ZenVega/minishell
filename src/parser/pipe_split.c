/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:59:35 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/25 13:44:29 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser.h"
#include "../malloc_list/malloc_list.h"
#include "../libft/libft.h"

/*
gives back a left side and a right side of the pipe for further handling
*/
char	**pipe_split(char *line, t_list **malloc_list)
{
	char	*part;
	char	**parts;
	size_t	len;

	part = ft_strchr(line, '|');
	if (part)
	{
		parts = malloc_and_add_list(malloc_list, sizeof(char *) * 3);
		parts[2] = NULL;
		//left part
		len = part - line;
		parts[0] = malloc_and_add_list(malloc_list, len + 1);
		if (parts[0])
			ft_strlcpy(parts[0], line, len);
		parts[0][len] = '\0';
		//right part
		parts[1] = ft_strdup(part + 1);
		add_to_malloc_list(malloc_list, parts[1]);
		if (!parts[0] || !parts[1])
			return (NULL);
	}
	else
		return (NULL);
	return (parts);
}
