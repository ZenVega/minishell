/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:47:31 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/02 11:03:41 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd_info	*parser(t_parser_info p_info, t_list **malloc_list)
{
	t_cmd_info	*cmd;
	char		**parts;
	int			err;

	cmd = cmd_info_init(malloc_list, &p_info);
	if (!cmd)
		return (NULL);
	//find pipe, split on first pipe
	parts = (char **)malloc_and_add_list (malloc_list, sizeof(char *) * 3);
	free(p_info.mask);
	err = create_mask(&p_info, malloc_list, cmd);
	if (err == -1 || !parts)
		return (NULL);
	err = pipe_split(parts, &p_info, malloc_list);
	//pipe failed
	if (err == -1)
		return (NULL);
	//pipe exists
	if (err == 0)
	{
		cmd->args = parts;
		cmd->type = PIPE;
		return (cmd);
	}
	cmd->type = BIN;
	err = set_io_files(p_info.line, cmd, malloc_list, p_info.mask);
	if (err != 0)
		return (NULL);
	return (cmd);
}
