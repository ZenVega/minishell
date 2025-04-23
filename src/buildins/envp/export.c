/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:49:45 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/23 11:01:50 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int export_no_args(t_app *app)
{
	char	**print;
	int		i;
	
	print = copy_and_qsort(app->envp);
	if (!print)
		return (-1);
	i = 0;
	while(print[i])
	{
		ft_printf("declare -x %s\n", print[i]);
		i++;
	}
	free_envp(print);
	return (0);
}

int	ft_export(t_app *app, t_cmd_info *cmd)
{
	if (cmd->args[0] && !cmd->args[1])
		return (export_no_args(app));
	return (0);
}
