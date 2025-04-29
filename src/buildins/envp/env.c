/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:41:06 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/29 12:09:01 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	env(t_app *app, t_cmd_info *cmd)
{
	int	i;

	i = 0;
	reroute_io(cmd->infile, cmd->outfile);
	while (app->envp[i])
	{
		ft_printf("%s\n", app->envp[i]);
		i++;
	}
	if (cmd->infile != 0)
		close(cmd->infile);
	if (cmd->outfile != 1)
		close(cmd->outfile);
	return (0);
}
