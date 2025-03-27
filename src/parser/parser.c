/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:47:31 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/27 11:26:12 by uschmidt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd_info	*parser(t_parser_info p_info, t_list **malloc_list)
{
	t_cmd_info	*cmd;
	char		**parts;

	cmd = cmd_info_init(malloc_list);
	//find pipe, split on first pipe
	parts = NULL;
	parts = pipe_split(p_info.line, malloc_list);
	if (parts)
	{
		cmd->args = parts;
		cmd->type = PIPE;
		return (cmd);
	}
	cmd->type = BIN;
	set_io_files(p_info.line, cmd, malloc_list);
	return (cmd);
}
