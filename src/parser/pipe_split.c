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


char **pipe_split(char *line, t_list **malloc_list)
{
	char	*part;
	char	**parts;
	size_t	len;

	parts = (char **)malloc(sizeof(char*) * 3);
 	if (!parts)
 	// TODO: error-handling
		return (NULL);

 	parts[2] = NULL;
	part = strchr(line, '|');
	if (part)
	{
		//left part
		len = part - line;
		parts[0] = (char *)malloc(len + 1);
		if (parts[0])
			ft_strlcpy(parts[0], line, len);
		parts[0][len] = '\0';

		//right
		parts[1] = strdup(part + 1);
		if(!parts[0] || !parts[1])
		{
			free(parts[0]);
			free(parts[1]);
			free(parts);
			return (NULL);
		}		
		add_to_malloc_list(malloc_list, parts[0]);
		add_to_malloc_list(malloc_list, parts[1]);
		add_to_malloc_list(malloc_list, parts);
	}
	else
	{
		free(parts);
		return (NULL);
	}
	return (parts);

}
