/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_info_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:37:02 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/31 11:37:14 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../malloc_list/malloc_list.h"

t_cmd_info	*cmd_info_init(t_list **malloc_list, t_parser_info *p_info)
{
	t_cmd_info *cmd_info;

	cmd_info = malloc_and_add_list(malloc_list, sizeof(t_cmd_info));
	if (!cmd_info)
		return (NULL);
	cmd_info->infile = p_info->infile;
	cmd_info->outfile = p_info->outfile;
	cmd_info->args = NULL;
	cmd_info->type = UNDEFINED;

	return (cmd_info);
}
