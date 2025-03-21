/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_info_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:37:02 by jhelbig           #+#    #+#             */
/*   Updated: 2025/03/18 09:38:50 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_info_init(t_cmd_info *cmd_info)
{
	cmd_info->infile = 0;
	cmd_info->outfile = 1;
	cmd_info->args = NULL;
}
