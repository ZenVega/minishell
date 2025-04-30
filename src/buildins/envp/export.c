/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:49:45 by jhelbig           #+#    #+#             */
/*   Updated: 2025/04/30 12:30:48 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	export_no_args(t_app *app)
{
	char	**print;
	int		i;
	char	*addr;
	char	*substr;

	print = copy_and_qsort(app->envp);
	if (!print)
		return (-1);
	i = 0;
	while (print[i])
	{
		addr = ft_strchr(print[i], '=');
		if (addr != NULL)
		{
			substr = ft_substr(print[i], 0, (size_t)(addr - print[i] + 1));
			ft_printf("declare -x %s\"%s\"\n", substr, addr + 1);
			free(substr);
		}
		else
			ft_printf("declare -x %s\n", print[i]);
		i++;
	}
	free_envp(print);
	app->ret_val = 0;
	return (0);
}

int	ft_export(t_app *app, t_cmd_info *cmd)
{
	if (!cmd->args[1])
		return (export_no_args(app));
	else
		return (export_with_args(app, cmd));
}
