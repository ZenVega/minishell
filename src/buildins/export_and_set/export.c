/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhelbig <jhelbig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:49:45 by jhelbig           #+#    #+#             */
/*   Updated: 2025/05/14 13:13:08 by jhelbig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_and_set.h"

int	export_no_args(t_app *app, t_cmd_info *cmd)
{
	char	**print;
	int		i;
	char	*addr;
	char	*substr;

	print = copy_and_qsort(app->envp);
	if (!print)
		return (-1);
	i = 0;
	reroute_io(cmd);
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
	free_var_arr(print);
	app->ret_val = 0;
	reset_io(cmd);
	return (0);
}

int	ft_export(t_app *app, t_cmd_info *cmd)
{
	if (!cmd->args[1])
		return (export_no_args(app, cmd));
	else
		return (export_with_args(app, cmd));
}
