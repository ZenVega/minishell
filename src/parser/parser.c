/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:47:31 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/25 12:27:22 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "parser.h"
#include "../malloc_list/malloc_list.h"
#include "../libft/libft.h"

int	parser(char *line, t_list **malloc_list)
{
	t_cmd_info	cmd;
	char		**parts;
	
	//find pipe, split on first pipe
	parts = NULL;
	parts = pipe_split(line, malloc_list);
	if (parts)
	{
		cmd.args = parts;
		cmd.type = PIPE;
		return (&cmd);
	}
}
