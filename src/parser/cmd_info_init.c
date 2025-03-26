/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_info_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:37:02 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/25 13:54:37 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../malloc_list/malloc_list.h"

t_cmd_info	*cmd_info_init(t_list **malloc_list)
{
	t_cmd_info *cmd_info;

	cmd_info = malloc_and_add_list(malloc_list, sizeof(t_cmd_info));
	cmd_info->infile = 0;
	cmd_info->outfile = 1;
	cmd_info->args = NULL;
	cmd_info->type = UN;

	return (cmd_info);
}
